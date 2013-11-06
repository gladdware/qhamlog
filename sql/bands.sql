--This file is part of QHamLog
--Copyright (C) 2013 Alex Gladd
--
--QHamLog is free software: you can redistribute it and/or modify
--it under the terms of the GNU General Public License as published by
--the Free Software Foundation, either version 3 of the License, or
--(at your option) any later version.
--
--QHamLog is distributed in the hope that it will be useful,
--but WITHOUT ANY WARRANTY; without even the implied warranty of
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--GNU General Public License for more details.
--
--You should have received a copy of the GNU General Public License
--along with QHamLog.  If not, see <http://www.gnu.org/licenses/>.

--Init for bands
drop table if exists bands;
create table bands (
  id INTEGER PRIMARY KEY,
  band TEXT,
  min_freq_mhz REAL,
  max_freq_mhz REAL
  );

--Bands data
--http://adif.org/304/ADIF_304.htm#Band_Enumeration
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('2190m', .136, .137);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('630m', .472, .479);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('560m', .501, .504);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('160m', 1.8, 2.0);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('80m', 3.5, 4.0);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('60m', 5.102, 5.4065);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('40m', 7.0, 7.3);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('30m', 10.0, 10.15);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('20m', 14.0, 14.35);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('17m', 18.068, 18.168);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('15m', 21.0, 21.45);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('12m', 24.890, 24.99);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('10m', 28.0, 29.7);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('6m', 50, 54);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('4m', 70, 71);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('2m', 144, 148);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('1.25m', 222, 225);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('70cm', 420, 450);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('33cm', 902, 928);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('23cm', 1240, 1300);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('13cm', 2300, 2450);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('9cm', 3300, 3500);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('6cm', 5650, 5925);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('3cm', 10000, 10500);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('1.25cm', 24000, 24250);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('6mm', 47000, 47200);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('4mm', 75500, 81000);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('2.5mm', 119980, 120020);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('2mm', 142000, 149000);
insert into bands (band, min_freq_mhz, max_freq_mhz) values ('1mm', 241000, 250000);
