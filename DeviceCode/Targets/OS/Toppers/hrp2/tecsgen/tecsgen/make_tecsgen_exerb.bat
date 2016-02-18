@echo off
REM $Id: make_tecsgen_exerb.bat 2048 2014-04-28 03:14:44Z okuma-top $
REM  This file is written in SJIS.
REM  Exerb 版ジェネレータ tecsgen.exe をビルドするスクリプト
echo raccing bnf.y.rb
call racc -v tecslib/core/bnf.y.rb
echo raccing C_parser.y.rb
call racc -v tecslib/core/C_parser.y.rb
echo exerbing tecsgen.exy
call exerb tecsgen.exy
echo exerbing tecsmerge.exy
call exerb tecsmerge.exy
echo done
