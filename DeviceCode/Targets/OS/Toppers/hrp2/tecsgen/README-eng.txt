TECS

  TECS - Toppers Embedded Component System -

  TECS is designed by TECS WG of NPO TOPPERS Project.

README

  This file explains preparation and invocation of TECS generator
  'tecsgen'.

Condition

  You may use TECS under the TOPPERS License which is described in
  each source file. But The TECS specification is distributed under
  the different license.

  Some files are distributed under other licenses. Please see each
  file header part.

Bug report

  If you find a bug or any problem, please let us know by sending
  e-mail. The address is com-wg@toppers.jp (if you are member of
  TOPPERS project) or users@toppers.jp.

  Note: before sending e-mail you have to participate ML.

    URL  http://www.toppers.jp/en/community.html

Preparation

  TECS generator is implemented using Ruby. So you have to install
  Ruby interpreter. But if you use exerb version of tecsgen on Windows
  based system, installing ruby is unnecessary.  platform on which
  tecsgen run

  We checked tecsgen on the platforms listed below.

    cygwin on Windows based systems
    MacOS X
    Linux (Ubuntu, Fedora)
    Command Prompt on Windows based systems (exerb version) 

Install Ruby

On fedora 12

  On fedora 12, you can download and install Ruby interpreter by
  following command.

  # yum install ruby ruby-devel ri

  Ruby 1.8.* is necessary. On later version of Ruby (1.9), tecsgen
  doesn't work.

Install Racc

  Racc is parser generator for Ruby programmer. It is like Yacc for C
  programmer.

  In cases below, it is not necessary to install Racc.

  - if you use exerb version of tecsgen
  - if ruby package you installed includes racc
  - if you use latest version of tecsgen and you don't want to
    regenerate parser because latest version of tecsgen includes the
    result of Racc generated parser.

     download URL  http://i.loveruby.net/archive/racc/racc-1.4.5-all.tar.gz 

  extract & setup 

  % tar xvzf racc-1.4.5-all.tar.gz
  % su               # this step is not necessary on cygwin environment.
  # cd racc-1.4.5-all
  # ruby setup.rb

Install tecsgen

  You can get TECS generator from svn repository (TOPPERS member only)
  or package from TECS homepage in TOPPERS project's HP.  setting
  Environment Variable

  At least PATH and RUBYLIB are necessary to be set. For PATH, add the
  path where tecsgen is placed. For RUBYLIB, set the path where
  tecslib is placed.

  set_env.sh sets the environment variables. Please read it into your
  shell by the command like below.

  %  source set_env.sh

    When doing this, you have to change current directory where
    set_env.sh is placed.

  You might need to set TECSGEN_LANG environment variable.

  export TECSGEN_LANG=en_US.ISO8859-1

To invoke tecsgen, type like below.

  % tecsgen hello.cdl

  You will need add some options -I, -D, etc.
  You can see brief help by the command below.

  % tecsgen --help
