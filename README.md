# Authors

- 11806764 - [Bruno Pereira Campos](brunopereira@usp.br)
- 11796378 - [João Henri Carrenho Rocha](joao.henri@usp.br)
- Coordinator: [Daniel Macedo Batista](batista@ime.usp.br)
- Coordinator: [Kifayat Ullah](kifayat@ime.usp.br)

# Executing

The SUMO Traffic Control Interface (TraCI) modules for OMNeT++ come with a small daemon to make running coupled simulations easier - the `veins_launchd` script under the `bin` folder.

Make sure to execute it from the root folder:
```bash
./bin/veins_launchd -vv -c /usr/local/bin/sumo
```

If your `sumo` executable is not under `/usr/local/bin`, check your `SUMO_HOME` and replace accordingly:
```bash
echo $SUMO_HOME
```