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

--Init for countries
drop table if exists countries;
create table countries (
  code INTEGER PRIMARY KEY,
  entity_name TEXT,
  deleted TEXT
  );

--Init for primary admin subdivision
drop table if exists primary_admin_subdivisions;
create table primary_admin_subdivisions (
  id INTEGER PRIMARY KEY,
  code TEXT,
  name TEXT,
  country_code INTEGER,
  FOREIGN KEY(country_code) REFERENCES countries(code)
  );

--Country data
--http://adif.org/304/ADIF_304.htm#Country_Codes
insert into countries (code, entity_name) values (-1, '');
insert into countries (code, entity_name) values (1, 'CANADA'); 
insert into countries (code, entity_name, deleted) values (2, 'ABU AIL IS', 'Y');
insert into countries (code, entity_name) values (3, 'AFGHANISTAN'); 
insert into countries (code, entity_name) values (4, 'AGALEGA & ST BRANDON'); 
insert into countries (code, entity_name) values (5, 'ALAND IS'); 
insert into countries (code, entity_name) values (6, 'ALASKA'); 
insert into countries (code, entity_name) values (7, 'ALBANIA'); 
insert into countries (code, entity_name, deleted) values (8, 'ALDABRA', 'Y');
insert into countries (code, entity_name) values (9, 'AMERICAN SAMOA'); 
insert into countries (code, entity_name) values (10, 'AMSTERDAM & ST PAUL'); 
insert into countries (code, entity_name) values (11, 'ANDAMAN & NICOBAR IS'); 
insert into countries (code, entity_name) values (12, 'ANGUILLA'); 
insert into countries (code, entity_name) values (13, 'ANTARCTICA'); 
insert into countries (code, entity_name) values (14, 'ARMENIA'); 
insert into countries (code, entity_name) values (15, 'ASIATIC RUSSIA'); 
insert into countries (code, entity_name) values (16, 'AUCKLAND & CAMPBELL'); 
insert into countries (code, entity_name) values (17, 'AVES ISLAND'); 
insert into countries (code, entity_name) values (18, 'AZERBAIJAN'); 
insert into countries (code, entity_name, deleted) values (19, 'BAJO NUEVO', 'Y');
insert into countries (code, entity_name) values (20, 'BAKER, HOWLAND IS'); 
insert into countries (code, entity_name) values (21, 'BALEARIC IS'); 
insert into countries (code, entity_name) values (22, 'PALAU'); 
insert into countries (code, entity_name, deleted) values (23, 'BLENHEIM REEF', 'Y');
insert into countries (code, entity_name) values (24, 'BOUVET'); 
insert into countries (code, entity_name, deleted) values (25, 'BRITISH N. BORNEO', 'Y');
insert into countries (code, entity_name, deleted) values (26, 'BRITISH SOMALI', 'Y');
insert into countries (code, entity_name) values (27, 'BELARUS'); 
insert into countries (code, entity_name, deleted) values (28, 'CANAL ZONE', 'Y');
insert into countries (code, entity_name) values (29, 'CANARY IS'); 
insert into countries (code, entity_name, deleted) values (30, 'CELEBE/MOLUCCA IS', 'Y');
insert into countries (code, entity_name) values (31, 'C KIRIBATI'); 
insert into countries (code, entity_name) values (32, 'CEUTA & MELILLA'); 
insert into countries (code, entity_name) values (33, 'CHAGOS'); 
insert into countries (code, entity_name) values (34, 'CHATHAM IS'); 
insert into countries (code, entity_name) values (35, 'CHRISTMAS IS'); 
insert into countries (code, entity_name) values (36, 'CLIPPERTON IS'); 
insert into countries (code, entity_name) values (37, 'COCOS ISLAND'); 
insert into countries (code, entity_name) values (38, 'COCOS-KEELING IS'); 
insert into countries (code, entity_name, deleted) values (39, 'COMOROS', 'Y');
insert into countries (code, entity_name) values (40, 'CRETE'); 
insert into countries (code, entity_name) values (41, 'CROZET'); 
insert into countries (code, entity_name, deleted) values (42, 'DAMAO, DUI', 'Y');
insert into countries (code, entity_name) values (43, 'DESECHEO IS'); 
insert into countries (code, entity_name, deleted) values (44, 'DESROCHES', 'Y');
insert into countries (code, entity_name) values (45, 'DODECANESE'); 
insert into countries (code, entity_name) values (46, 'EAST MALAYSIA'); 
insert into countries (code, entity_name) values (47, 'EASTER IS'); 
insert into countries (code, entity_name) values (48, 'EASTERN KIRIBATI'); 
insert into countries (code, entity_name) values (49, 'EQUATORIAL GUINEA'); 
insert into countries (code, entity_name) values (50, 'MEXICO'); 
insert into countries (code, entity_name) values (51, 'ERITREA'); 
insert into countries (code, entity_name) values (52, 'ESTONIA'); 
insert into countries (code, entity_name) values (53, 'ETHIOPIA'); 
insert into countries (code, entity_name) values (54, 'EUROPEAN RUSSIA'); 
insert into countries (code, entity_name, deleted) values (55, 'FARQUHAR', 'Y');
insert into countries (code, entity_name) values (56, 'FERNANDO DE NORONHA'); 
insert into countries (code, entity_name, deleted) values (57, 'FRENCH EQ. AFRICA', 'Y');
insert into countries (code, entity_name, deleted) values (58, 'FRENCH INDO-CHINA', 'Y');
insert into countries (code, entity_name, deleted) values (59, 'FRENCH WEST AFRICA', 'Y');
insert into countries (code, entity_name) values (60, 'BAHAMAS'); 
insert into countries (code, entity_name) values (61, 'FRANZ JOSEF LAND'); 
insert into countries (code, entity_name) values (62, 'BARBADOS'); 
insert into countries (code, entity_name) values (63, 'FRENCH GUIANA'); 
insert into countries (code, entity_name) values (64, 'BERMUDA'); 
insert into countries (code, entity_name) values (65, 'BRITISH VIRGIN IS'); 
insert into countries (code, entity_name) values (66, 'BELIZE'); 
insert into countries (code, entity_name, deleted) values (67, 'FRENCH INDIA', 'Y');
insert into countries (code, entity_name, deleted) values (68, 'SAUDI/KUWAIT N.Z.', 'Y');
insert into countries (code, entity_name) values (69, 'CAYMAN ISLANDS'); 
insert into countries (code, entity_name) values (70, 'CUBA'); 
insert into countries (code, entity_name) values (71, 'GALAPAGOS'); 
insert into countries (code, entity_name) values (72, 'DOMINICAN REPUBLIC'); 
insert into countries (code, entity_name) values (74, 'EL SALVADOR'); 
insert into countries (code, entity_name) values (75, 'GEORGIA'); 
insert into countries (code, entity_name) values (76, 'GUATEMALA'); 
insert into countries (code, entity_name) values (77, 'GRENADA'); 
insert into countries (code, entity_name) values (78, 'HAITI'); 
insert into countries (code, entity_name) values (79, 'GUADELOUPE'); 
insert into countries (code, entity_name) values (80, 'HONDURAS'); 
insert into countries (code, entity_name, deleted) values (81, 'GERMANY', 'Y');
insert into countries (code, entity_name) values (82, 'JAMAICA'); 
insert into countries (code, entity_name) values (84, 'MARTINIQUE'); 
insert into countries (code, entity_name, deleted) values (85, 'BONAIRE,CURACAO', 'Y');
insert into countries (code, entity_name) values (86, 'NICARAGUA'); 
insert into countries (code, entity_name) values (88, 'PANAMA'); 
insert into countries (code, entity_name) values (89, 'TURKS & CAICOS IS'); 
insert into countries (code, entity_name) values (90, 'TRINIDAD & TOBAGO'); 
insert into countries (code, entity_name) values (91, 'ARUBA'); 
insert into countries (code, entity_name, deleted) values (93, 'GEYSER REEF', 'Y');
insert into countries (code, entity_name) values (94, 'ANTIGUA & BARBUDA'); 
insert into countries (code, entity_name) values (95, 'DOMINICA'); 
insert into countries (code, entity_name) values (96, 'MONTSERRAT'); 
insert into countries (code, entity_name) values (97, 'ST LUCIA'); 
insert into countries (code, entity_name) values (98, 'ST VINCENT'); 
insert into countries (code, entity_name) values (99, 'GLORIOSO IS'); 
insert into countries (code, entity_name) values (100, 'ARGENTINA'); 
insert into countries (code, entity_name, deleted) values (101, 'GOA', 'Y');
insert into countries (code, entity_name, deleted) values (102, 'GOLD COAST, TOGOLAND', 'Y');
insert into countries (code, entity_name) values (103, 'GUAM'); 
insert into countries (code, entity_name) values (104, 'BOLIVIA'); 
insert into countries (code, entity_name) values (105, 'GUANTANAMO BAY'); 
insert into countries (code, entity_name) values (106, 'GUERNSEY'); 
insert into countries (code, entity_name) values (107, 'GUINEA'); 
insert into countries (code, entity_name) values (108, 'BRAZIL'); 
insert into countries (code, entity_name) values (109, 'GUINEA-BISSAU'); 
insert into countries (code, entity_name) values (110, 'HAWAII'); 
insert into countries (code, entity_name) values (111, 'HEARD IS'); 
insert into countries (code, entity_name) values (112, 'CHILE'); 
insert into countries (code, entity_name, deleted) values (113, 'IFNI', 'Y');
insert into countries (code, entity_name) values (114, 'ISLE OF MAN'); 
insert into countries (code, entity_name, deleted) values (115, 'ITALIAN SOMALI', 'Y');
insert into countries (code, entity_name) values (116, 'COLOMBIA'); 
insert into countries (code, entity_name) values (117, 'ITU HQ'); 
insert into countries (code, entity_name) values (118, 'JAN MAYEN'); 
insert into countries (code, entity_name, deleted) values (119, 'JAVA', 'Y');
insert into countries (code, entity_name) values (120, 'ECUADOR'); 
insert into countries (code, entity_name) values (122, 'JERSEY'); 
insert into countries (code, entity_name) values (123, 'JOHNSTON IS'); 
insert into countries (code, entity_name) values (124, 'JUAN DE NOVA'); 
insert into countries (code, entity_name) values (125, 'JUAN FERNANDEZ'); 
insert into countries (code, entity_name) values (126, 'KALININGRAD'); 
insert into countries (code, entity_name, deleted) values (127, 'KAMARAN IS', 'Y');
insert into countries (code, entity_name, deleted) values (128, 'KARELO-FINN REP', 'Y');
insert into countries (code, entity_name) values (129, 'GUYANA'); 
insert into countries (code, entity_name) values (130, 'KAZAKHSTAN'); 
insert into countries (code, entity_name) values (131, 'KERGUELEN'); 
insert into countries (code, entity_name) values (132, 'PARAGUAY'); 
insert into countries (code, entity_name) values (133, 'KERMADEC'); 
insert into countries (code, entity_name) values (134, 'KINGMAN REEF'); 
insert into countries (code, entity_name) values (135, 'KYRGYZSTAN'); 
insert into countries (code, entity_name) values (136, 'PERU'); 
insert into countries (code, entity_name) values (137, 'REPUBLIC OF KOREA'); 
insert into countries (code, entity_name) values (138, 'KURE ISLAND'); 
insert into countries (code, entity_name, deleted) values (139, 'KURIA MURIA IS', 'Y');
insert into countries (code, entity_name) values (140, 'SURINAME'); 
insert into countries (code, entity_name) values (141, 'FALKLAND IS'); 
insert into countries (code, entity_name) values (142, 'LAKSHADWEEP ISLANDS'); 
insert into countries (code, entity_name) values (143, 'LAOS'); 
insert into countries (code, entity_name) values (144, 'URUGUAY'); 
insert into countries (code, entity_name) values (145, 'LATVIA'); 
insert into countries (code, entity_name) values (146, 'LITHUANIA'); 
insert into countries (code, entity_name) values (147, 'LORD HOWE IS'); 
insert into countries (code, entity_name) values (148, 'VENEZUELA'); 
insert into countries (code, entity_name) values (149, 'AZORES'); 
insert into countries (code, entity_name) values (150, 'AUSTRALIA'); 
insert into countries (code, entity_name, deleted) values (151, 'MALYJ VYSOTSKIIS', 'Y');
insert into countries (code, entity_name) values (152, 'MACAO'); 
insert into countries (code, entity_name) values (153, 'MACQUARIE IS'); 
insert into countries (code, entity_name, deleted) values (154, 'YEMEN ARAB REP', 'Y');
insert into countries (code, entity_name, deleted) values (155, 'MALAYA', 'Y');
insert into countries (code, entity_name) values (157, 'NAURU'); 
insert into countries (code, entity_name) values (158, 'VANUATU'); 
insert into countries (code, entity_name) values (159, 'MALDIVES'); 
insert into countries (code, entity_name) values (160, 'TONGA'); 
insert into countries (code, entity_name) values (161, 'MALPELO IS'); 
insert into countries (code, entity_name) values (162, 'NEW CALEDONIA'); 
insert into countries (code, entity_name) values (163, 'PAPUA NEW GUINEA'); 
insert into countries (code, entity_name, deleted) values (164, 'MANCHURIA', 'Y');
insert into countries (code, entity_name) values (165, 'MAURITIUS IS'); 
insert into countries (code, entity_name) values (166, 'MARIANA IS'); 
insert into countries (code, entity_name) values (167, 'MARKET REEF'); 
insert into countries (code, entity_name) values (168, 'MARSHALL IS'); 
insert into countries (code, entity_name) values (169, 'MAYOTTE'); 
insert into countries (code, entity_name) values (170, 'NEW ZEALAND'); 
insert into countries (code, entity_name) values (171, 'MELLISH REEF'); 
insert into countries (code, entity_name) values (172, 'PITCAIRN IS'); 
insert into countries (code, entity_name) values (173, 'MICRONESIA'); 
insert into countries (code, entity_name) values (174, 'MIDWAY IS'); 
insert into countries (code, entity_name) values (175, 'FRENCH POLYNESIA'); 
insert into countries (code, entity_name) values (176, 'FIJI'); 
insert into countries (code, entity_name) values (177, 'MINAMI TORISHIMA'); 
insert into countries (code, entity_name, deleted) values (178, 'MINERVA REEF', 'Y');
insert into countries (code, entity_name) values (179, 'MOLDOVA'); 
insert into countries (code, entity_name) values (180, 'MOUNT ATHOS'); 
insert into countries (code, entity_name) values (181, 'MOZAMBIQUE'); 
insert into countries (code, entity_name) values (182, 'NAVASSA IS'); 
insert into countries (code, entity_name, deleted) values (183, 'NETHERLANDS BORNEO', 'Y');
insert into countries (code, entity_name, deleted) values (184, 'NETHERLANDS N GUINEA', 'Y');
insert into countries (code, entity_name) values (185, 'SOLOMON ISLANDS'); 
insert into countries (code, entity_name, deleted) values (186, 'NEWFOUNDLAND, LABRADOR', 'Y');
insert into countries (code, entity_name) values (187, 'NIGER'); 
insert into countries (code, entity_name) values (188, 'NIUE'); 
insert into countries (code, entity_name) values (189, 'NORFOLK IS'); 
insert into countries (code, entity_name) values (190, 'SAMOA'); 
insert into countries (code, entity_name) values (191, 'N COOK IS'); 
insert into countries (code, entity_name) values (192, 'OGASAWARA'); 
insert into countries (code, entity_name, deleted) values (193, 'OKINAWA', 'Y');
insert into countries (code, entity_name, deleted) values (194, 'OKINO TORI-SHIMA', 'Y');
insert into countries (code, entity_name) values (195, 'ANNOBON I.'); 
insert into countries (code, entity_name, deleted) values (196, 'PALESTINE', 'Y');
insert into countries (code, entity_name) values (197, 'PALMYRA & JARVIS IS'); 
insert into countries (code, entity_name, deleted) values (198, 'PAPUA TERR', 'Y');
insert into countries (code, entity_name) values (199, 'PETER I IS'); 
insert into countries (code, entity_name, deleted) values (200, 'PORTUGUESE TIMOR', 'Y');
insert into countries (code, entity_name) values (201, 'PRINCE EDWARD & MARION'); 
insert into countries (code, entity_name) values (202, 'PUERTO RICO'); 
insert into countries (code, entity_name) values (203, 'ANDORRA'); 
insert into countries (code, entity_name) values (204, 'REVILLAGIGEDO'); 
insert into countries (code, entity_name) values (205, 'ASCENSION ISLAND'); 
insert into countries (code, entity_name) values (206, 'AUSTRIA'); 
insert into countries (code, entity_name) values (207, 'RODRIGUEZ IS'); 
insert into countries (code, entity_name, deleted) values (208, 'RUANDA-URUNDI', 'Y');
insert into countries (code, entity_name) values (209, 'BELGIUM'); 
insert into countries (code, entity_name, deleted) values (210, 'SAAR', 'Y');
insert into countries (code, entity_name) values (211, 'SABLE ISLAND'); 
insert into countries (code, entity_name) values (212, 'BULGARIA'); 
insert into countries (code, entity_name) values (213, 'SAINT MARTIN'); 
insert into countries (code, entity_name) values (214, 'CORSICA'); 
insert into countries (code, entity_name) values (215, 'CYPRUS'); 
insert into countries (code, entity_name) values (216, 'SAN ANDRES & PROVIDENCIA'); 
insert into countries (code, entity_name) values (217, 'SAN FELIX'); 
insert into countries (code, entity_name, deleted) values (218, 'CZECHOSLOVAKIA', 'Y');
insert into countries (code, entity_name) values (219, 'SAO TOME & PRINCIPE'); 
insert into countries (code, entity_name, deleted) values (220, 'SARAWAK', 'Y');
insert into countries (code, entity_name) values (221, 'DENMARK'); 
insert into countries (code, entity_name) values (222, 'FAROE IS'); 
insert into countries (code, entity_name) values (223, 'ENGLAND'); 
insert into countries (code, entity_name) values (224, 'FINLAND'); 
insert into countries (code, entity_name) values (225, 'SARDINIA'); 
insert into countries (code, entity_name, deleted) values (226, 'SAUDI/IRAQ N.Z.', 'Y');
insert into countries (code, entity_name) values (227, 'FRANCE'); 
insert into countries (code, entity_name, deleted) values (228, 'SERRANA BANK & RONCADOR CAY', 'Y');
insert into countries (code, entity_name, deleted) values (229, 'GERMAN DEM. REP.', 'Y');
insert into countries (code, entity_name) values (230, 'FED REP OF GERMANY'); 
insert into countries (code, entity_name, deleted) values (231, 'SIKKIM', 'Y');
insert into countries (code, entity_name) values (232, 'SOMALIA'); 
insert into countries (code, entity_name) values (233, 'GIBRALTAR'); 
insert into countries (code, entity_name) values (234, 'S COOK IS'); 
insert into countries (code, entity_name) values (235, 'SOUTH GEORGIA IS'); 
insert into countries (code, entity_name) values (236, 'GREECE'); 
insert into countries (code, entity_name) values (237, 'GREENLAND'); 
insert into countries (code, entity_name) values (238, 'SOUTH ORKNEY IS'); 
insert into countries (code, entity_name) values (239, 'HUNGARY'); 
insert into countries (code, entity_name) values (240, 'SOUTH SANDWICH ISLANDS'); 
insert into countries (code, entity_name) values (241, 'SOUTH SHETLAND ISLANDS'); 
insert into countries (code, entity_name) values (242, 'ICELAND'); 
insert into countries (code, entity_name, deleted) values (243, 'DEM REP OF YEMEN', 'Y');
insert into countries (code, entity_name, deleted) values (244, 'SOUTHERN SUDAN', 'Y');
insert into countries (code, entity_name) values (245, 'IRELAND'); 
insert into countries (code, entity_name) values (246, 'SOV MILITARY ORDER OF MALTA'); 
insert into countries (code, entity_name) values (247, 'SPRATLY IS'); 
insert into countries (code, entity_name) values (248, 'ITALY'); 
insert into countries (code, entity_name) values (249, 'ST KITTS & NEVIS'); 
insert into countries (code, entity_name) values (250, 'ST HELENA IS'); 
insert into countries (code, entity_name) values (251, 'LIECHTENSTEIN'); 
insert into countries (code, entity_name) values (252, 'ST PAUL ISLAND'); 
insert into countries (code, entity_name) values (253, 'ST. PETER & ST. PAUL ROCKS'); 
insert into countries (code, entity_name) values (254, 'LUXEMBOURG'); 
insert into countries (code, entity_name, deleted) values (255, 'SINT MAARTEN, SABA, ST EUSTATIUS', 'Y');
insert into countries (code, entity_name) values (256, 'MADEIRA IS'); 
insert into countries (code, entity_name) values (257, 'MALTA'); 
insert into countries (code, entity_name, deleted) values (258, 'SUMATRA', 'Y');
insert into countries (code, entity_name) values (259, 'SVALBARD IS'); 
insert into countries (code, entity_name) values (260, 'MONACO'); 
insert into countries (code, entity_name, deleted) values (261, 'SWAN ISLAND', 'Y');
insert into countries (code, entity_name) values (262, 'TAJIKISTAN'); 
insert into countries (code, entity_name) values (263, 'NETHERLANDS'); 
insert into countries (code, entity_name, deleted) values (264, 'TANGIER', 'Y');
insert into countries (code, entity_name) values (265, 'NORTHERN IRELAND'); 
insert into countries (code, entity_name) values (266, 'NORWAY'); 
insert into countries (code, entity_name, deleted) values (267, 'TERR NEW GUINEA', 'Y');
insert into countries (code, entity_name, deleted) values (268, 'TIBET', 'Y');
insert into countries (code, entity_name) values (269, 'POLAND'); 
insert into countries (code, entity_name) values (270, 'TOKELAU IS'); 
insert into countries (code, entity_name, deleted) values (271, 'TRIESTE', 'Y');
insert into countries (code, entity_name) values (272, 'PORTUGAL'); 
insert into countries (code, entity_name) values (273, 'TRINDADE & MARTIN VAZ ISLANDS'); 
insert into countries (code, entity_name) values (274, 'TRISTAN DA CUNHA & GOUGH IS'); 
insert into countries (code, entity_name) values (275, 'ROMANIA'); 
insert into countries (code, entity_name) values (276, 'TROMELIN'); 
insert into countries (code, entity_name) values (277, 'ST PIERRE & MIQUELON'); 
insert into countries (code, entity_name) values (278, 'SAN MARINO'); 
insert into countries (code, entity_name) values (279, 'SCOTLAND'); 
insert into countries (code, entity_name) values (280, 'TURKMENISTAN'); 
insert into countries (code, entity_name) values (281, 'SPAIN'); 
insert into countries (code, entity_name) values (282, 'TUVALU'); 
insert into countries (code, entity_name) values (283, 'UK BASES ON CYPRUS'); 
insert into countries (code, entity_name) values (284, 'SWEDEN'); 
insert into countries (code, entity_name) values (285, 'US VIRGIN ISLANDS'); 
insert into countries (code, entity_name) values (286, 'UGANDA'); 
insert into countries (code, entity_name) values (287, 'SWITZERLAND'); 
insert into countries (code, entity_name) values (288, 'UKRAINE'); 
insert into countries (code, entity_name) values (289, 'UNITED NATIONS HQ'); 
insert into countries (code, entity_name) values (291, 'UNITED STATES'); 
insert into countries (code, entity_name) values (292, 'UZBEKISTAN'); 
insert into countries (code, entity_name) values (293, 'VIETNAM'); 
insert into countries (code, entity_name) values (294, 'WALES'); 
insert into countries (code, entity_name) values (295, 'VATICAN'); 
insert into countries (code, entity_name) values (296, 'SERBIA'); 
insert into countries (code, entity_name) values (297, 'WAKE IS'); 
insert into countries (code, entity_name) values (298, 'WALLIS & FUTUNA'); 
insert into countries (code, entity_name) values (299, 'WEST MALAYSIA'); 
insert into countries (code, entity_name) values (301, 'W KIRIBATI'); 
insert into countries (code, entity_name) values (302, 'WESTERN SAHARA'); 
insert into countries (code, entity_name) values (303, 'WILLIS IS'); 
insert into countries (code, entity_name) values (304, 'BAHRAIN'); 
insert into countries (code, entity_name) values (305, 'BANGLADESH'); 
insert into countries (code, entity_name) values (306, 'BHUTAN'); 
insert into countries (code, entity_name, deleted) values (307, 'ZANZIBAR', 'Y');
insert into countries (code, entity_name) values (308, 'COSTA RICA'); 
insert into countries (code, entity_name) values (309, 'MYANMAR'); 
insert into countries (code, entity_name) values (312, 'CAMBODIA'); 
insert into countries (code, entity_name) values (315, 'SRI LANKA'); 
insert into countries (code, entity_name) values (318, 'CHINA'); 
insert into countries (code, entity_name) values (321, 'HONG KONG'); 
insert into countries (code, entity_name) values (324, 'INDIA'); 
insert into countries (code, entity_name) values (327, 'INDONESIA'); 
insert into countries (code, entity_name) values (330, 'IRAN'); 
insert into countries (code, entity_name) values (333, 'IRAQ'); 
insert into countries (code, entity_name) values (336, 'ISRAEL'); 
insert into countries (code, entity_name) values (339, 'JAPAN'); 
insert into countries (code, entity_name) values (342, 'JORDAN'); 
insert into countries (code, entity_name) values (344, 'DEMOCRATIC PEOPLE''S REPUBLIC OF KOREA'); 
insert into countries (code, entity_name) values (345, 'BRUNEI'); 
insert into countries (code, entity_name) values (348, 'KUWAIT'); 
insert into countries (code, entity_name) values (354, 'LEBANON'); 
insert into countries (code, entity_name) values (363, 'MONGOLIA'); 
insert into countries (code, entity_name) values (369, 'NEPAL'); 
insert into countries (code, entity_name) values (370, 'OMAN'); 
insert into countries (code, entity_name) values (372, 'PAKISTAN'); 
insert into countries (code, entity_name) values (375, 'PHILIPPINES'); 
insert into countries (code, entity_name) values (376, 'QATAR'); 
insert into countries (code, entity_name) values (378, 'SAUDI ARABIA'); 
insert into countries (code, entity_name) values (379, 'SEYCHELLES'); 
insert into countries (code, entity_name) values (381, 'SINGAPORE'); 
insert into countries (code, entity_name) values (382, 'DJIBOUTI'); 
insert into countries (code, entity_name) values (384, 'SYRIA'); 
insert into countries (code, entity_name) values (386, 'TAIWAN'); 
insert into countries (code, entity_name) values (387, 'THAILAND'); 
insert into countries (code, entity_name) values (390, 'TURKEY'); 
insert into countries (code, entity_name) values (391, 'UNITED ARAB EMIRATES'); 
insert into countries (code, entity_name) values (400, 'ALGERIA'); 
insert into countries (code, entity_name) values (401, 'ANGOLA'); 
insert into countries (code, entity_name) values (402, 'BOTSWANA'); 
insert into countries (code, entity_name) values (404, 'BURUNDI'); 
insert into countries (code, entity_name) values (406, 'CAMEROON'); 
insert into countries (code, entity_name) values (408, 'CENTRAL AFRICAN REPUBLIC'); 
insert into countries (code, entity_name) values (409, 'CAPE VERDE'); 
insert into countries (code, entity_name) values (410, 'CHAD'); 
insert into countries (code, entity_name) values (411, 'COMOROS'); 
insert into countries (code, entity_name) values (412, 'REPUBLIC OF THE CONGO'); 
insert into countries (code, entity_name) values (414, 'DEM. REPUBLIC OF THE CONGO'); 
insert into countries (code, entity_name) values (416, 'BENIN'); 
insert into countries (code, entity_name) values (420, 'GABON'); 
insert into countries (code, entity_name) values (422, 'THE GAMBIA'); 
insert into countries (code, entity_name) values (424, 'GHANA'); 
insert into countries (code, entity_name) values (428, 'COTE D''IVOIRE'); 
insert into countries (code, entity_name) values (430, 'KENYA'); 
insert into countries (code, entity_name) values (432, 'LESOTHO'); 
insert into countries (code, entity_name) values (434, 'LIBERIA'); 
insert into countries (code, entity_name) values (436, 'LIBYA'); 
insert into countries (code, entity_name) values (438, 'MADAGASCAR'); 
insert into countries (code, entity_name) values (440, 'MALAWI'); 
insert into countries (code, entity_name) values (442, 'MALI'); 
insert into countries (code, entity_name) values (444, 'MAURITANIA'); 
insert into countries (code, entity_name) values (446, 'MOROCCO'); 
insert into countries (code, entity_name) values (450, 'NIGERIA'); 
insert into countries (code, entity_name) values (452, 'ZIMBABWE'); 
insert into countries (code, entity_name) values (453, 'REUNION'); 
insert into countries (code, entity_name) values (454, 'RWANDA'); 
insert into countries (code, entity_name) values (456, 'SENEGAL'); 
insert into countries (code, entity_name) values (458, 'SIERRA LEONE'); 
insert into countries (code, entity_name) values (460, 'ROTUMA IS'); 
insert into countries (code, entity_name) values (462, 'REPUBLIC OF SOUTH AFRICA'); 
insert into countries (code, entity_name) values (464, 'NAMIBIA'); 
insert into countries (code, entity_name) values (466, 'SUDAN'); 
insert into countries (code, entity_name) values (468, 'SWAZILAND'); 
insert into countries (code, entity_name) values (470, 'TANZANIA'); 
insert into countries (code, entity_name) values (474, 'TUNISIA'); 
insert into countries (code, entity_name) values (478, 'EGYPT'); 
insert into countries (code, entity_name) values (480, 'BURKINA-FASO'); 
insert into countries (code, entity_name) values (482, 'ZAMBIA'); 
insert into countries (code, entity_name) values (483, 'TOGO'); 
insert into countries (code, entity_name, deleted) values (488, 'WALVIS BAY', 'Y');
insert into countries (code, entity_name) values (489, 'CONWAY REEF'); 
insert into countries (code, entity_name) values (490, 'BANABA ISLAND'); 
insert into countries (code, entity_name) values (492, 'YEMEN'); 
insert into countries (code, entity_name, deleted) values (493, 'PENGUIN ISLANDS', 'Y');
insert into countries (code, entity_name) values (497, 'CROATIA'); 
insert into countries (code, entity_name) values (499, 'SLOVENIA'); 
insert into countries (code, entity_name) values (501, 'BOSNIA-HERZEGOVINA'); 
insert into countries (code, entity_name) values (502, 'MACEDONIA'); 
insert into countries (code, entity_name) values (503, 'CZECH REPUBLIC'); 
insert into countries (code, entity_name) values (504, 'SLOVAK REPUBLIC'); 
insert into countries (code, entity_name) values (505, 'PRATAS IS'); 
insert into countries (code, entity_name) values (506, 'SCARBOROUGH REEF'); 
insert into countries (code, entity_name) values (507, 'TEMOTU PROVINCE'); 
insert into countries (code, entity_name) values (508, 'AUSTRAL IS'); 
insert into countries (code, entity_name) values (509, 'MARQUESAS IS'); 
insert into countries (code, entity_name) values (510, 'PALESTINE'); 
insert into countries (code, entity_name) values (511, 'TIMOR-LESTE'); 
insert into countries (code, entity_name) values (512, 'CHESTERFIELD IS'); 
insert into countries (code, entity_name) values (513, 'DUCIE IS'); 
insert into countries (code, entity_name) values (514, 'MONTENEGRO'); 
insert into countries (code, entity_name) values (515, 'SWAINS ISLAND'); 
insert into countries (code, entity_name) values (516, 'ST. BARTHELEMY'); 
insert into countries (code, entity_name) values (517, 'CURACAO'); 
insert into countries (code, entity_name) values (518, 'SINT MAARTEN'); 
insert into countries (code, entity_name) values (519, 'ST EUSTATIUS AND SABA'); 
insert into countries (code, entity_name) values (520, 'BONAIRE'); 
insert into countries (code, entity_name) values (521, 'SOUTH SUDAN');

--Primary Admin Subdivision data
--http://adif.org/304/ADIF_304.htm#Primary_Administrative_Subdivisions
insert into primary_admin_subdivisions (code, name, country_code) values ('AK', 'Alaska', 6);
insert into primary_admin_subdivisions (code, name, country_code) values ('HI', 'Hawaii', 110);
insert into primary_admin_subdivisions (code, name, country_code) values ('CT', 'Connecticut', 291); --05	08	W1
insert into primary_admin_subdivisions (code, name, country_code) values ('ME', 'Maine', 291); --05	08	W1
insert into primary_admin_subdivisions (code, name, country_code) values ('MA', 'Massachusetts', 291); --05	08	W1
insert into primary_admin_subdivisions (code, name, country_code) values ('NH', 'New Hampshire', 291); --05	08	W1
insert into primary_admin_subdivisions (code, name, country_code) values ('RI', 'Rhode Island', 291); --05	08	W1
insert into primary_admin_subdivisions (code, name, country_code) values ('VT', 'Vermont', 291); --05	08	W1
insert into primary_admin_subdivisions (code, name, country_code) values ('NJ', 'New Jersey', 291); --05	08	W2
insert into primary_admin_subdivisions (code, name, country_code) values ('NY', 'New York', 291); --05	08	W2
insert into primary_admin_subdivisions (code, name, country_code) values ('DE', 'Delaware', 291); --05	08	W3
insert into primary_admin_subdivisions (code, name, country_code) values ('DC', 'District of Columbia', 291); --05	08	W3
insert into primary_admin_subdivisions (code, name, country_code) values ('MD', 'Maryland', 291); --05	08	W3
insert into primary_admin_subdivisions (code, name, country_code) values ('PA', 'Pennsylvania', 291); --05	08	W3
insert into primary_admin_subdivisions (code, name, country_code) values ('AL', 'Alabama', 291); --04	08	W4
insert into primary_admin_subdivisions (code, name, country_code) values ('FL', 'Florida', 291); --05	08	W4
insert into primary_admin_subdivisions (code, name, country_code) values ('GA', 'Georgia', 291); --05	08	W4
insert into primary_admin_subdivisions (code, name, country_code) values ('KY', 'Kentucky', 291); --04	08	W4
insert into primary_admin_subdivisions (code, name, country_code) values ('NC', 'North Carolina', 291); --04	08	W4
insert into primary_admin_subdivisions (code, name, country_code) values ('SC', 'South Carolina', 291); --05	08	W4
insert into primary_admin_subdivisions (code, name, country_code) values ('TN', 'Tennessee', 291); --04	07/08	W4
insert into primary_admin_subdivisions (code, name, country_code) values ('VA', 'Virginia', 291); --05	08	W4
insert into primary_admin_subdivisions (code, name, country_code) values ('AR', 'Arkansas', 291); --04	07/08	W5
insert into primary_admin_subdivisions (code, name, country_code) values ('LA', 'Louisiana', 291); --04	07/08	W5
insert into primary_admin_subdivisions (code, name, country_code) values ('MS', 'Mississippi', 291); --04	07/08	W5
insert into primary_admin_subdivisions (code, name, country_code) values ('NM', 'New Mexico', 291); --04	07	W5
insert into primary_admin_subdivisions (code, name, country_code) values ('OK', 'Oklahoma', 291); --04	07	W5
insert into primary_admin_subdivisions (code, name, country_code) values ('TX', 'Texas', 291); --04	07	W5
insert into primary_admin_subdivisions (code, name, country_code) values ('CA', 'California', 291); --03	06	W6
insert into primary_admin_subdivisions (code, name, country_code) values ('AZ', 'Arizona', 291); --03	06/07	W7
insert into primary_admin_subdivisions (code, name, country_code) values ('ID', 'Idaho', 291); --03	06	W7
insert into primary_admin_subdivisions (code, name, country_code) values ('MT', 'Montana', 291); --04	06/07	W7
insert into primary_admin_subdivisions (code, name, country_code) values ('NV', 'Nevada', 291); --03	06	W7
insert into primary_admin_subdivisions (code, name, country_code) values ('OR', 'Oregon', 291); --03	06	W7
insert into primary_admin_subdivisions (code, name, country_code) values ('UT', 'Utah', 291); --03	06/07	W7
insert into primary_admin_subdivisions (code, name, country_code) values ('WA', 'Washington', 291); --03	06	W7
insert into primary_admin_subdivisions (code, name, country_code) values ('WY', 'Wyoming', 291); --04	07	W7
insert into primary_admin_subdivisions (code, name, country_code) values ('MI', 'Michigan', 291); --04	07/08	W8
insert into primary_admin_subdivisions (code, name, country_code) values ('OH', 'Ohio', 291); --04	08	W8
insert into primary_admin_subdivisions (code, name, country_code) values ('WV', 'West Virginia', 291); --05	08	W8
insert into primary_admin_subdivisions (code, name, country_code) values ('IL', 'Illinois', 291); --04	07/08	W9
insert into primary_admin_subdivisions (code, name, country_code) values ('IN', 'Indiana', 291); --04	08	W9
insert into primary_admin_subdivisions (code, name, country_code) values ('WI', 'Wisconsin', 291); --04	07/08	W9
insert into primary_admin_subdivisions (code, name, country_code) values ('CO', 'Colorado', 291); --04	07	W0
insert into primary_admin_subdivisions (code, name, country_code) values ('IA', 'Iowa', 291); --04	07	W0
insert into primary_admin_subdivisions (code, name, country_code) values ('KS', 'Kansas', 291); --04	07	W0
insert into primary_admin_subdivisions (code, name, country_code) values ('MN', 'Minnesota', 291); --04	07	W0
insert into primary_admin_subdivisions (code, name, country_code) values ('MO', 'Missouri', 291); --04	07/08	W0
insert into primary_admin_subdivisions (code, name, country_code) values ('NE', 'Nebraska', 291); --04	07	W0
insert into primary_admin_subdivisions (code, name, country_code) values ('ND', 'North Dakota', 291); --04	07	W0
insert into primary_admin_subdivisions (code, name, country_code) values ('SD', 'South Dakota', 291); --04	07	W0
