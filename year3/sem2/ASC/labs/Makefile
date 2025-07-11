# Compiler collection setup
NVCC      ?= nvcc
NVCCFLAGS ?=
CPPFLAGS  ?=
LDFLAGS   ?=
LIBS      ?=
EXECS     ?=

# Cluster setup
PARTITION  ?= ucsx
RUN_TIME   ?= 00:05:00
BUILD_TIME ?= 00:05:00
IMG        ?= docker://gitlab.cs.pub.ro:5050/asc/asc-public/cuda-labs:1.9.1
LOAD_CMD   ?= module load libraries/cuda-11.4;
BUILD_CMD  ?= make LOCAL=y
RUN_CMD    ?= ./$${exec}

build: $(EXECS)

# Build each executable
$(EXECS): %: %.cu
	$(NVCC) $(NVCCFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LIBS)


clean:
	rm -f $(EXECS) slurm-*.out slurm-*.err
