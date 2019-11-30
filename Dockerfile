FROM ubuntu:16.04
MAINTAINER bbiskup@gmx.de

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update -y -q && apt-get install -y -q \
        ccache \
        cmake cmake-curses-gui \
        cppcheck \
        dos2unix \
        doxygen \
        graphviz \
        less \
        libboost-all-dev \
        libboost-log-dev \
        locales \
        locales-all \
        software-properties-common \
        unzip \
        valgrind \
        wget \
        libncurses5-dev \
        libncursesw5-dev \
    && rm -rf /var/lib/apt/lists/*

# Install recent version of clang
WORKDIR /
ENV CLANG_VERSION=9.0.0
ENV CLANG_PACKAGE=clang+llvm-${CLANG_VERSION}-x86_64-linux-gnu-ubuntu-14.04
ENV CLANG_URL=http://releases.llvm.org/${CLANG_VERSION}/${CLANG_PACKAGE}.tar.xz
RUN echo ${CLANG_URL}
RUN wget -q ${CLANG_URL}
RUN xz -d ${CLANG_PACKAGE}.tar.xz && \
    tar xf ${CLANG_PACKAGE}.tar && \
    rm ${CLANG_PACKAGE}.tar
ENV PATH=/${CLANG_PACKAGE}/bin:$PATH
RUN ln -sf /${CLANG_PACKAGE}/bin/clang++ /usr/bin/clang++
RUN ln -sf /${CLANG_PACKAGE}/bin/clang++ /usr/bin/c++

# Install Ninja build system
RUN wget -q https://github.com/ninja-build/ninja/releases/download/v1.9.0/ninja-linux.zip; \
    unzip ninja-linux.zip; \
    mv ninja /usr/bin; \
    chmod ugo+x /usr/bin/ninja


WORKDIR /code/
COPY ./docker ./docker

RUN cat docker/bashrc_fragment >> $HOME/.bashrc
RUN rm -rf  ./docker
ENV PATH=/code:/code/scripts/:$PATH
ENV DISPLAY :0
ENTRYPOINT ["bash", "-c"]

