#bin/bash!

gcc -g *.c -I. -o bin/PASM &&\
    rm *.sh~ \
    *.h~  \
    *.c~
