FROM omnetpp/omnetpp-gui:u18.04-5.6.2
LABEL maintainer="https://github.com/brunopecampos"
WORKDIR /root
RUN wget https://github.com/eclipse/sumo/archive/refs/tags/v1_8_0.tar.gz  && tar zxf v1_8_0.tar.gz && rm v1_8_0.tar.gz
RUN apt-get update -y && apt-get install -y cmake python g++ libxerces-c-dev libfox-1.6-dev libgdal-dev libproj-dev libgl2ps-dev swig
WORKDIR /root/sumo-1_8_0
RUN export SUMO_HOME="$PWD" && mkdir build/cmake-build && cd build/cmake-build && cmake ../..  && make -j6
ENV PATH="$PATH:/root/sumo-1_8_0/bin"