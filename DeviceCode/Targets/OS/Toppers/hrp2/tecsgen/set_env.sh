#
# This shell script is not intended to execute direclty in the shell.
# Please read this file into your shell using cmmand like below.
#  % source set_env.sh
# Or you can put the contents of this file into your rc file. ex) .bashrc, .profile ... etc
#
BASEDIR=$PWD    # This line is to be changed if you put the contents into your rc file.

echo $PATH | grep "$BASEDIR/tecsgen" > /dev/null
if [ $? = 0 ]; then
	echo "PATH: unchanged !!"
else
	PATH=$BASEDIR/tecsgen:$PATH
fi
if [ "$RUBYLIB" = ""  ]; then
	export RUBYLIB=$BASEDIR/tecsgen
else
	echo "RUBYLIB: unchanged !! ($RUBYLIB)"
fi
if [ "$TECSPATH" = ""  ]; then
	export TECSPATH=$BASEDIR/tecs
else
	echo "TECSPATH: unchanged !! ($TECSPATH)"
fi

# if [ "$JSPPATH" = "" ] ; then
#   echo '$JSPPATH is required when making rpc'
# else
#   export JSPPATH
#   echo  "JSPPATH=$JSPPATH"
#   export PATH=$PWD/tecs/generator:$JSPPATH/cfg:$PATH
# fi
