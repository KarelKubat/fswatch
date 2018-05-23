class Cmd {
 public:
  Cmd(char **args);
  int getpid() const;
  bool reap();
  bool exited() const;
  int exitstatus() const;
  bool signalled() const;
  int termsig() const;
  bool coredumped() const;
  bool running() const;
  void hose(unsigned killwait);
  unsigned runtime() const;
 private:
  int pid, status;
  bool isrunning;
  time_t starttime;
};
