set number
set expandtab
set tabstop=4
set softtabstop=4
set smarttab
set shiftwidth=4
set encoding=utf8
set autoindent
set noswapfile
set ffs=unix
set fileformat=unix
set clipboard=unnamedplus
set cursorline
set termguicolors
set bg=dark

syntax on

nnoremap <F5> :let _s=@/<Bar>:%s/\s\+$//e<Bar>:let @/=_s<Bar><CR>

let &t_SI = "\e[6 q"
let &t_EI = "\e[2 q"

inoremap " ""<left>
inoremap ' ''<left>
inoremap ( ()<left>
inoremap [ []<left>
inoremap { {}<left>

call plug#begin()
Plug 'morhetz/gruvbox'
Plug 'Yggdroot/indentLine'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'preservim/nerdtree'
call plug#end()

let g:gruvbox_italic=1

colorscheme gruvbox

nmap <F4> :NERDTree<CR>
