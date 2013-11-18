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

--Init for qso log
drop table if exists qso_log;
create table qso_log (
  id INTEGER PRIMARY KEY,
  callsign TEXT not null,
  time_on_utc INTEGER not null,
  time_off_utc INTEGER,
  band TEXT not null,
  mode TEXT not null,
  submode TEXT,
  freq_mhz REAL,
  power_w REAL,
  rst_sent INTEGER,
  rst_recv INTEGER,
  city TEXT,
  country TEXT,
  primary_admin_sub TEXT,
  secondary_admin_sub TEXT,
  comments TEXT,
  qso_msg TEXT
  );
