f = open("nodes.xml", 'w')
f.write("<nodes>\n")
for i in range(6):
  for j in range(6):
    x = i * 500.00
    y = j * 500.00
    f.write(f'\t<node id="n{i}{j}" x="{x}" y="{y}" type="traffic_light" />\n')
f.write("</nodes>\n")
