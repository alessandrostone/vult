sh .travis-ocaml.sh
export OPAMYES=1
eval $(opam config env)
# installs all dependencies
opam install containers ppx_deriving ounit js_of_ocaml js_of_ocaml-ppx pla ollvm
# install LuaJIT to run the Lua tests
cd ..
git clone https://github.com/LuaJIT/LuaJIT.git
cd LuaJIT
git checkout v2.1
make
export PATH=$PATH:`pwd`/src
cd vult
# compile Vult
make all
# prepare to package
cp ./_build/src/vultc.native ./vultc
if [ $TRAVIS_OS_NAME == linux ];
then
   tar -cvzf vult-linux.tar.gz vultc runtime/vultin.h runtime/vultin.c
else
   tar -cvzf vult-osx.tar.gz vultc runtime/vultin.h runtime/vultin.c
fi
# test the instalation of vulc from npm and check it runs
npm install vult -g
vultc --help
