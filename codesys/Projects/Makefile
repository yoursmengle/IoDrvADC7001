# output usage by default
.PHONY:help
help:
	@echo "Show usage:"
	@echo "1) Build commands";
	@echo "all:                        build codesyscontrol";
	@echo "clean:                      clean codesyscontrol";
	@echo ""
	@echo "2) Basic ssh commands";
	@echo "ssh:                        login establish ssh connection to target"
	@echo "wipe_login:                 delete credentials/login for ssh, e.g. to connect to another target"
	@echo ""
	@echo "3) Remote commands";
	@echo "deploy:                     deploy codesyscontrol binary to target"
	@echo "start:                      start codesyscontrol binary on target"
	@echo "stop:                       stop all runtimes/gdbserver/installed runtimes on target"
	@echo "gdbserver:                  start codesyscontrol in gdbserver on target and remote debug target"
	@echo "gdbserver_attach:           attach with gdbserver on target (runtime must be running already. see command start) and remote debug target"
	@echo ""
	@echo "4) Component commands";
	@echo "cmp        DEP=<path to Dep.m4>:   build component as libCmp<xyz>.so"
	@echo "clean_cmp  DEP=<path to Dep.m4>:   clean component"
	@echo "deploy_cmp DEP=<path to Dep.m4>:   build and deploy libCmp<xyz>.so to target"
	@echo ""
	@echo ""
	@echo "**NOTE**"
	@echo "Some of the remote commands are working asynchronously (start, gdbserver, gdbserver_attach). "
	@echo "They require that there is no password prompt (e.g. for the sudo command)."
	@echo "If you want to use these commands, these prompts have to be avoided."
	@echo ""
	@echo "For sudo you can achieve this, by adding a line to your sudoers file:"
	@echo "e.g. if your user is called 'debian', you could tell your system to not prompt for password for sudo:"
	@echo "debian ALL=(ALL) NOPASSWD: ALL"
	@echo ""
	@echo "Please be aware of other rules or included sudoers file e.g. in /etc/sudoers.d/ directory, "
	@echo "that might conflict with the example rule above."
	@echo "You can change the sudoers file with the command 'sudo visudo'"
	@echo "Please be aware that this might increase the vulnerability of your system!"
	@echo ""
	@echo ""


# Include configuration files and generic rules
include Makeconfig
include Makerules
include Makedepends
include Makecmp
include Makedeploy


all: $(TARGET) $(COMPONENTS_DYNAMIC)

.PHONY:clean
clean:
	@echo "*** clean ***";
	rm -f *.o
	rm -f *.a
	rm -f *.so
	rm -f ../*.o
	rm -f ../*.so
	rm -f $(TARGET)
	find ../ -name *.o -exec rm {} \;
	find ../ -name *.app.cpp -exec rm {} \;
	find ../../../Components -name *.o -exec rm {} \;
	find ../../../Components__CONFIDENTIAL__ -name *.o -exec rm {} \;
	find ../../../Components__AddOns__ -name *.o -exec rm {} \;
