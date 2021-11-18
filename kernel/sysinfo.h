struct sysinfo {
  uint64 freemem;   // amount of free memory (bytes)
  uint64 nproc;     // number of process
};

uint64 getnproc(void);
uint64 getfreemem(void);
