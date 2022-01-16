#!/bin/sh
cd /root
rm -f backup/*.*
docker exec -t postgres_wallabag rm -f /root/db_backup.tar
rm -f ./wallabag/db_backup.tar
docker exec -t postgres_wallabag pg_dump -h 127.0.0.1 -U wallabag -f /root/db_backup.tar -F t
docker cp postgres_wallabag:/root/db_backup.tar ./wallabag/
docker exec -t postgres rm -f /root/db_backup.tar
rm -f ./photoprism/db_backup.tar
docker exec -t postgres pg_dump -h 127.0.0.1 -U photoprism -f /root/db_backup.tar -F t
docker cp postgres:/root/db_backup.tar ./photoprism/
tar -cf ./backup/postgres.tar ./postgres/
tar -cf ./backup/trilium-data.tar ./trilium-data/
tar -cf ./backup/rssreader.tar ./rssreader/
tar -cf ./backup/tg-rssbot.tar ./tg-rssbot/
tar -cf ./backup/conf.tar ./conf/
tar -cf ./backup/wallabag.tar ./wallabag/
tar -cf ./backup/photoprism.tar ./photoprism/
tar -cf ./backup/run_backup.tar ./run_backup.sh
xz -T0 ./backup/postgres.tar
xz -T0 ./backup/trilium-data.tar
xz -T0 ./backup/rssreader.tar
xz -T0 ./backup/tg-rssbot.tar
xz -T0 ./backup/conf.tar
xz -T0 ./backup/wallabag.tar
xz -T0 ./backup/photoprism.tar
xz -T0 ./backup/run_backup.tar
