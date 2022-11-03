f = open("./examples/veins/first.nod.xml", 'w')
f.write("<nodes>\n")
for i in range(6):
  for j in range(6):
    x = i * 300.00
    y = j * 300.00
    if i == 3 and j == 3:
      f.write(f'\t<node id="n{i}{j}" x="{x}" y="{y}" type="traffic_light" />\n')
    else:
      f.write(f'\t<node id="n{i}{j}" x="{x}" y="{y}" />\n')
f.write("</nodes>\n")
