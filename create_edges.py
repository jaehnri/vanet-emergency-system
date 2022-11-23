f = open("./examples/veins/first.edg.xml", 'w')
f.write("<edges>\n")
horz = [-1, 0, 0, 1]
vert = [0, 1, -1, 0]
for i in range(6):
  for j in range(6):
    for k in range(4):
      h = horz[k]
      v = vert[k]
      if (i + h > -1) and (i + h < 6) and (j + v > -1) and (j + v < 6):
        x = i + h
        y = j + v
        f.write(f'\t<edge id="e{i}{j}-{x}{y}" from="n{i}{j}" to="n{x}{y}" numLanes="3" speed="13.89" />\n')
f.write("</edges>\n")
