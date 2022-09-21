# Authors

- 11806764 - [Bruno Pereira Campos](brunopereira@usp.br)
- 11796378 - [João Henri Carrenho Rocha](joao.henri@usp.br)
- Coordinator: [Daniel Macedo Batista](batista@ime.usp.br)
- Coordinator: [Kifayat Ullah](kifayat@ime.usp.br)

# Executing

The SUMO Traffic Control Interface (TraCI) modules for OMNeT++ come with a small daemon to make running coupled simulations easier - the `veins_launchd` script under the `bin` folder.

Make sure to execute it from the root folder:
```bash
./bin/veins_launchd -vv -c sumo
```

Notice that this assumes you can execute `sumo` from anywhere. If this is not the case, check your `SUMO_HOME` variable and replace accordingly, example:
```bash
$ echo $SUMO_HOME
/usr/local/bin/sumo

$ ./bin/veins_launchd -vv -c /usr/local/bin/sumo
```
