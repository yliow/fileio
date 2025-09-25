
pdf:
	pdflatex --shell-escape main.tex
	pdflatex --shell-escape main.tex
	make cleantmp

view:
	xdg-open main.pdf

v:
	xdg-open main.pdf
        
plain:
	setstyle.py main.tex --style=plain
	make

fancy:
	setstyle.py main.tex --style=fancy
	make

commit:
	svn commit -m ''

s:
	make sync

sync:
	rsync -avz --delete --exclude=".svn" /home/student/svnproject/n/ /home/student/host-symlinks/360/n
	make diff

diff:
        # only works for ciss360
	diff -r -x ".svn"  . ~/host-symlinks/360/n

cleantmp:
	rm -rf abc.outut
	rm -rf 'main.log' 
	rm -rf 'main.aux'
	rm -rf 'main.toc'
	rm -rf 'main.out'
	rm -rf 'main.idx'
	rm -rf 'main.ilg'
	rm -rf 'texput.log'
	rm -rf 'shEsc.tmp'
	rm -rf 'main.vrb'
	rm -rf 'main.snm'
	rm -rf 'main.nav'
	rm -rf 'abc.output'
	rm -rf 'main.py.err'
	rm -rf 'main.py.out'
	rm -rf 'makefile.old'
	rm -rf 'auto'
	rm -rf 'desktop.ini'
	rm -rf 'main.py'
	find 'latex.py' -exec grep -q 'jobname="main"' '{}' \;  -delete

clean:
	rm -rf 'main.pdf'
	make cleantmp
        
c:
	rm -rf 'main.pdf'
	make cleantmp
    
mail:
	sendgmail --attach=main.pdf

g:
	cp *.pdf /mnt/hgfs/yliow/Google\ Drive/toprint/

