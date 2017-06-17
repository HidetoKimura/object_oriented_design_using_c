# How to build(You need the gcc environment.)
~~~
$ git clone https://github.com/HidetoKimura/object_oriented_design_using_c.git
$ cd view_sample
$ make
gcc -g -Wall -c main.c
gcc -g -Wall -c view_class.c
gcc -g -Wall -c view_carnavi_ood

$ make clean
rm -f main.o view_class.o view_carnavi_ood.o view_sample
~~~

- If you want to build the structured design program, please change Makefile below.

~~~
Makefile 
<for Object Oriented Design>
OBJS   = main.o view_class.o view_carnavi_ood.o
#OBJS   = main.o view_class.o view_carnavi_std.o

<For Structured Design>
#OBJS   = main.o view_class.o view_carnavi_ood.o
OBJS   = main.o view_class.o view_carnavi_std.o
~~~

# How to use

- This program use the UNIX signal to emulate the user operation.
~~~
$ ./view_sample &

<<USAGE>>
HOME:
$ killall view_sample -35
BACK:
$ killall view_sample -36
NEXT:
$ killall view_sample -37
TERM:
$ killall view_sample -38
~~~
