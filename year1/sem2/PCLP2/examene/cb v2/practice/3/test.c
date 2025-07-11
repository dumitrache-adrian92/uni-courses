#include <stdio.h>

extern void reveal_passwd(const char *passwd);
extern void show_message(unsigned int pin, const char *password);

int main(void)
{
	// TODO: b)
	reveal_passwd("heard");

  // TODO: c)
	show_message(19228, "yorkshire terrier");

	return 0;
}
