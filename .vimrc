let $VIM_BUILD_FOLDER='build'
let $VIM_SRC_FOLDER='..'
let $COMPILE_COMMANDS_JSON='compile_commands.json'

function! LinkCompileCommands()
  silent !ln -sf $(find ./${VIM_BUILD_FOLDER}/ -name "$COMPILE_COMMANDS_JSON") ./$COMPILE_COMMANDS_JSON
  redraw!
endfunction

function! TagIt()
  silent !clear
  silent !rm -frv tags project.files
  silent !echo "Building tags and database..."
  silent !find . -name '*.cpp' > project.files
  silent !find /usr/include/X11/ -name '*.c' -or -name '*.h' >> project.files
  silent !sed -i '/.*build.*/d' project.files
  silent !sed -i '/.*ccls.*/d' project.files
  silent !cat project.files | ctags --verbose=yes --sort=yes --c++-kinds=+p --fields=+iaS --extras=+q --language-force=C++ -f tags -L -
  silent !rm -frv project.files
  silent !echo "Done"
  redraw!
endfunction

function! Build()
  silent !mkdir -p $VIM_BUILD_FOLDER
  !cd $VIM_BUILD_FOLDER && cmake $VIM_SRC_FOLDER -DCMAKE_EXPORT_COMPILE_COMMANDS=YES && make -j${CORES};
  redraw!
endfunction

function! CleanBuild()
  silent !mkdir -p $VIM_BUILD_FOLDER
  !cd $VIM_BUILD_FOLDER && rm -frv * && cmake $VIM_SRC_FOLDER -DCMAKE_EXPORT_COMPILE_COMMANDS=YES && make -j${CORES};
  redraw!
endfunction

function! Run()
  silent !clear
  !cd ./$VIM_BUILD_FOLDER/src && [ -f "IngenicoTask" ] && ./IngenicoTask;
  redraw!
endfunction

function! CleanBuildRun()
  silent !clear
  silent !mkdir -p $VIM_BUILD_FOLDER
  !cd $VIM_BUILD_FOLDER && cmake $VIM_SRC_FOLDER -DCMAKE_EXPORT_COMPILE_COMMANDS=YES && make -j${CORES} && cd ./src && [ -f "IngenicoTask" ] && ./IngenicoTask;
  redraw!
endfunction



command! SetupProject call TagIt() | call LinkCompileCommands()
command! Build call Build()
command! CleanBuild call CleanBuild()
command! CleanBuildRun call CleanBuildRun()
command! Run call Run()

nmap <F4> :SetupProject<CR>
nmap <Leader><F4> :CleanBuild<CR>
nmap <Leader><F5> :Run<CR>
nmap <Leader><F6> :CleanBuildRun<CR>
