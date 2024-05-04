select sum(energy)/count(1) from songs where artist_id = (select id from artists where name = 'Drake');
