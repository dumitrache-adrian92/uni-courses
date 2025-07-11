/*
 * Loader Implementation
 *
 * 2077, Operating Systems
 */

#include "loader.h"
#include "exec_parser.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

static so_exec_t *exec;
static int fd;

/* determines how many bytes we should copy from the file to memory in a three
 * case simplified method
 */
static int page_size_in_file(char *signal_addr, int segment, unsigned int page)
{
	unsigned int page_size = getpagesize();
	unsigned int file_page_count; // how many pages are actually in the file

	file_page_count = exec->segments[segment].file_size / page_size + 1;
	// regular full size page if the page is in the file, but isn't the last
	if (page + 1 < file_page_count)
		return page_size;

	// don't copy anything if the page isn't part of the file
	if (page + 1 > file_page_count)
		return 0;

	/* if we're on the last page of the file, we only need to copy the bytes
	 * that are actually part of the file, this is because the last page isn't
	 * always completely occupied by file data
	 */
	return exec->segments[segment].file_size - page * page_size;
}

static void segfault_handler(int sig, siginfo_t *info, void *ucontext)
{
	unsigned int page, page_count;
	char *segment_addr, *signal_addr, *data;
	unsigned int page_size = getpagesize();
	int copy_size;

	signal_addr = (char *)info->si_addr;
	// loop through the segments to figure out the origin of the segfault
	for (int i = 0; i < exec->segments_no; i++) {
		segment_addr = (char *)exec->segments[i].vaddr;

		// if true, our SIGSEGV is caused by an access in this segment
		if (signal_addr >= segment_addr &&
			signal_addr < segment_addr + exec->segments[i].mem_size) {
			page_count = exec->segments[i].mem_size / page_size + 1;

			/* we'll be using data to determine which pages have already been
			 * mapped, data[i] == 1 => page i is mapped
			 */
			if (exec->segments[i].data == NULL)
				exec->segments[i].data = calloc(page_count, sizeof(char));
			data = exec->segments[i].data; // ease of use

			// the page from which the SISEGV originates
			page = (int)(signal_addr - exec->segments[i].vaddr) / page_size;
			// if it has already been mapped we're dealing with a real segfault
			if (data[page])
				break;

			// map the page with temporary write permissions for copying data
			char *mapped = mmap(segment_addr + page * page_size, page_size,
								PROT_WRITE, MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS,
								-1, 0);
			if (mapped == MAP_FAILED) {
				perror("mmap");
				exit(-1);
			}

			copy_size = page_size_in_file(signal_addr, i, page);
			/* copy the page from the executable to memory if the page isn't completely
			 * bss, otherwise leave it zeroed
			 */
			if (copy_size) {
				lseek(fd, exec->segments[i].offset + page * page_size, SEEK_SET);
				if (read(fd, mapped, copy_size) == -1) {
					perror("read");
					exit(-1);
				}
			}

			// set correct permissions and mark the page as mapped
			if (mprotect(mapped, page_size, exec->segments[i].perm)) {
				perror("mprotect");
				exit(-1);
			}
			data[page] = 1;

			// exit the handler without throwing a segfault
			return;
		}
	}

	/* if the handler gets to this point, it means we're dealing with an actual
	 * segfault so we'll be sending another segfault signal using the default
	 * handler to stop execution
	 */
	signal(SIGSEGV, SIG_DFL);
	raise(SIGSEGV);
}

int so_init_loader(void)
{
	struct sigaction segfault_action;
	memset(&segfault_action, 0, sizeof(segfault_action));

	// sigaction structure setup for flags and new handler
	segfault_action.sa_flags = SA_SIGINFO;
	segfault_action.sa_sigaction = segfault_handler;

	// installing the new handler for SIGSEGV and accounting for errors
	if (sigaction(SIGSEGV, &segfault_action, NULL) < 0) {
		perror("sigaction");
		return -1;
	}

	return 0;
}

int so_execute(char *path, char *argv[])
{
	// opening the file globally so the handler can access it
	fd = open(path, O_RDONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	exec = so_parse_exec(path);
	if (!exec)
		return -1;

	so_start_exec(exec, argv);

	if (close(fd) < 0) {
		perror("close");
		exit(1);
	}

	return -1;
}
