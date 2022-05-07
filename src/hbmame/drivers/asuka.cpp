// Proyecto Shadows Arcade Classic+
// copyright-holders:Gaston90
#include "../mame/drivers/asuka.cpp"

/*************
 Asuka & Asuka
***************/

ROM_START( asukac )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "b68-13c.ic23", 0x00000, 0x20000, CRC(356a3151) SHA1(a2929a30bcd45962a4fc08a980e82d9914078c29) )
	ROM_LOAD16_BYTE( "b68-12c.ic8",  0x00001, 0x20000, CRC(8bd073d4) SHA1(53453cb0dd4aa606215922ad8363e536524dc0f3) )
	ROM_LOAD16_WORD( "b68-03c.ic30", 0x80000, 0x80000, CRC(3d0d7798) SHA1(a63d9fc043e8ba0b79a7606c17faac406e0b92ec) )

	ROM_REGION( 0x80000, "tc0100scn", 0 )
	ROM_LOAD16_WORD_SWAP( "b68-01c.ic3",  0x00000, 0x80000, CRC(d5dec087) SHA1(1f8888c15cb08c1c0d27ce29cb71106360c9c852) )

	ROM_REGION( 0xa0000, "pc090oj", 0 )
	ROM_LOAD16_WORD_SWAP( "b68-02c.ic6", 0x00000, 0x80000, CRC(09927d23) SHA1(b9761286feaa14c4eb6fc87ec35e7245c318d687) )
	ROM_LOAD16_BYTE( "b68-07.ic5", 0x80000, 0x10000, CRC(c113acc8) SHA1(613c61a78df73dcb0b9c9018ae829e865baac772) )
	ROM_LOAD16_BYTE( "b68-06.ic4", 0x80001, 0x10000, CRC(f517e64d) SHA1(8be491bfe0f7eed58521de9d31da677acf635c23) )

	ROM_REGION( 0x1c000, "audiocpu", 0 )
	ROM_LOAD( "b68-11.ic27", 0x00000, 0x04000, CRC(c378b508) SHA1(1b145fe736b924f298e02532cf9f26cc18b42ca7) )
	ROM_CONTINUE(            0x10000, 0x0c000 )

	ROM_REGION( 0x10000, "msm", 0 )
	ROM_LOAD( "b68-10.ic24", 0x00000, 0x10000, CRC(387aaf40) SHA1(47c583564ef1d49ece15f97221b2e073e8fb0544) )

	ROM_REGION( 0x144, "pals", 0 )
	ROM_LOAD( "b68-04.ic32", 0x00000, 0x144, CRC(9be618d1) SHA1(61ee33c3db448a05ff8f455e77fe17d51106baec) )
	ROM_LOAD( "b68-05.ic43", 0x00000, 0x104, CRC(d6524ccc) SHA1(f3b56253692aebb63278d47832fc27b8b212b59c) )
ROM_END

/*************
 Jigoku Meguri
***************/

ROM_START( jigkmgrihack01 ) //jigkmgria
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "b41-09-1_hack01.17", 0x00000, 0x10000, CRC(5d3a5283) SHA1(8c4804569f5e55ecef7a0ac83292ba4153dbf2a4) )
	ROM_LOAD16_BYTE( "b41-11-1_hack01.26", 0x00001, 0x10000, CRC(e1f2f205) SHA1(ba1184107ac4e4558fbfb75d6bbf983168705769) )
	ROM_LOAD16_BYTE( "b41-10.16",   0x20000, 0x10000, CRC(4ca94d77) SHA1(69a9f6bcb6d5e4132eed50860bdfe8d6b6d914cd) )
	ROM_LOAD16_BYTE( "b41-12.25",   0x20001, 0x10000, CRC(40d9c1fc) SHA1(6f03d263e10559988aaa2be00d9bbf55f2fb864e) )
	ROM_LOAD16_WORD_SWAP( "b41-01.15", 0x80000, 0x80000, CRC(5d072fa4) SHA1(6ffe1b8531381eb6dd3f1fec18c91294a6aca9f6) )

	ROM_REGION( 0x2000, "cchip:cchip_eprom", 0 )
	ROM_LOAD( "cchip_b41-05.43", 0x0000, 0x2000, CRC(75c52553) SHA1(87bbaefab90e7d43f63556fbae3e937baf9d397b) )

	ROM_REGION( 0x80000, "tc0100scn", 0 )
	ROM_LOAD16_WORD_SWAP( "b41-03.1",  0x00000, 0x80000, CRC(736d35d0) SHA1(7d41a7d71e117714bbd2cdda2953589cda6e763a) )

	ROM_REGION( 0x80000, "pc090oj", 0 )
	ROM_LOAD16_WORD_SWAP( "b41-02.7",  0x00000, 0x80000, CRC(29f205d9) SHA1(9e9f0c2755a9aa5acfe2601911bfa07d8d61164c) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "b41-13.20", 0x00000, 0x10000, CRC(9e464254) SHA1(b6f6126b54c15320ecaa652d0eeabaa4cd94bd26) )

	ROM_REGION( 0x80000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "b41-04.48",  0x00000, 0x80000, CRC(c668638f) SHA1(07238a6cb4d93ffaf6351657163b5d80f0dbf688) )
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
// Asuka & Asuka
GAME( 1988, asukac,          asuka,    asuka,    asuka,    asuka_state, empty_init,  ROT270, "Taito Corporation",   "Asuka & Asuka (Translation Chinese)", MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE )
// Jigoku Meguri
GAME( 1988, jigkmgrihack01,  bonzeadv, bonzeadv, jigkmgri, asuka_state, empty_init,  ROT0,   "Taito Corporation",   "Jigoku Meguri (Japan, hack?)", MACHINE_SUPPORTS_SAVE )
