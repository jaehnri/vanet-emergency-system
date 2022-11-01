#/bin/sh

python3 create_nodes.py
python3 create_edges.py
netconvert --node-files=./examples/veins/first.nod.xml \
 --edge-files=./examples/veins/first.edg.xml --output-file=./examples/veins/first.net.xml
netedit ./examples/veins/first.net.xml