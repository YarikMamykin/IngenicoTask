function! TagIt()
  silent !clear
  silent !rm -frv tags project.files
  silent !echo "Building tags and database..."
  silent !find . -name '*.cpp' > project.files
  silent !find /usr/include/X11/ -name '*.c' -or -name '*.h' >> project.files
  silent !sed -i '/.*build.*/d' project.files
  silent !sed -i '/.*ccls.*/d' project.files
  silent !cat project.files | ctags --sort=yes --c++-kinds=+p --fields=+iaS --extras=+q --language-force=C++ -f tags -L -
  silent !echo "Done"
  redraw!
endfunction

function! Build()
  silent !clear
  silent !mkdir -p build
  !cd build && rm -frv * && cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=YES && make -j12;
  redraw!
endfunction

function! CleanBuild()
  silent !clear
  silent !mkdir -p build
  !cd build && cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=YES && make -j12;
  redraw!
endfunction

function! Run()
  silent! !clear
  !cd build/src && [ -f "IngenicoTask" ] && ./IngenicoTask;
  redraw!
endfunction

function! CleanBuildRun()
  silent !clear
  silent !mkdir -p build
  !cd build && cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=YES && make -j12 && cd ./src && [ -f "IngenicoTask" ] && ./IngenicoTask;
  redraw!
endfunction

function! SetupCcls()
  silent !cd build && rm -frv Debug compile_commands.json CMakeCache.txt CMakeFiles ccls-cache
  silent !cd build && cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=YES
  silent !ln -sf ./build/compile_commands.json .
  if !filereadable('.ccls')
    silent !echo '\%compile_commands.json' > .ccls
    silent !echo '\%h -x' >> .ccls
    silent !echo '\%h c++-header' >> .ccls
  endif
  redraw!
endfunction

command! SetupProject call TagIt() | call SetupCcls()
command! Build call Build()
command! CleanBuild call CleanBuild()
command! CleanBuildRun call CleanBuildRun()
command! Run call Run()

nmap <Leader><F4> :CleanBuild<CR>
nmap <Leader><F5> :Run<CR>
nmap <Leader><F6> :CleanBuildRun<CR>
