# Example of route <route edges="e23-33 e33-43" color="yellow" id="route_0"/>
routes = ""
for i in range(6):
  for k in range(5):
    route = "<route edges=\""
    for y in range(k, 5):
      route = route + f"e{y}{i}-{y+1}{i}"
      if y != 4:
        route = route + " "
    route = route + f"\" color=\"yellow\" id=\"route_{i*2}_{k}\"/>\n"
    routes = routes + route
   
  for k in range(5):
    route = "<route edges=\""
    for y in reversed(range(k, 5)):
      route = route + f"e{y+1}{i}-{y}{i}"
      if y != 0:
        route = route + " "
    route = route + f"\" color=\"yellow\" id=\"route_{i*2 + 1}_{k}\"/>\n"
    routes = routes + route


for i in range(6):
  for k in range(5):
    route = "<route edges=\""
    for y in range(k, 5):
      route = route + f"e{i}{y}-{i}{y+1}"
      if y != 4:
        route = route + " "
    route = route + f"\" color=\"yellow\" id=\"route_{i*2 + 12}_{k}\"/>\n"
    routes = routes + route

  for k in range(5):
    route = "<route edges=\""
    for y in reversed(range(k, 5)):
      route = route + f"e{i}{y+1}-{i}{y}"
      if y != 0:
        route = route + " "
    route = route + f"\" color=\"yellow\" id=\"route_{i*2+1 + 12}_{k}\"/>\n"
    routes = routes + route



print(routes)