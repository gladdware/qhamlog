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

--Init for modes
drop table if exists modes;
create table modes (
  id INTEGER PRIMARY KEY,
  mode TEXT
  );

--Modes data
--http://adif.org/304/ADIF_304.htm#Mode_Enumeration
insert into modes (mode) values ('AM');
insert into modes (mode) values ('ATV');
insert into modes (mode) values ('CHIP');
insert into modes (mode) values ('CLO');
insert into modes (mode) values ('CONTESTI');
insert into modes (mode) values ('CW');
insert into modes (mode) values ('DIGITALVOICE');
insert into modes (mode) values ('DOMINO');
insert into modes (mode) values ('DSTAR');
insert into modes (mode) values ('FAX');
insert into modes (mode) values ('FM');
insert into modes (mode) values ('FSK441');
insert into modes (mode) values ('HELL');
insert into modes (mode) values ('ISCAT');
insert into modes (mode) values ('JT4');
insert into modes (mode) values ('JT6M');
insert into modes (mode) values ('JT9');
insert into modes (mode) values ('JT44');
insert into modes (mode) values ('JT65');
insert into modes (mode) values ('MFSK');
insert into modes (mode) values ('MT63');
insert into modes (mode) values ('OLIVIA');
insert into modes (mode) values ('OPERA');
insert into modes (mode) values ('PAC');
insert into modes (mode) values ('PAX');
insert into modes (mode) values ('PKT');
insert into modes (mode) values ('PSK');
insert into modes (mode) values ('PSK2K');
insert into modes (mode) values ('Q15');
insert into modes (mode) values ('ROS');
insert into modes (mode) values ('RTTY');
insert into modes (mode) values ('RTTYM');
insert into modes (mode) values ('SSB');
insert into modes (mode) values ('SSTV');
insert into modes (mode) values ('THOR');
insert into modes (mode) values ('THRB');
insert into modes (mode) values ('TOR');
insert into modes (mode) values ('V4');
insert into modes (mode) values ('VOI');
insert into modes (mode) values ('WINMOR');
insert into modes (mode) values ('WSPR');

--Init for submodes
drop table if exists submodes;
create table submodes (
  id INTEGER PRIMARY KEY,
  submode TEXT,
  parent_mode INTEGER,
  FOREIGN KEY(parent_mode) REFERENCES modes(id)
  );

--Submodes data
--http://adif.org/304/ADIF_304.htm#Submode_Enumeration
insert into submodes (submode, parent_mode) values ('AMTORFEC', (select id from modes where mode='TOR'));
insert into submodes (submode, parent_mode) values ('ASCI', (select id from modes where mode='RTTY'));
insert into submodes (submode, parent_mode) values ('CHIP64', (select id from modes where mode='CHIP'));
insert into submodes (submode, parent_mode) values ('CHIP128', (select id from modes where mode='CHIP'));
insert into submodes (submode, parent_mode) values ('DOMINOEX', (select id from modes where mode='DOMINO'));
insert into submodes (submode, parent_mode) values ('DOMINOF', (select id from modes where mode='DOMINO'));
insert into submodes (submode, parent_mode) values ('FMHELL', (select id from modes where mode='HELL'));
insert into submodes (submode, parent_mode) values ('FSK31', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('FSKHELL', (select id from modes where mode='HELL'));
insert into submodes (submode, parent_mode) values ('GTOR', (select id from modes where mode='TOR'));
insert into submodes (submode, parent_mode) values ('HELL80', (select id from modes where mode='HELL'));
insert into submodes (submode, parent_mode) values ('HFSK', (select id from modes where mode='HELL'));
insert into submodes (submode, parent_mode) values ('ISCAT-A', (select id from modes where mode='ISCAT'));
insert into submodes (submode, parent_mode) values ('ISCAT-B', (select id from modes where mode='ISCAT'));
insert into submodes (submode, parent_mode) values ('JT4A', (select id from modes where mode='JT4'));
insert into submodes (submode, parent_mode) values ('JT4B', (select id from modes where mode='JT4'));
insert into submodes (submode, parent_mode) values ('JT4C', (select id from modes where mode='JT4'));
insert into submodes (submode, parent_mode) values ('JT4D', (select id from modes where mode='JT4'));
insert into submodes (submode, parent_mode) values ('JT4E', (select id from modes where mode='JT4'));
insert into submodes (submode, parent_mode) values ('JT4F', (select id from modes where mode='JT4'));
insert into submodes (submode, parent_mode) values ('JT4G', (select id from modes where mode='JT4'));
insert into submodes (submode, parent_mode) values ('JT9-1', (select id from modes where mode='JT9'));
insert into submodes (submode, parent_mode) values ('JT9-2', (select id from modes where mode='JT9'));
insert into submodes (submode, parent_mode) values ('JT9-5', (select id from modes where mode='JT9'));
insert into submodes (submode, parent_mode) values ('JT9-10', (select id from modes where mode='JT9'));
insert into submodes (submode, parent_mode) values ('JT9-30', (select id from modes where mode='JT9'));
insert into submodes (submode, parent_mode) values ('JT65A', (select id from modes where mode='JT65'));
insert into submodes (submode, parent_mode) values ('JT65B', (select id from modes where mode='JT65'));
insert into submodes (submode, parent_mode) values ('JT65B2', (select id from modes where mode='JT65'));
insert into submodes (submode, parent_mode) values ('JT65C', (select id from modes where mode='JT65'));
insert into submodes (submode, parent_mode) values ('JT65C2', (select id from modes where mode='JT65'));
insert into submodes (submode, parent_mode) values ('LSB', (select id from modes where mode='SSB'));
insert into submodes (submode, parent_mode) values ('MFSK4', (select id from modes where mode='MFSK'));
insert into submodes (submode, parent_mode) values ('MFSK8', (select id from modes where mode='MFSK'));
insert into submodes (submode, parent_mode) values ('MFSK11', (select id from modes where mode='MFSK'));
insert into submodes (submode, parent_mode) values ('MFSK16', (select id from modes where mode='MFSK'));
insert into submodes (submode, parent_mode) values ('MFSK22', (select id from modes where mode='MFSK'));
insert into submodes (submode, parent_mode) values ('MFSK31', (select id from modes where mode='MFSK'));
insert into submodes (submode, parent_mode) values ('MFSK32', (select id from modes where mode='MFSK'));
insert into submodes (submode, parent_mode) values ('MFSK64', (select id from modes where mode='MFSK'));
insert into submodes (submode, parent_mode) values ('MFSK128', (select id from modes where mode='MFSK'));
insert into submodes (submode, parent_mode) values ('OLIVIA 4/125', (select id from modes where mode='OLIVIA'));
insert into submodes (submode, parent_mode) values ('OLIVIA 4/250', (select id from modes where mode='OLIVIA'));
insert into submodes (submode, parent_mode) values ('OLIVIA 8/250', (select id from modes where mode='OLIVIA'));
insert into submodes (submode, parent_mode) values ('OLIVIA 8/500', (select id from modes where mode='OLIVIA'));
insert into submodes (submode, parent_mode) values ('OLIVIA 16/500', (select id from modes where mode='OLIVIA'));
insert into submodes (submode, parent_mode) values ('OLIVIA 16/1000', (select id from modes where mode='OLIVIA'));
insert into submodes (submode, parent_mode) values ('OLIVIA 32/1000', (select id from modes where mode='OLIVIA'));
insert into submodes (submode, parent_mode) values ('OPERA-BEACON', (select id from modes where mode='OPERA'));
insert into submodes (submode, parent_mode) values ('OPERA-QSO', (select id from modes where mode='OPERA'));
insert into submodes (submode, parent_mode) values ('PAC2', (select id from modes where mode='PAC'));
insert into submodes (submode, parent_mode) values ('PAC3', (select id from modes where mode='PAC'));
insert into submodes (submode, parent_mode) values ('PAC4', (select id from modes where mode='PAC'));
insert into submodes (submode, parent_mode) values ('PAX2', (select id from modes where mode='PAX'));
insert into submodes (submode, parent_mode) values ('PCW', (select id from modes where mode='CW'));
insert into submodes (submode, parent_mode) values ('PSK10', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('PSK31', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('PSK63', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('PSK63F', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('PSK125', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('PSK250', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('PSK500', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('PSK1000', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('PSKAM10', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('PSKAM31', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('PSKAM50', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('PSKFEC31', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('PSKHELL', (select id from modes where mode='HELL'));
insert into submodes (submode, parent_mode) values ('QPSK31', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('QPSK63', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('QPSK125', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('QPSK250', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('QPSK500', (select id from modes where mode='PSK'));
insert into submodes (submode, parent_mode) values ('ROS-EME', (select id from modes where mode='ROS'));
insert into submodes (submode, parent_mode) values ('ROS-HF', (select id from modes where mode='ROS'));
insert into submodes (submode, parent_mode) values ('ROS-MF', (select id from modes where mode='ROS'));
insert into submodes (submode, parent_mode) values ('THRBX', (select id from modes where mode='THRB'));
insert into submodes (submode, parent_mode) values ('USB', (select id from modes where mode='SSB'));
