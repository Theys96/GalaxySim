make:
	gcc main.c nbody.c bodies.c image.c tree.c -o nbody -O2 --pedantic -Wall -lm

clean:
	rm img/*.pbm

gif:
	convert -delay 4 -loop 0 img/*.pbm img/image.gif

movie:
	ffmpeg -y -r 25 -f image2 -i img/image%04d.pbm -vcodec libx264 -crf 25 -pix_fmt yuv420p img/image.mp4

execute:
	./nbody

all:
	make
	make clean
	make execute
	make movie
	# make gif
