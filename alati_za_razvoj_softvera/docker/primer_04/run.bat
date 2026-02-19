docker stop primer04 2>nul
docker rm primer04 2>nul

docker run --name primer04 -e PREFIX="hey" -p 12345:5000 -v %cd%\data:/data  primer04
        REM ime kontejnera promenljiva okruženja          mapiranje dir-a    ime slike 