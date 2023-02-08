# About

This project is a Veins framework (v4.7.1) based emergency system. It is part of a the software system group in IME-USP

# Dependencies

It's expected omnet++ v5.6.2 and SUMO v1.8.0.

This project has a docker image in order to speed up its development. Its dockerfile is in /docker and you can download it via https://hub.docker.com/repository/docker/brunopec/veins/general

The Dockerfile requires Docker v20.10.21 or higher and x11Docker v7.4.2 or higher (to run gui interfaces in the container). x11Docker can be found here https://github.com/mviereck/x11docker

# Executing

To execute the docker image:

```bash
cd ..
x11docker -i --sudouser -- --rm -v "$(pwd):/root/models" -u "$(id -u):$(id -g)" -- brunopec/veins:v4.7.1-o5.6.2-s1.8.0
```

The project will be in the /root/models/vanet-emergency-system container directory. Omnet++ and sumo can be executed normaly in the container.

The SUMO Traffic Control Interface (TraCI) modules for OMNeT++ come with a small daemon to make running coupled simulations easier - the `veins_launchd` script under the `bin` folder.

Make sure to execute it from the root folder:

```bash
./bin/veins_launchd -vv -c sumo
```

Notice that this assumes you can execute `sumo` from anywhere. If this is not the case, check your `SUMO_HOME` variable and replace accordingly, example:

```bash
$ echo $SUMO_HOME
/usr/local/bin/sumo

# if you have sumo path set
$ ./bin/veins_launchd -vv -c sumo
# otherwise
$ ./bin/veins_launchd -vv -c /usr/local/bin/sumo
```

# Authors

- 11806764 - [Bruno Pereira Campos](brunopereira@usp.br)
- 11796378 - [João Henri Carrenho Rocha](joao.henri@usp.br)
- Coordinator: [Daniel Macedo Batista](batista@ime.usp.br)
- Coordinator: [Kifayat Ullah](kifayat@ime.usp.br)
