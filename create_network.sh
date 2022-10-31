#/bin/sh

python3 create_nodes.py
python3 create_edges.py
netconvert --node-files=nodes.xml --edge-files=edges.xml --output-file=$PWD/examples/veins/first.net.xml
netedit ./examples/veins/first.net.xml