savedcmd_packagefilter.mod := printf '%s\n'   packagefilter.o | awk '!x[$$0]++ { print("./"$$0) }' > packagefilter.mod
