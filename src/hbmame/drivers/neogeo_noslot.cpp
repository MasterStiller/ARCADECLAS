// license:BSD-3-Clause
// copyright-holders:Bryan McPhail,Ernesto Corvi,Andrew Prime,Zsolt Vasvari, Robbbert
// thanks-to:Fuzz

#include "includes/neogeo.h"


/*************************************
 *
 *  Official sets
 *
 *************************************

    About supported sets:
    =====================

    MVS carts (arcade) were released before the AES carts (home)
    The actual codepath taken depends entirely on the BIOS rom, not the roms in the cartridge, which (with
    a few exceptions) support both codepaths.

    The initial AES releases are therefore later revisions of the game, often with bug fixes over the
    initial MVS releases. It isn't uncommon for later production runs and bootlegs to use these newer sets,
    so all of them are supported in MAME.

    Likewise, because the MVS carts were released first (and were produced in higher numbers and generally
    have a lower cost) it's not uncommon for AES units to operate with converted MVS carts, so, with the
    exception of the sets that specifically lock out the AES mode* these sets are all equally suitable
    for MESS.
    * nitd, kof2001 (initial release has no AES code), and a number of the hacked bootlegs.

    The 'MVS ONLY RELEASE' tagged sets were not officially released for the AES (home) system.
    Information about this can be found at 'The NeoGeo Master List' (unofficial) - http://www.neo-geo.com
    and the official NeoGeo museum - http://neogeomuseum.snkplaymore.co.jp/english/index.php
    Several unofficial 'conversions' of these sets can be found across the internet.
    For completeness sake: Some of these have sets have been released for the CD system.


    M1 (sound driver) rom information:
    ==================================
    . Many 'M1' roms contain mirrored data (64k mirrored or 128k mirrored).
    . Found on several early sets (ID 0001 ~ 0045) and on the last sets (ID 0267 ~ 0272).
    . This caused some confusion and incorrect rom sizes.
    . Minimum 'M1' size is 1mbit, maximum size 4mbit.
    . The remaining 64k 'M1' are marked BAD_DUMP.


    S1 (text layer) rom information:
    ================================
    . All 'S1' roms found on prom are 1mbit.
    . The remainig 64k 'S1' are marked BAD_DUMP.


    MULTI PLAY MODE:
    ================
    The NeoGeo has three games which support MULTI PLAY MODE (Riding Hero / League Bowling / Trash Rally).
    This allows you to 'link' 4 games (MVS) / 2 games (AES) using in game 'Multi-Play' option. To establish
    a link between the carts you have to connect the carts to each other by a communicator cable. The communicatior
    cable is a regular headphone cable with stereo pin jack. It has been reported that you can also 'link' MVS <-> AES.

    All three games use a special PROG board for MULTI PLAY MODE support:
    . Riding Hero    (AES - NEO-AEG PROG-HERO   / MVS NEO-MVS PROG-HERO)
    . League Bowling (AES - NEO-AEG PROG-HERO   / MVS NEO-MVS PROG-HERO)
    . Trash Rally    (AES - NEO-AEG PROG42G-COM / NEO-MVS PROG42G-COM)

    A HD6301V1P MCU on the above boards is used for establishing the 'link'. The MCU has a 4kb internal ROM which
    is not dumped.
    To use the MULTI PLAY MODE on your MVS you have to set the following hardware dips:
    HARD DIP SETTING  4   5   6
    CABINET 1:        OFF OFF ON
    CABINET 2:        OFF ON  ON
    CABINET 3:        ON  OFF ON
    CABINET 4:        ON  ON  ON


    SPHERO SYMPHONY:
    ================
    Several early games have a 'feature' called "sphero symphony". None of the games featuring "sphero symphony"
    uses special hardware. It is something sound based, but what exactly it is (specially arranged samples,
    FM synthesis etc.) is unknown. The AES and MVS releases share the same sound data and driver.

    The AES game-inserts and manuals have an eye-shaped logo with the following text (not to be found on MVS sets):
    sphero
    symphony
    STEREOPHONIC SOUND

    Experience this "LIVE" 3 dimensional sound coming from all around you.

    Games featuring "sphero symphony":
    ID-0006 - Riding Hero
    ID-0007 - Alpha Mission II / ASO II - Last Guardian
    ID-0009 - Ninja Combat
    ID-0010 - Cyber-Lip
    ID-0011 - The Super Spy
    ID-0014 - Mutation Nation
    ID-0017 - Sengoku / Sengoku Denshou
    ID-0018 - Burning Fight
    ID-0020 - Ghost Pilots
    ID-0024 - Last Resort
    ID-0031 - Soccer Brawl
    ID-0033 - Fatal Fury - King of Fighters / Garou Densetsu - shukumei no tatakai
    ID-0034 - Football Frenzy
    ID-0037 - Crossed Swords
    ID-0038 - Thrash Rally
    ID-0039 - King of the Monsters 2 - The Next Thing
    ID-0041 - Baseball Stars 2
    ID-0044 - Art of Fighting / Ryuuko no Ken
    ID-0047 - Fatal Fury 2 / Garou Densetsu 2 - arata-naru tatakai
    ID-0049 - Andro Dunos

*/


// Game specific input definitions

INPUT_PORTS_START( dualbios )
	PORT_INCLUDE( neogeo )

	/* the rom banking seems to be tied directly to the dipswitch */
	PORT_MODIFY("DSW")
	PORT_DIPNAME( 0x04, 0x00, DEF_STR( Region ) ) PORT_DIPLOCATION("SW:3") PORT_CHANGED_MEMBER(DEVICE_SELF, neogeo_state, select_bios, 0)
	PORT_DIPSETTING(    0x00, DEF_STR( Asia ) )
	PORT_DIPSETTING(    0x04, DEF_STR( Japan ) )
INPUT_PORTS_END


INPUT_PORTS_START( mjneogeo )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("DSW")
	PORT_DIPNAME( 0x04, 0x00, DEF_STR( Controller ) ) PORT_DIPLOCATION("SW:3")
	PORT_DIPSETTING(    0x04, DEF_STR( Joystick ) )
	PORT_DIPSETTING(    0x00, "Mahjong Panel" )
INPUT_PORTS_END

INPUT_PORTS_START( kizuna4p )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("DSW")
	PORT_DIPNAME( 0x02, 0x00, DEF_STR( Players ) ) PORT_DIPLOCATION("SW:2")
	PORT_DIPSETTING(    0x02, "2" )
	PORT_DIPSETTING(    0x00, "4" )

	PORT_MODIFY("SYSTEM")
	PORT_BIT( 0x0f00, IP_ACTIVE_HIGH, IPT_CUSTOM ) PORT_CUSTOM_MEMBER(neogeo_state, kizuna4p_start_r)
INPUT_PORTS_END

INPUT_PORTS_START( irrmaze )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("SYSTEM")
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_UNUSED )
INPUT_PORTS_END

INPUT_PORTS_START( vliner )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("DSW")
	PORT_BIT( 0x0f00, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_NAME("View Payout Table/Big")
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_NAME("Bet/Small")
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_NAME("Stop/Double Up")
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_NAME("Start/Collect")

	PORT_MODIFY("SYSTEM")
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_UNKNOWN ) /* this bit is used.. */
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_UNKNOWN ) /* this bit is used.. */

	PORT_MODIFY("AUDIO_COIN")
	PORT_BIT( 0x003f, IP_ACTIVE_LOW, IPT_UNUSED )

	PORT_START("IN5")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("Operator Menu") PORT_CODE(KEYCODE_F1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON5 ) PORT_NAME("Clear Credit")
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_BUTTON6 ) PORT_NAME("Hopper Out")
	PORT_BIT( 0xff00, IP_ACTIVE_LOW, IPT_UNKNOWN )

	/* not sure what any of these bits are */
	PORT_START("IN6")
	PORT_BIT( 0x0003, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0xffc0, IP_ACTIVE_HIGH, IPT_UNKNOWN )
INPUT_PORTS_END


INPUT_PORTS_START( jockeygp )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("SYSTEM")
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_UNKNOWN ) /* game freezes with this bit enabled */
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_UNKNOWN ) /* game freezes with this bit enabled */
INPUT_PORTS_END



/****************************************
 ID-0001
 . NGM-001
 NEO-MVS PROG-NAM / NEO-MVS CHA-32
 . NGH-001
 NEO-AEG PROG-NAM / NEO-AEG CHA-32
****************************************/

ROM_START( nam1975 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "001.p1", 0x000000, 0x080000, CRC(cc9fc951) SHA1(92f4e6ddeeb825077d92dbb70b50afea985f15c0) )

	NEO_SFIX_128K( "001.s1", CRC(7988ba51) SHA1(bc2f661f381b06b34ac2fa215dd5689d3bf84832) )

	NEO_BIOS_AUDIO_256K( "001.m1", CRC(ba874463) SHA1(a83514f4b20301f84a98699900e2593f1c1b8846) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "001.v1", 0x000000, 0x080000, CRC(a7c3d5e5) SHA1(e3efc86940f91c53b7724c4566cfc21ea1a7a465) )
	// AES has different label, data is the same: 001.v1

	ROM_REGION( 0x180000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "001.v21", 0x000000, 0x080000, CRC(55e670b3) SHA1(a047049646a90b6db2d1882264df9256aa5a85e5) )
	// AES has different label, data is the same: 001.v21
	ROM_LOAD( "001.v22", 0x080000, 0x080000, CRC(ab0d8368) SHA1(404114db9f3295929080b87a5d0106b40da6223a) )
	ROM_LOAD( "001.v23", 0x100000, 0x080000, CRC(df468e28) SHA1(4e5d4a709a4737a87bba4083aeb788f657862f1a) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "001.c1", 0x000000, 0x80000, CRC(32ea98e1) SHA1(c2fb3fb7dd14523a4b4b7fbdb81f44cb4cc48239) )
	ROM_LOAD16_BYTE( "001.c2", 0x000001, 0x80000, CRC(cbc4064c) SHA1(224c970fd060d841fd430c946ef609bb57b6d78c) )
	ROM_LOAD16_BYTE( "001.c3", 0x100000, 0x80000, CRC(0151054c) SHA1(f24fb501a7845f64833f4e5a461bcf9dc3262557) )
	ROM_LOAD16_BYTE( "001.c4", 0x100001, 0x80000, CRC(0a32570d) SHA1(f108446ec7844fde25f7a4ab454f76d384bf5e52) )
	ROM_LOAD16_BYTE( "001.c5", 0x200000, 0x80000, CRC(90b74cc2) SHA1(89898da36db259180e5261ed45eafc99ca13e504) )
	ROM_LOAD16_BYTE( "001.c6", 0x200001, 0x80000, CRC(e62bed58) SHA1(d05b2903b212a51ee131e52c761b714cb787683e) )
ROM_END

/****************************************
 ID-0002
 . NGM-002
 NEO-MVS PROG-EP / NEO-MVS CHA-32
 . NGH-002
 NEO-AEG PROG-4A / NEO-AEG CHA-32
****************************************/

ROM_START( bstars ) /* MVS VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "002.p1", 0x000000, 0x080000, CRC(c100b5f5) SHA1(4cea9f29ad67288c3eccfa4cf961ee9782e49165) )

	NEO_SFIX_128K( "002.s1", CRC(1a7fd0c6) SHA1(3fc701b7afddab369ddf9dedfbc5e1aaf80b8af3) )

	NEO_BIOS_AUDIO_256K( "002.m1", CRC(4ecaa4ee) SHA1(50abfb8eed6cb4887393089f9ccc76f306ef69b5) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "002.v11", 0x000000, 0x080000, CRC(b7b925bd) SHA1(644c92fa90e74998e73714f74b1e0680ee372a07) )
	ROM_LOAD( "002.v12", 0x080000, 0x080000, CRC(329f26fc) SHA1(2c8009edc88c6b26f7be5beb2b8d260aac394ee1) )
	ROM_LOAD( "002.v13", 0x100000, 0x080000, CRC(0c39f3c8) SHA1(db8f8670639601215707d918d4fb93221460446a) )
	ROM_LOAD( "002.v14", 0x180000, 0x080000, CRC(c7e11c38) SHA1(5abf2a7877e0162c758a4dcf09f183930fa7ef24) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "002.v21", 0x000000, 0x080000, CRC(04a733d1) SHA1(84159368c0f6de2c3b8121227201cd3422455cf6) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "002.c1", 0x000000, 0x080000, CRC(aaff2a45) SHA1(c91ee72d1d74514df8ec44fca703409d92158ae3) )
	ROM_LOAD16_BYTE( "002.c2", 0x000001, 0x080000, CRC(3ba0f7e4) SHA1(f023b134b9c7994f477867307d2732026033501d) )
	ROM_LOAD16_BYTE( "002.c3", 0x100000, 0x080000, CRC(96f0fdfa) SHA1(9f779a1ae46aeda54d69382b074392ade687f62f) )
	ROM_LOAD16_BYTE( "002.c4", 0x100001, 0x080000, CRC(5fd87f2f) SHA1(a5dd6f26f9485f216c2428ae1792c182beb10dbc) )
	ROM_LOAD16_BYTE( "002.c5", 0x200000, 0x080000, CRC(807ed83b) SHA1(3268e7d4602c3f55f1e0da2c80653d5ae461ef67) )
	ROM_LOAD16_BYTE( "002.c6", 0x200001, 0x080000, CRC(5a3cad41) SHA1(c620d18f4ff32ed5489c941dfc641030a54f1c14) )
ROM_END

ROM_START( bstarsh ) /* AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "002.p1", 0x000000, 0x080000, CRC(3bc7790e) SHA1(50b2fffb1278151bb4849fbe1f8cb23916019815) )

	NEO_SFIX_128K( "002.s1", CRC(1a7fd0c6) SHA1(3fc701b7afddab369ddf9dedfbc5e1aaf80b8af3) )

	NEO_BIOS_AUDIO_256K( "002.m1", CRC(4ecaa4ee) SHA1(50abfb8eed6cb4887393089f9ccc76f306ef69b5) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "002.v11", 0x000000, 0x080000, CRC(b7b925bd) SHA1(644c92fa90e74998e73714f74b1e0680ee372a07) )
	ROM_LOAD( "002.v12", 0x080000, 0x080000, CRC(329f26fc) SHA1(2c8009edc88c6b26f7be5beb2b8d260aac394ee1) )
	ROM_LOAD( "002.v13", 0x100000, 0x080000, CRC(0c39f3c8) SHA1(db8f8670639601215707d918d4fb93221460446a) )
	ROM_LOAD( "002.v14", 0x180000, 0x080000, CRC(c7e11c38) SHA1(5abf2a7877e0162c758a4dcf09f183930fa7ef24) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "002.v21", 0x000000, 0x080000, CRC(04a733d1) SHA1(84159368c0f6de2c3b8121227201cd3422455cf6) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "002.c1", 0x000000, 0x080000, CRC(aaff2a45) SHA1(c91ee72d1d74514df8ec44fca703409d92158ae3) )
	ROM_LOAD16_BYTE( "002.c2", 0x000001, 0x080000, CRC(3ba0f7e4) SHA1(f023b134b9c7994f477867307d2732026033501d) )
	ROM_LOAD16_BYTE( "002.c3", 0x100000, 0x080000, CRC(96f0fdfa) SHA1(9f779a1ae46aeda54d69382b074392ade687f62f) )
	ROM_LOAD16_BYTE( "002.c4", 0x100001, 0x080000, CRC(5fd87f2f) SHA1(a5dd6f26f9485f216c2428ae1792c182beb10dbc) )
	ROM_LOAD16_BYTE( "002.c5", 0x200000, 0x080000, CRC(807ed83b) SHA1(3268e7d4602c3f55f1e0da2c80653d5ae461ef67) )
	ROM_LOAD16_BYTE( "002.c6", 0x200001, 0x080000, CRC(5a3cad41) SHA1(c620d18f4ff32ed5489c941dfc641030a54f1c14) )
ROM_END

/****************************************
 ID-0003
 . NGM-003
 NEO-MVS PROG-EP / NEO-MVS CHA-32
 . NGH-003
 NEO-AEG PROG-4B / NEO-AEG CHA-32
****************************************/

ROM_START( tpgolf ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "003.p1", 0x000000, 0x080000, CRC(f75549ba) SHA1(3f7bdf5e2964e921fe1dd87c51a79a1a501fc73f) )
	ROM_LOAD16_WORD_SWAP( "003.p2", 0x080000, 0x080000, CRC(b7809a8f) SHA1(1604c889592c9610668bff296de48a0d6906156d) )

	NEO_SFIX_128K( "003.s1", CRC(7b3eb9b1) SHA1(39cd8bad9f8bfdeb8ac681b5b79ae5aa81c8dd5f) )

	NEO_BIOS_AUDIO_128K( "003.m1", CRC(4cc545e6) SHA1(8e014b8cab3e5b3995756a4ea52ce49c36866377) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "003.v11", 0x000000, 0x080000, CRC(ff97f1cb) SHA1(defa249d46ae220f7bfa70746f5202bbbcc3e5fe) )
	// AES has different label, data is the same (also found on MVS): 003.v11

	ROM_REGION( 0x200000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "003.v21", 0x000000, 0x080000, CRC(d34960c6) SHA1(36d5877d5e42aab943f4d693159f4f3ad8b0addc) )
	// AES has different label, data is the same (also found on MVS): 003.v21
	ROM_LOAD( "003.v22", 0x080000, 0x080000, CRC(9a5f58d4) SHA1(2b580595e1820430a36f06fd3e0e0b8f7d686889) )
	ROM_LOAD( "003.v23", 0x100000, 0x080000, CRC(30f53e54) SHA1(22461f88a56d272b78dbc23204c0c6816200532b) )
	ROM_LOAD( "003.v24", 0x180000, 0x080000, CRC(5ba0f501) SHA1(ca02937a611a2c50c9e4b54f8fd4eaea09259894) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "003.c1", 0x000000, 0x80000, CRC(0315fbaf) SHA1(583c9253219c1026d81ee5e0cf5568683adc2633) )
	ROM_LOAD16_BYTE( "003.c2", 0x000001, 0x80000, CRC(b4c15d59) SHA1(b0d8ec967f9b8e5216301c10b2d36912abce6515) )
	ROM_LOAD16_BYTE( "003.c3", 0x100000, 0x80000, CRC(8ce3e8da) SHA1(bc6c49b27d498f75a0d1a8c4d0cca75e140b9efc) )
	ROM_LOAD16_BYTE( "003.c4", 0x100001, 0x80000, CRC(29725969) SHA1(f1407da84919c2b3fe0e8f1fca65934b147c86c7) )
	ROM_LOAD16_BYTE( "003.c5", 0x200000, 0x80000, CRC(9a7146da) SHA1(2fc83d13e3e9565919aab01bf2a1b028f433b547) )
	ROM_LOAD16_BYTE( "003.c6", 0x200001, 0x80000, CRC(1e63411a) SHA1(ee397e2f679042e87b37d95837af62bb95a72af9) )
	ROM_LOAD16_BYTE( "003.c7", 0x300000, 0x80000, CRC(2886710c) SHA1(1533dd935f0a8f92a0a3c47d1d2bc6d035454244) )
	ROM_LOAD16_BYTE( "003.c8", 0x300001, 0x80000, CRC(422af22d) SHA1(f67c844c34545de6ea187f5bfdf440dec8518532) )
ROM_END

/****************************************
 ID-0004
 . NGM-004
 NEO-MVS PROG-EP / NEO-MVS CHA-32
 . NGH-004
 NEO-AEG PROG B  / NEO-AEG CHA-32
****************************************/

ROM_START( mahretsu ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "004.p1", 0x000000, 0x080000, CRC(fc6f53db) SHA1(64a62ca4c8fb68954e06121399c9402278bd0467) )

	NEO_SFIX_128K( "004.s1", CRC(2bd05a06) SHA1(876deadd4645373d82a503154eeddf18f440d743) )

	NEO_BIOS_AUDIO_128K( "004.m1", CRC(c71fbb3b) SHA1(59c58665b53da61352359d191a0569de5dd1f4b3) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "004.v11", 0x000000, 0x080000, CRC(b2fb2153) SHA1(36e0cc8927b11105de40188af46f6cf532794c10) )
	ROM_LOAD( "004.v12", 0x080000, 0x080000, CRC(8503317b) SHA1(ab22f1aba1e977ab234a4f1d73dc6ed789dbeb85) )

	ROM_REGION( 0x180000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "004.v21", 0x000000, 0x080000, CRC(4999fb27) SHA1(2d4926a220ea21bdd5e816bb16f985fff089500a) )
	ROM_LOAD( "004.v22", 0x080000, 0x080000, CRC(776fa2a2) SHA1(e7d5a362ab7806b7b009700a435c815a20e8ec68) )
	ROM_LOAD( "004.v23", 0x100000, 0x080000, CRC(b3e7eeea) SHA1(4d1e97f380702a3a06e7f954b4caddd9c4119d8f) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "004.c1", 0x000000, 0x80000, CRC(f1ae16bc) SHA1(df68feed4dcba1e1566032b01ebb7b478a1792bf) )
	ROM_LOAD16_BYTE( "004.c2", 0x000001, 0x80000, CRC(bdc13520) SHA1(2bc4c996d019a4c539f6c3188ef18089e54b7efa) )
	ROM_LOAD16_BYTE( "004.c3", 0x100000, 0x80000, CRC(9c571a37) SHA1(21388aeb92bb8e15a55a063701ca9df79e292127) )
	ROM_LOAD16_BYTE( "004.c4", 0x100001, 0x80000, CRC(7e81cb29) SHA1(5036f04df30cf6903bd1a8cc06ff6f015c24a74b) )
ROM_END

/****************************************
 ID-0005
 . NGM-005
 NEO-MVS PROG-EP / NEO-MVS CHA-32
 . NGH-005
 NEO-AEG PROG-4B / NEO-AEG CHA-32
****************************************/

ROM_START( maglord ) /* MVS VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "005.p1", 0x000000, 0x080000, CRC(bd0a492d) SHA1(d043d3710cf2b0d2b3798008e65e4c7c3ead1af3) )

	NEO_SFIX_128K( "005.s1", CRC(1c5369a2) SHA1(db0dba0a7dced6c9ca929c5abda491b05d84199c) )

	NEO_BIOS_AUDIO_256K( "005.m1", CRC(26259f0f) SHA1(4f3e500093d61585048767dbd9fa09b3911a05d6) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "005.v11", 0x000000, 0x080000, CRC(cc0455fd) SHA1(a8ff4270e7705e263d25ff0b301f503bccea7e59) )

	ROM_REGION( 0x100000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "005.v21", 0x000000, 0x080000, CRC(f94ab5b7) SHA1(2c16985102e3585e08622d8c54ac5c60425b9ff8) )
	ROM_LOAD( "005.v22", 0x080000, 0x080000, CRC(232cfd04) SHA1(61b66a9decbbd1f500a8c186615e7fd077c6861e) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "005.c1", 0x000000, 0x80000, CRC(806aee34) SHA1(3c32a0edbbddb694495b510c13979c44b83de8bc) )
	ROM_LOAD16_BYTE( "005.c2", 0x000001, 0x80000, CRC(34aa9a86) SHA1(cec97e1ff7f91158040c629ba75742db82c4ae5e) )
	ROM_LOAD16_BYTE( "005.c3", 0x100000, 0x80000, CRC(c4c2b926) SHA1(478bfafca21f5a1338808251a06ab405e6a9e65f) )
	ROM_LOAD16_BYTE( "005.c4", 0x100001, 0x80000, CRC(9c46dcf4) SHA1(4c05f3dc25777a87578ce09a6cefb3a4cebf3266) )
	ROM_LOAD16_BYTE( "005.c5", 0x200000, 0x80000, CRC(69086dec) SHA1(7fa47f4a765948813ebf366168275dcc3c42e951) )
	ROM_LOAD16_BYTE( "005.c6", 0x200001, 0x80000, CRC(ab7ac142) SHA1(e6ad2843947d35d8e913d2666f87946c1ba7944f) )
ROM_END

ROM_START( maglordh ) /* AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "005.p1", 0x000000, 0x080000, CRC(599043c5) SHA1(43f234b0f89b72b4c6050c40d9daa5c4e96b94ce) )

	NEO_SFIX_128K( "005.s1", CRC(1c5369a2) SHA1(db0dba0a7dced6c9ca929c5abda491b05d84199c) )

	NEO_BIOS_AUDIO_256K( "005.m1", CRC(26259f0f) SHA1(4f3e500093d61585048767dbd9fa09b3911a05d6) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "005.v11", 0x000000, 0x080000, CRC(cc0455fd) SHA1(a8ff4270e7705e263d25ff0b301f503bccea7e59) )

	ROM_REGION( 0x100000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "005.v21", 0x000000, 0x080000, CRC(f94ab5b7) SHA1(2c16985102e3585e08622d8c54ac5c60425b9ff8) )
	ROM_LOAD( "005.v22", 0x080000, 0x080000, CRC(232cfd04) SHA1(61b66a9decbbd1f500a8c186615e7fd077c6861e) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "005.c1", 0x000000, 0x80000, CRC(806aee34) SHA1(3c32a0edbbddb694495b510c13979c44b83de8bc) )
	ROM_LOAD16_BYTE( "005.c2", 0x000001, 0x80000, CRC(34aa9a86) SHA1(cec97e1ff7f91158040c629ba75742db82c4ae5e) )
	ROM_LOAD16_BYTE( "005.c3", 0x100000, 0x80000, CRC(c4c2b926) SHA1(478bfafca21f5a1338808251a06ab405e6a9e65f) )
	ROM_LOAD16_BYTE( "005.c4", 0x100001, 0x80000, CRC(9c46dcf4) SHA1(4c05f3dc25777a87578ce09a6cefb3a4cebf3266) )
	ROM_LOAD16_BYTE( "005.c5", 0x200000, 0x80000, CRC(69086dec) SHA1(7fa47f4a765948813ebf366168275dcc3c42e951) )
	ROM_LOAD16_BYTE( "005.c6", 0x200001, 0x80000, CRC(ab7ac142) SHA1(e6ad2843947d35d8e913d2666f87946c1ba7944f) )
ROM_END

/****************************************
 ID-0006
 . NGM-006
 NEO-MVS PROG-HERO / NEO-MVS CHA-32
 . NGH-006
 NEO-AEG PROG-HERO / NEO-AEG CHA-32
****************************************/

ROM_START( ridhero ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "006.p1", 0x000000, 0x080000, CRC(d4aaf597) SHA1(34d35b71adb5bd06f4f1b50ffd9c58ab9c440a84) )

	ROM_REGION( 0x2000, "mcu", 0 )    /* Hitachi HD6301V1 MCU */
	ROM_LOAD( "rhcom.bin", 0x0000, 0x2000, CRC(e5cd6306) SHA1(f6bbb8ae562804d67e137290c765c3589fa334c0) ) // dumped from a prototype with external ROM, not 100% confirmed as being the same on a final, or other games (lbowling, trally)

	NEO_SFIX_128K( "006.s1", CRC(eb5189f0) SHA1(0239c342ea62e73140a2306052f226226461a478) )

	NEO_BIOS_AUDIO_256K( "006.m1", CRC(92e7b4fe) SHA1(d240056cd632f92bdfaa5e0492c09aa9bd7b0471) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "006.v11", 0x000000, 0x080000, CRC(cdf74a42) SHA1(a17106cc3f9e5c5d52b4def861c0545a98151da2) )
	ROM_LOAD( "006.v12", 0x080000, 0x080000, CRC(e2fd2371) SHA1(cc95297bee7ffbdcb24ac4daeb5307cb39a52067) )

	ROM_REGION( 0x200000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "006.v21", 0x000000, 0x080000, CRC(94092bce) SHA1(1a2906271fe6bc396898a756153629a5862930eb) )
	ROM_LOAD( "006.v22", 0x080000, 0x080000, CRC(4e2cd7c3) SHA1(72fb215a4f208a22a764e801186d1643d3d840ca) )
	ROM_LOAD( "006.v23", 0x100000, 0x080000, CRC(069c71ed) SHA1(f450e9f60cd6ef846dbc77993159ec6157fb64e7) )
	ROM_LOAD( "006.v24", 0x180000, 0x080000, CRC(89fbb825) SHA1(656a97c6a8832dab3a5e1577d9cd257b561cc356) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "006.c1", 0x000000, 0x080000, CRC(4a5c7f78) SHA1(f8f1e6b7841c74368210d52a84307bb28f722a2d) )
	ROM_LOAD16_BYTE( "006.c2", 0x000001, 0x080000, CRC(e0b70ece) SHA1(e2b750e43cdddcea29d1c9c943a3628117a16a1b) )
	ROM_LOAD16_BYTE( "006.c3", 0x100000, 0x080000, CRC(8acff765) SHA1(11fe89b9d112d0658c9ddf40d928584de6ea9202) )
	ROM_LOAD16_BYTE( "006.c4", 0x100001, 0x080000, CRC(205e3208) SHA1(aa2acf2c6f48ffffdcc0c94ddc031acc9e4a2e68) )
ROM_END

ROM_START( ridheroh )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "006.p1", 0x000000, 0x080000, BAD_DUMP CRC(52445646) SHA1(647bb31f2f68453c1366cb6e2e867e37d1df7a54) )
	/* Chip label p1h does not exist, renamed temporarly to pg1, marked BAD_DUMP. This needs to be verified. */

	ROM_REGION( 0x2000, "mcu", 0 )    /* Hitachi HD6301V1 MCU */
	ROM_LOAD( "rhcom.bin", 0x0000, 0x2000, CRC(e5cd6306) SHA1(f6bbb8ae562804d67e137290c765c3589fa334c0) ) // dumped from a prototype with external ROM, not 100% confirmed as being the same on a final, or other games (lbowling, trally)

	NEO_SFIX_128K( "006.s1", CRC(eb5189f0) SHA1(0239c342ea62e73140a2306052f226226461a478) )

	NEO_BIOS_AUDIO_256K( "006.m1", CRC(92e7b4fe) SHA1(d240056cd632f92bdfaa5e0492c09aa9bd7b0471) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "006.v11", 0x000000, 0x080000, CRC(cdf74a42) SHA1(a17106cc3f9e5c5d52b4def861c0545a98151da2) )
	ROM_LOAD( "006.v12", 0x080000, 0x080000, CRC(e2fd2371) SHA1(cc95297bee7ffbdcb24ac4daeb5307cb39a52067) )

	ROM_REGION( 0x200000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "006.v21", 0x000000, 0x080000, CRC(94092bce) SHA1(1a2906271fe6bc396898a756153629a5862930eb) )
	ROM_LOAD( "006-v22.v22", 0x080000, 0x080000, CRC(4e2cd7c3) SHA1(72fb215a4f208a22a764e801186d1643d3d840ca) )
	ROM_LOAD( "006-v23.v23", 0x100000, 0x080000, CRC(069c71ed) SHA1(f450e9f60cd6ef846dbc77993159ec6157fb64e7) )
	ROM_LOAD( "006-v24.v24", 0x180000, 0x080000, CRC(89fbb825) SHA1(656a97c6a8832dab3a5e1577d9cd257b561cc356) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "006.c1", 0x000000, 0x080000, CRC(4a5c7f78) SHA1(f8f1e6b7841c74368210d52a84307bb28f722a2d) )
	ROM_LOAD16_BYTE( "006.c2", 0x000001, 0x080000, CRC(e0b70ece) SHA1(e2b750e43cdddcea29d1c9c943a3628117a16a1b) )
	ROM_LOAD16_BYTE( "006.c3", 0x100000, 0x080000, CRC(8acff765) SHA1(11fe89b9d112d0658c9ddf40d928584de6ea9202) )
	ROM_LOAD16_BYTE( "006.c4", 0x100001, 0x080000, CRC(205e3208) SHA1(aa2acf2c6f48ffffdcc0c94ddc031acc9e4a2e68) )
ROM_END

/****************************************
 ID-0007
 . NGM-007
 NEO-MVS PROG42G / NEO-MVS CHA42G
 . NGH-007
 NEO-AEG PROG42G / NEO-AEG CHA42G
 NEO-AEG PROG42G / NEO-AEG CHA-8M
 . prototype
 NEO-AEG PROG-EP / NEO-AEG CHA-EP
****************************************/

ROM_START( alpham2 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "007.p1", 0x000000, 0x080000, CRC(5b266f47) SHA1(8afbf995989f47ad93fea1f31a884afc7228b53a) )
	ROM_LOAD16_WORD_SWAP( "007.p2", 0x080000, 0x020000, CRC(eb9c1044) SHA1(65d3416dcd96663bc4e7cefe90ecb7c1eafb2dda) )

	NEO_SFIX_128K( "007.s1", CRC(85ec9acf) SHA1(39a11974438ad36a2cc84307151b31474c3c5518) )

	NEO_BIOS_AUDIO_128K( "007.m1", CRC(28dfe2cd) SHA1(1a1a99fb917c6c8db591e3be695ce03f843ee1df) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "007.v1", 0x000000, 0x100000, CRC(cd5db931) SHA1(b59f9f2df29f49470312a6cd20f5669b6aaf51ff) )
	ROM_LOAD( "007.v2", 0x100000, 0x100000, CRC(63e9b574) SHA1(1ade4cd0b15c84dd4a0fb7f7abf0885eef3a3f71) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "007.c1", 0x000000, 0x100000, CRC(8fba8ff3) SHA1(1a682292e99eb91b0edb9771c44bc5e762867e98) )
	ROM_LOAD16_BYTE( "007.c2", 0x000001, 0x100000, CRC(4dad2945) SHA1(ac85a146276537fed124bda892bb93ff549f1d93) )
	ROM_LOAD16_BYTE( "007.c3", 0x200000, 0x080000, CRC(68c2994e) SHA1(4f8dfc6e5188942e03b853a2c9f0ea6138dec791) )
	ROM_LOAD16_BYTE( "007.c4", 0x200001, 0x080000, CRC(7d588349) SHA1(a5ed789d7bbc25be5c5b2d99883b64d379c103a2) )
ROM_END

ROM_START( alpham2p ) /* early prototype - all roms were hand labeled with CRCs, dumps verified against them */ /* AES VERSION*/
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "007_p1_faac.p1", 0x000001, 0x080000, CRC(c763e52a) SHA1(b24acbac255c5ee1a2e92e77cdde6620a24081cf) )
	ROM_LOAD16_BYTE( "007_p2_1813.p2", 0x000000, 0x080000, CRC(7a0b435c) SHA1(40e6f42a92001d9f4e51898dd7489da143b6b74b) )

	NEO_SFIX_128K( "007_s1_36f1.s1", CRC(efc9ae2e) SHA1(a594826b0082fe5a13191673e8d9aa42517230f5) )

	NEO_BIOS_AUDIO_128K( "007_m1_9384.m1", CRC(5976b464) SHA1(ec824567ecc3579f6d86c9d9385710cbaeef16a3) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "007_v11_1bb4.v11", 0x000000, 0x080000, CRC(18eaa9e1) SHA1(85c94d8660f8a32e4ca8e015f0bd704208482d68) )
	ROM_LOAD( "007_v12_c8e8.v12", 0x080000, 0x080000, CRC(2487d495) SHA1(49af3c4dc6a38c5158d3641fd8f9a40041b42aa6) )
	ROM_LOAD( "007_v13_09fa.v13", 0x100000, 0x080000, CRC(25e60f25) SHA1(d06b0df872372de38fcf90187195070ac5f8c651) )
	ROM_LOAD( "007_v21_28c2.v21", 0x180000, 0x080000, CRC(ac44b75a) SHA1(7399a05cd4e2c7ecde4a7323d3e189255afe5fc2) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_COPY( "ymsnd:adpcma", 0x180000, 0x00000, 0x80000 )

	ROM_REGION( 0x400000, "sprites", 0 ) // note, ROM_LOAD32_BYTE
	ROM_LOAD32_BYTE( "007_c1_210e.c11", 0x000000, 0x80000, CRC(24841639) SHA1(fcc2a349121dad86ffefc44b9f0e8ba616ce0d30) )
	ROM_LOAD32_BYTE( "007_c2_29ae.c12", 0x000002, 0x80000, CRC(912763ab) SHA1(cedf26d7d85ad140399ee62813c71f35e65498d6) )
	ROM_LOAD32_BYTE( "007_c3_c873.c13", 0x000001, 0x80000, CRC(0743bde2) SHA1(0d13ad6333909ad3cf10f9ac360f9abf191318de) )
	ROM_LOAD32_BYTE( "007_c4_2462.c14", 0x000003, 0x80000, CRC(61240212) SHA1(dee36f6604adaeb96e0d761a7256241c066b1cd2) )
	ROM_LOAD32_BYTE( "007_c5_5f16.c15", 0x200000, 0x80000, CRC(cf9f4c53) SHA1(f979c85f83d9f76e554c2617f85f6d4efca6799c) )
	ROM_LOAD32_BYTE( "007_c6_8abc.c16", 0x200002, 0x80000, CRC(3d903b19) SHA1(001a8c762336b855fe1df69fe2e605d30a3f00a1) )
	ROM_LOAD32_BYTE( "007_c7_c983.c17", 0x200001, 0x80000, CRC(e41e3875) SHA1(730aceb8a66cb33d0194b096568f053ad7dc000a) )
	ROM_LOAD32_BYTE( "007_c8_b599.c18", 0x200003, 0x80000, CRC(4483e2cf) SHA1(47c3364f5c36ae9dc3a49fe37ca60bcee0e73314) )
ROM_END

/****************************************
 ID-0008
 Sun Shine (prototype) 1990 SNK / Alpha
****************************************/

/****************************************
 ID-0009
 . NGM-009
 NEO-MVS PROG-EP / NEO-MVS CHA-32
 . NGH-009
 NEO-AEG PROG-4A / NEO-AEG CHA-32
****************************************/

ROM_START( ncombat ) /* MVS VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "009.p1", 0x000000, 0x080000, CRC(b45fcfbf) SHA1(3872147dda2d1ba905d35f4571065d87b1958b4a) )

	NEO_SFIX_128K( "009.s1", CRC(d49afee8) SHA1(77615f12edf08ae8f1353f7a056a8f3a50d3ebdc) )

	NEO_BIOS_AUDIO_128K( "009.m1", CRC(b5819863) SHA1(6f2309d51531052dbf7d712993c9e35649db0d84) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "009.v11", 0x000000, 0x080000, CRC(cf32a59c) SHA1(af5b7fcd8a4aff1307c0a1d937e5f0460c32de79) )
	ROM_LOAD( "009.v12", 0x080000, 0x080000, CRC(7b3588b7) SHA1(a4e6d9d4113ff4ce48b371f65e9187d551821d3b) )
	ROM_LOAD( "009.v13", 0x100000, 0x080000, CRC(505a01b5) SHA1(9426a4f5b31e16f74e72e61951c189a878f211c5) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "009.v21", 0x000000, 0x080000, CRC(365f9011) SHA1(aebd292214ab280b05ee9e759b7e9a681a099c4a) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "009.c1", 0x000000, 0x80000, CRC(33cc838e) SHA1(c445c891c0ba4190aa0b472786150620e76df5b4) )
	ROM_LOAD16_BYTE( "009.c2", 0x000001, 0x80000, CRC(26877feb) SHA1(8f48097fb8e4757f50b6d86219122fbf4b6f87ef) )
	ROM_LOAD16_BYTE( "009.c3", 0x100000, 0x80000, CRC(3b60a05d) SHA1(0a165a17af4834876fcd634599cd2208adc9248f) )
	ROM_LOAD16_BYTE( "009.c4", 0x100001, 0x80000, CRC(39c2d039) SHA1(8ca6c3f977c43c7abba2a00a0e70f02e2a49f5f2) )
	ROM_LOAD16_BYTE( "009.c5", 0x200000, 0x80000, CRC(67a4344e) SHA1(b325f152c7b2388fc92c5826e1dc99094b9ea749) )
	ROM_LOAD16_BYTE( "009.c6", 0x200001, 0x80000, CRC(2eca8b19) SHA1(16764ef10e404325ba0a1a2ad3a4c0af287be21f) )
ROM_END

ROM_START( ncombath ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "009.p1", 0x000000, 0x080000, CRC(8e9f0add) SHA1(d0b908a86a58f2537eea73a431038f1cd74a5a2f) )

	NEO_SFIX_128K( "009.s1", CRC(d49afee8) SHA1(77615f12edf08ae8f1353f7a056a8f3a50d3ebdc) )

	NEO_BIOS_AUDIO_128K( "009.m1", CRC(b5819863) SHA1(6f2309d51531052dbf7d712993c9e35649db0d84) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "009.v11", 0x000000, 0x080000, CRC(cf32a59c) SHA1(af5b7fcd8a4aff1307c0a1d937e5f0460c32de79) )
	ROM_LOAD( "009.v12", 0x080000, 0x080000, CRC(7b3588b7) SHA1(a4e6d9d4113ff4ce48b371f65e9187d551821d3b) )
	ROM_LOAD( "009.v13", 0x100000, 0x080000, CRC(505a01b5) SHA1(9426a4f5b31e16f74e72e61951c189a878f211c5) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "009.v21", 0x000000, 0x080000, CRC(365f9011) SHA1(aebd292214ab280b05ee9e759b7e9a681a099c4a) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "009.c1", 0x000000, 0x80000, CRC(33cc838e) SHA1(c445c891c0ba4190aa0b472786150620e76df5b4) )
	ROM_LOAD16_BYTE( "009.c2", 0x000001, 0x80000, CRC(26877feb) SHA1(8f48097fb8e4757f50b6d86219122fbf4b6f87ef) )
	ROM_LOAD16_BYTE( "009.c3", 0x100000, 0x80000, CRC(3b60a05d) SHA1(0a165a17af4834876fcd634599cd2208adc9248f) )
	ROM_LOAD16_BYTE( "009.c4", 0x100001, 0x80000, CRC(39c2d039) SHA1(8ca6c3f977c43c7abba2a00a0e70f02e2a49f5f2) )
	ROM_LOAD16_BYTE( "009.c5", 0x200000, 0x80000, CRC(67a4344e) SHA1(b325f152c7b2388fc92c5826e1dc99094b9ea749) )
	ROM_LOAD16_BYTE( "009.c6", 0x200001, 0x80000, CRC(2eca8b19) SHA1(16764ef10e404325ba0a1a2ad3a4c0af287be21f) )
ROM_END

/****************************************
 ID-0010
 . NGM-010
 NEO-MVS PROG-EP / NEO-MVS CHA-32
 . NGH-010
 NEO-AEG PROG-B / NEO-AEG CHA-32
****************************************/

ROM_START( cyberlip )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "010.p1", 0x000000, 0x080000, CRC(69a6b42d) SHA1(6e7cb089de83f1d22cc4a87db5b1a94bf76fb1e8) )

	NEO_SFIX_128K( "010.s1", CRC(79a35264) SHA1(c2819a82adbe1f5e489496e0e03477863a5b7665) )

	NEO_BIOS_AUDIO_128K( "010.m1", CRC(8be3a078) SHA1(054ec6a061fcc88df1ecbb0a01611a31f37a7709) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "010.v11", 0x000000, 0x080000, CRC(90224d22) SHA1(5443ee6f90d80d43194cb4b4f0e08851a59e7784) )
	ROM_LOAD( "010.v12", 0x080000, 0x080000, CRC(a0cf1834) SHA1(8df57a7941bdae7e446a6056039adb012cdde246) )
	ROM_LOAD( "010.v13", 0x100000, 0x080000, CRC(ae38bc84) SHA1(c0937b4f89b8b26c8a0e747b234f44ad6a3bf2ba) )
	ROM_LOAD( "010.v14", 0x180000, 0x080000, CRC(70899bd2) SHA1(8cf01144f0bcf59f09777175ae6b71846b09f3a1) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "010.v21", 0x000000, 0x080000, CRC(586f4cb2) SHA1(588460031d84c308e3353ecf714db9986425c21c) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "010.c1", 0x000000, 0x80000, CRC(8bba5113) SHA1(70f0926409ab265da4b8632500d1d32d63cf77cf) )
	ROM_LOAD16_BYTE( "010.c2", 0x000001, 0x80000, CRC(cbf66432) SHA1(cc529640c475d08330e116ea9c5e5a28b7cd13db) )
	ROM_LOAD16_BYTE( "010.c3", 0x100000, 0x80000, CRC(e4f86efc) SHA1(fa60863d8a7ed4f21d30f91eb1936d0b8329db7a) )
	ROM_LOAD16_BYTE( "010.c4", 0x100001, 0x80000, CRC(f7be4674) SHA1(b4ad0432d4bb6d5a98e27015910343c964b73ed4) )
	ROM_LOAD16_BYTE( "010.c5", 0x200000, 0x80000, CRC(e8076da0) SHA1(3ec5cc19809dea688041a42b32c13d257576f3da) )
	ROM_LOAD16_BYTE( "010.c6", 0x200001, 0x80000, CRC(c495c567) SHA1(2f58475fbb5f1adafce027d396fb05dd71e8fb55) )
ROM_END

/****************************************
 ID-0011
 . NGM-011
 NEO-MVS PROG-8MB / NEO-MVS CHA-8M
 . NGH-011
 NEO-AEG PROG-8MB / NEO-AEG CHA-8M
****************************************/

ROM_START( superspy ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "011.p1",  0x000000, 0x080000, CRC(c7f944b5) SHA1(da7560e09187c68f1d9f7656218497b4464c56c9) )
	ROM_LOAD16_WORD_SWAP( "011.p2",  0x080000, 0x020000, CRC(811a4faf) SHA1(8169dfaf79f52d80ecec402ce1b1ab9cafb7ebdd) )

	NEO_SFIX_128K( "011.s1", CRC(ec5fdb96) SHA1(8003028025ac7bf531e568add6ba66c02d0b7e84) )

	NEO_BIOS_AUDIO_256K( "011.m1", CRC(ca661f1b) SHA1(4e3cb57db716ec48487c1b070c3a55a5faf40856) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "011.v11", 0x000000, 0x100000, CRC(5c674d5c) SHA1(d7b9beddeb247b584cea9ca6c43ec6869809b673) )
	ROM_LOAD( "011.v12", 0x100000, 0x080000, CRC(9f513d5a) SHA1(37b04962f0b8e2a74abd35c407337a6151dc4e95) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "011.v21", 0x000000, 0x080000, CRC(426cd040) SHA1(b2b45189837c8287223c2b8bd4df9525b72a3f16) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "011.c1", 0x000000, 0x100000, CRC(cae7be57) SHA1(43b35b349594535689c358d9f324adda55e5281a) )
	ROM_LOAD16_BYTE( "011.c2", 0x000001, 0x100000, CRC(9e29d986) SHA1(b417763bad1acf76116cd56f4203c2d2677e22e5) )
	ROM_LOAD16_BYTE( "011.c3", 0x200000, 0x100000, CRC(14832ff2) SHA1(1179792d773d97d5e45e7d8f009051d362d72e24) )
	ROM_LOAD16_BYTE( "011.c4", 0x200001, 0x100000, CRC(b7f63162) SHA1(077a81b2bb0a8f17c9df6945078608f74432877a) )
ROM_END

/****************************************
 ID-0012
 unknown
****************************************/

/****************************************
 ID-0013
 unknown
****************************************/

/****************************************
 ID-0014
 . NGM-014
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . NGH-014
 NEO-AEG PROG42G-1 / NEO-AEG CHA42G-1
****************************************/

ROM_START( mutnat ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "014.p1", 0x000000, 0x080000, CRC(6f1699c8) SHA1(87206f67a619dede7959230f9ff3701b8b78957a) )

	NEO_SFIX_128K( "014.s1", CRC(99419733) SHA1(b2524af8704941acc72282aa1d62fd4c93e3e822) )

	NEO_BIOS_AUDIO_128K( "014.m1", CRC(b6683092) SHA1(623ec7ec2915fb077bf65b4a16c815e071c25259) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "014.v1", 0x000000, 0x100000, CRC(25419296) SHA1(c9fc04987c4e0875d276e1a0fb671740b6f548ad) )
	ROM_LOAD( "014.v2", 0x100000, 0x100000, CRC(0de53d5e) SHA1(467f6040da3dfb1974785e95e14c3f608a93720a) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "014.c1", 0x000000, 0x100000, CRC(5e4381bf) SHA1(d429a5e09dafd2fb99495658b3652eecbf58f91b) )
	ROM_LOAD16_BYTE( "014.c2", 0x000001, 0x100000, CRC(69ba4e18) SHA1(b3369190c47771a790c7adffa958ff55d90e758b) )
	ROM_LOAD16_BYTE( "014.c3", 0x200000, 0x100000, CRC(890327d5) SHA1(47f97bf120a8480758e1f3bb8982be4c5325c036) )
	ROM_LOAD16_BYTE( "014.c4", 0x200001, 0x100000, CRC(e4002651) SHA1(17e53a5f4708866a120415bf24f3b89621ad0bcc) )
ROM_END

/****************************************
 ID-0015
 unknown
****************************************/

/****************************************
 ID-0016
 . NGM-016
 NEO-MVS PROG42G   / NEO-MVS CHA42G
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . NGH-016
 NEO-AEG PROG42G   / NEO-AEG CHA42G
 NEO-AEG PROG42G-1 / NEO-AEG CHA42G-1
****************************************/

ROM_START( kotm ) /* MVS VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "016.p1", 0x000000, 0x080000, CRC(1b818731) SHA1(b98b1b33c0301fd79aac908f6b635dd00d1cb08d) )
	ROM_LOAD16_WORD_SWAP( "016.p2", 0x080000, 0x020000, CRC(12afdc2b) SHA1(3a95f5910cbb9f17e63ddece995c6e120fa2f622) )

	NEO_SFIX_128K( "016.s1", CRC(1a2eeeb3) SHA1(8d2b96d395020197bc59294b6b0c8d62b1d8d4dd) )

	NEO_BIOS_AUDIO_128K( "016.m1", CRC(9da9ca10) SHA1(88b915827d529f39c365d3e41197d5461e07a085) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "016.v1", 0x000000, 0x100000, CRC(86c0a502) SHA1(7fe2db0c64aefdd14d6c36f7fcd6442591e9a014) )
	ROM_LOAD( "016.v2", 0x100000, 0x100000, CRC(5bc23ec5) SHA1(f4ff5d20587469daa026d5c812739335ce53cfdf) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "016.c1", 0x000000, 0x100000, CRC(71471c25) SHA1(bc8e3fee56b33ef2bac5b4b852339d2fbcd09b7c) )
	ROM_LOAD16_BYTE( "016.c2", 0x000001, 0x100000, CRC(320db048) SHA1(d6b43834de6f5442e23ca8fb26b3a36e96790d8d) )
	ROM_LOAD16_BYTE( "016.c3", 0x200000, 0x100000, CRC(98de7995) SHA1(e33edf4d36c82196d2b474e37be180a05976f558) )
	ROM_LOAD16_BYTE( "016.c4", 0x200001, 0x100000, CRC(070506e2) SHA1(3a2ec365e1d87a9c5ce1ee9bea88402a8eef4ed7) )
ROM_END

ROM_START( kotmh ) /* AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "016h.p1",0x000000, 0x080000, CRC(b774621e) SHA1(7684b2e07163aec68cd083ef1d8900f855f6cb42) )
	ROM_LOAD16_WORD_SWAP( "016.p2", 0x080000, 0x020000, CRC(12afdc2b) SHA1(3a95f5910cbb9f17e63ddece995c6e120fa2f622) )

	NEO_SFIX_128K( "016.s1", CRC(1a2eeeb3) SHA1(8d2b96d395020197bc59294b6b0c8d62b1d8d4dd) )

	NEO_BIOS_AUDIO_128K( "016.m1", CRC(9da9ca10) SHA1(88b915827d529f39c365d3e41197d5461e07a085) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "016.v1", 0x000000, 0x100000, CRC(86c0a502) SHA1(7fe2db0c64aefdd14d6c36f7fcd6442591e9a014) )
	ROM_LOAD( "016.v2", 0x100000, 0x100000, CRC(5bc23ec5) SHA1(f4ff5d20587469daa026d5c812739335ce53cfdf) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "016.c1", 0x000000, 0x100000, CRC(71471c25) SHA1(bc8e3fee56b33ef2bac5b4b852339d2fbcd09b7c) )
	ROM_LOAD16_BYTE( "016.c2", 0x000001, 0x100000, CRC(320db048) SHA1(d6b43834de6f5442e23ca8fb26b3a36e96790d8d) )
	ROM_LOAD16_BYTE( "016.c3", 0x200000, 0x100000, CRC(98de7995) SHA1(e33edf4d36c82196d2b474e37be180a05976f558) )
	ROM_LOAD16_BYTE( "016.c4", 0x200001, 0x100000, CRC(070506e2) SHA1(3a2ec365e1d87a9c5ce1ee9bea88402a8eef4ed7) )
ROM_END

/****************************************
 ID-0017
 . NGM-017
 NEO-MVS PROG42G / NEO-MVS CHA42G
 . NGH-017
 NEO-AEG PROG42G  / NEO-AEG CHA42G
 NEO-AEG PRO42G-1 / NEO-AEG CHA42G-1
****************************************/

ROM_START( sengoku ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "017.p1", 0x000000, 0x080000, CRC(f8a63983) SHA1(7a10ecb2f0fd8315641374c065d2602107b09e72) )
	ROM_LOAD16_WORD_SWAP( "017.p2", 0x080000, 0x020000, CRC(3024bbb3) SHA1(88892e1292dd60f35a76f9a22e623d4f0f9693cc) )

	NEO_SFIX_128K( "017.s1", CRC(b246204d) SHA1(73dce64c61fb5bb7e836a8e60f081bb77d80d281) )

	NEO_BIOS_AUDIO_128K( "017.m1", CRC(9b4f34c6) SHA1(7f3a51f47fcbaa598f5c76bc66e2c53c8dfd852d) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "017.v1", 0x000000, 0x100000, CRC(23663295) SHA1(9374a5d9f3de8e6a97c11f07d8b4485ac9d55edb) )
	ROM_LOAD( "017.v2", 0x100000, 0x100000, CRC(f61e6765) SHA1(1c9b287996947319eb3d288c3d82932cf01039db) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "017.c1", 0x000000, 0x100000, CRC(b4eb82a1) SHA1(79879e2ea78c07d04c88dc9a1ad59604b7a078be) )
	ROM_LOAD16_BYTE( "017.c2", 0x000001, 0x100000, CRC(d55c550d) SHA1(6110f693aa23710939c04153cf5af26493e4a03f) )
	ROM_LOAD16_BYTE( "017.c3", 0x200000, 0x100000, CRC(ed51ef65) SHA1(e8a8d86e24454948e51a75c883bc6e4091cbf820) )
	ROM_LOAD16_BYTE( "017.c4", 0x200001, 0x100000, CRC(f4f3c9cb) SHA1(8faafa89dbd0345218f71f891419d2e4e7578200) )
ROM_END

ROM_START( sengokuh ) /* AES VERSION (US) */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "017h.p1", 0x000000, 0x080000, CRC(33eccae0) SHA1(000ccf9a9c73df75eeba3f2c367c3a1a9e0a3a6b) )
	ROM_LOAD16_WORD_SWAP( "017.p2",  0x080000, 0x020000, CRC(3024bbb3) SHA1(88892e1292dd60f35a76f9a22e623d4f0f9693cc) )

	NEO_SFIX_128K( "017.s1", CRC(b246204d) SHA1(73dce64c61fb5bb7e836a8e60f081bb77d80d281) )

	NEO_BIOS_AUDIO_128K( "017.m1", CRC(9b4f34c6) SHA1(7f3a51f47fcbaa598f5c76bc66e2c53c8dfd852d) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "017.v1", 0x000000, 0x100000, CRC(23663295) SHA1(9374a5d9f3de8e6a97c11f07d8b4485ac9d55edb) )
	ROM_LOAD( "017.v2", 0x100000, 0x100000, CRC(f61e6765) SHA1(1c9b287996947319eb3d288c3d82932cf01039db) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "017.c1", 0x000000, 0x100000, CRC(b4eb82a1) SHA1(79879e2ea78c07d04c88dc9a1ad59604b7a078be) )
	ROM_LOAD16_BYTE( "017.c2", 0x000001, 0x100000, CRC(d55c550d) SHA1(6110f693aa23710939c04153cf5af26493e4a03f) )
	ROM_LOAD16_BYTE( "017.c3", 0x200000, 0x100000, CRC(ed51ef65) SHA1(e8a8d86e24454948e51a75c883bc6e4091cbf820) )
	ROM_LOAD16_BYTE( "017.c4", 0x200001, 0x100000, CRC(f4f3c9cb) SHA1(8faafa89dbd0345218f71f891419d2e4e7578200) )
ROM_END

/****************************************
 ID-0018
 . NGM-018
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 also found on (seen several times; CHA and PROG board are 'manually patched up' with wires and resistors)
 NEO-MVS PROG42G / NEO-MVS CHA42G
 . NGH-018
 NEO-AEG PROG42G / NEO-AEG CHA42G
 . prototype
 NEO-AEG PROG-EP / NEO-AEG CHA-EP
****************************************/

ROM_START( burningf ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "018.p1", 0x000000, 0x080000, CRC(4092c8db) SHA1(df194a4ad2c35e0e18bc053ff9284183444a4666) )

	NEO_SFIX_128K( "018.s1", CRC(6799ea0d) SHA1(ec75ef9dfdcb0b123574fc6d81ebaaadfba32fb5) )

	NEO_BIOS_AUDIO_128K( "018.m1", CRC(0c939ee2) SHA1(57d580d3279e66b9fe66bbcc68529d3384a926ff) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "018.v1", 0x000000, 0x100000, CRC(508c9ffc) SHA1(cd3a97a233a4585f8507116aba85884623cccdc4) )
	ROM_LOAD( "018.v2", 0x100000, 0x100000, CRC(854ef277) SHA1(4b3083b9c80620064cb44e812a787a700e32a6f3) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "018.c1", 0x000000, 0x100000, CRC(25a25e9b) SHA1(3cf02d0662e190678d0530d7b7d3f425209adf83) )
	ROM_LOAD16_BYTE( "018.c2", 0x000001, 0x100000, CRC(d4378876) SHA1(45659aa1755d96b992c977042186e47fff68bba9) )
	ROM_LOAD16_BYTE( "018.c3", 0x200000, 0x100000, CRC(862b60da) SHA1(e2303eb1609f1050f0b4f46693a15e37deb176fb) )
	ROM_LOAD16_BYTE( "018.c4", 0x200001, 0x100000, CRC(e2e0aff7) SHA1(1c691c092a6e2787de4f433b0eb9252bfdaa7e16) )
ROM_END

ROM_START( burningfh ) /* AES VERSION (US) */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "018h.p1", 0x000000, 0x080000, CRC(ddffcbf4) SHA1(c646c4bbdb4e9b32df76c90f582ccd69fcc9f8e7) )

	NEO_SFIX_128K( "018.s1", CRC(6799ea0d) SHA1(ec75ef9dfdcb0b123574fc6d81ebaaadfba32fb5) )

	NEO_BIOS_AUDIO_128K( "018.m1", CRC(0c939ee2) SHA1(57d580d3279e66b9fe66bbcc68529d3384a926ff) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "018.v1", 0x000000, 0x100000, CRC(508c9ffc) SHA1(cd3a97a233a4585f8507116aba85884623cccdc4) )
	ROM_LOAD( "018.v2", 0x100000, 0x100000, CRC(854ef277) SHA1(4b3083b9c80620064cb44e812a787a700e32a6f3) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "018.c1", 0x000000, 0x100000, CRC(25a25e9b) SHA1(3cf02d0662e190678d0530d7b7d3f425209adf83) )
	ROM_LOAD16_BYTE( "018.c2", 0x000001, 0x100000, CRC(d4378876) SHA1(45659aa1755d96b992c977042186e47fff68bba9) )
	ROM_LOAD16_BYTE( "018.c3", 0x200000, 0x100000, CRC(862b60da) SHA1(e2303eb1609f1050f0b4f46693a15e37deb176fb) )
	ROM_LOAD16_BYTE( "018.c4", 0x200001, 0x100000, CRC(e2e0aff7) SHA1(1c691c092a6e2787de4f433b0eb9252bfdaa7e16) )
ROM_END

ROM_START( burningfp ) /* early prototype - all roms were hand labeled with CRCs, dumps verified against them */ /* AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "018_p1_9397.p1", 0x000001, 0x080000, CRC(5b4032e7) SHA1(55df91dad6f484d3d49c28ab5972700bf71a8662) )
	ROM_LOAD16_BYTE( "018_p2_e335.p2", 0x000000, 0x080000, CRC(78762f68) SHA1(12170fc6efe75cb5d32624033d3d341032c97548) )

	NEO_SFIX_128K( "018_s1_9899.s1", CRC(f3d130e8) SHA1(2fdeb93f4bb2a60d391cac2822be41661b1e1795) )

	NEO_BIOS_AUDIO_128K( "018_m1_4586.m1", CRC(470dd5d4) SHA1(4291811b4aefe45261a1ae3631b6999fcd74fb3f) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "018_v11_56ac.v11", 0x000000, 0x080000, CRC(dc07ea3c) SHA1(c3e71aaec44ead7ddc581565d16b90030e6db5fd) )
	ROM_LOAD( "018_v12_db95.v12", 0x080000, 0x080000, CRC(f1ae637c) SHA1(02a4c7d4a544350a314ab7b26d8c9d3baa8f5778) )
	ROM_LOAD( "018_v21_98dd.v21", 0x100000, 0x080000, CRC(9f3b4eda) SHA1(7f516923d04daa483b4b99c9babba66505931a34) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_COPY( "ymsnd:adpcma", 0x100000, 0x00000, 0x80000 )

	ROM_REGION( 0x400000, "sprites", 0 ) // note, ROM_LOAD32_BYTE
	ROM_LOAD32_BYTE( "018_c1_ba06.c11", 0x000000, 0x80000, CRC(6569018b) SHA1(25040e0a9c2b72900100a22a2a41de5f6c339d8a) )
	ROM_LOAD32_BYTE( "018_c2_d534.c12", 0x000002, 0x80000, CRC(6949b501) SHA1(d8ee48837faff6cc849046ee8757b2b94d440303) )
	ROM_LOAD32_BYTE( "018_c3_9d70.c13", 0x000001, 0x80000, CRC(410f653b) SHA1(ce94667721baa7b2c318fc268e3bb9209671c9f5) )
	ROM_LOAD32_BYTE( "018_c4_bf9d.c14", 0x000003, 0x80000, CRC(d43bf2a5) SHA1(c27985d8973611d02570f469a0d8cb4f5b63b614) )
	ROM_LOAD32_BYTE( "018_c5_ac9d.c15", 0x200000, 0x80000, CRC(837d09d3) SHA1(d3b06931fca6123604549599544b04529ef34c53) )
	ROM_LOAD32_BYTE( "018_c6_d2a5.c16", 0x200002, 0x80000, CRC(5fee51e7) SHA1(835c632fa12a1d5b4104cd80b8f686ac80b314a1) )
	ROM_LOAD32_BYTE( "018_c7_d568.c17", 0x200001, 0x80000, CRC(0f3f0823) SHA1(ec1d681c1795de43d20f30f85956e2473ec39c95) )
	ROM_LOAD32_BYTE( "018_c8_d256.c18", 0x200003, 0x80000, CRC(67cc9e34) SHA1(dc72a464c1456a4d2f7b992b416a984fb7885e99) )
ROM_END

/****************************************
 ID-0019
 . NGM-019
 NEO-MVS PROG-HERO / NEO-MVS CHA-32
 . NGH-019
 NEO-AEG PROG-HERO / NEO-AEG CHA-32
****************************************/

ROM_START( lbowling ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "019.p1", 0x000000, 0x080000, CRC(a2de8445) SHA1(893d7ae72b4644123469de143fa35fac1cbcd61e) )

	ROM_REGION( 0x1000, "mcu", 0 )    /* Hitachi HD6301V1 MCU */
	ROM_LOAD( "hd6301v1p.com", 0x0000, 0x1000, NO_DUMP )

	NEO_SFIX_128K( "019.s1", CRC(5fcdc0ed) SHA1(86415077e7adc3ba6153eeb4fb0c62cf36e903fa) )

	NEO_BIOS_AUDIO_128K( "019.m1", CRC(d568c17d) SHA1(a2e318ed6ad1809c79f3f0853d75e0dd1a2f275c) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "019.v11", 0x000000, 0x080000, CRC(0fb74872) SHA1(38c555926c77576d63472bc075210c42e9ce13a3) )
	ROM_LOAD( "019.v12", 0x080000, 0x080000, CRC(029faa57) SHA1(7bbaa87e38929ab1e32df5f6a2ec0fd5001e7cdb) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "019.v21", 0x000000, 0x080000, CRC(2efd5ada) SHA1(8ba70f5f665d566824333075227d9bce1253b8d8) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD16_BYTE( "019.c1", 0x000000, 0x080000, CRC(4ccdef18) SHA1(5011e30ec235d0b0a5a513a11d4275777e61acdb) )
	ROM_LOAD16_BYTE( "019.c2", 0x000001, 0x080000, CRC(d4dd0802) SHA1(82069752028c118d42384a95befde45844f0f247) )
ROM_END

/****************************************
 ID-0020
 . NGM-020
 NEO-MVS PROG8M42 / NEO-MVS CHA-8M
 . NGH-020
 NEO-AEG PROG8M42 / NEO-AEG CHA-8M
****************************************/

ROM_START( gpilots ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "020.p1", 0x000000, 0x080000, CRC(e6f2fe64) SHA1(50ab82517e077727d97668a4df2b9b96d2e78ab6) )
	ROM_LOAD16_WORD_SWAP( "020.p2", 0x080000, 0x020000, CRC(edcb22ac) SHA1(505d2db38ae999b7d436e8f2ff56b81796d62b54) )

	NEO_SFIX_128K( "020.s1", CRC(a6d83d53) SHA1(9a8c092f89521cc0b27a385aa72e29cbaca926c5) )

	NEO_BIOS_AUDIO_128K( "020.m1", CRC(48409377) SHA1(0e212d2c76856a90b2c2fdff675239525972ac43) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "020.v11", 0x000000, 0x100000, CRC(1b526c8b) SHA1(2801868d2badcf8aaf5d490e010e4049d81d7bc1) )
	ROM_LOAD( "020.v12", 0x100000, 0x080000, CRC(4a9e6f03) SHA1(d3ac11f333b03d8a318921bdaefb14598e289a14) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "020.v21", 0x000000, 0x080000, CRC(7abf113d) SHA1(5b2a0e70f2eaf4638b44702dacd4cb17838fb1d5) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "020.c1", 0x000000, 0x100000, CRC(bd6fe78e) SHA1(50b704862cd79d64fa488e621b079f6e413c33bc) )
	ROM_LOAD16_BYTE( "020.c2", 0x000001, 0x100000, CRC(5f4a925c) SHA1(71c5ef8141234daaa7025427a6c65e79766973a5) )
	ROM_LOAD16_BYTE( "020.c3", 0x200000, 0x100000, CRC(d1e42fd0) SHA1(f0d476aebbdc2ce008f5f0783be86d295b24aa44) )
	ROM_LOAD16_BYTE( "020.c4", 0x200001, 0x100000, CRC(edde439b) SHA1(79be7b10ecdab54c2f77062b8f5fda0e299fa982) )
ROM_END

ROM_START( gpilotsh ) /* AES VERSION (US) */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "020h.p1", 0x000000, 0x080000, CRC(7cdb01ce) SHA1(32cae2ddf5e26fb7e8a09132e600220db82df3b8) )
	ROM_LOAD16_WORD_SWAP( "020.p2",  0x080000, 0x020000, CRC(edcb22ac) SHA1(505d2db38ae999b7d436e8f2ff56b81796d62b54) )

	NEO_SFIX_128K( "020.s1", CRC(a6d83d53) SHA1(9a8c092f89521cc0b27a385aa72e29cbaca926c5) )

	NEO_BIOS_AUDIO_128K( "020.m1", CRC(48409377) SHA1(0e212d2c76856a90b2c2fdff675239525972ac43) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "020.v11", 0x000000, 0x100000, CRC(1b526c8b) SHA1(2801868d2badcf8aaf5d490e010e4049d81d7bc1) )
	ROM_LOAD( "020.v12", 0x100000, 0x080000, CRC(4a9e6f03) SHA1(d3ac11f333b03d8a318921bdaefb14598e289a14) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "020.v21", 0x000000, 0x080000, CRC(7abf113d) SHA1(5b2a0e70f2eaf4638b44702dacd4cb17838fb1d5) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "020.c1", 0x000000, 0x100000, CRC(bd6fe78e) SHA1(50b704862cd79d64fa488e621b079f6e413c33bc) )
	ROM_LOAD16_BYTE( "020.c2", 0x000001, 0x100000, CRC(5f4a925c) SHA1(71c5ef8141234daaa7025427a6c65e79766973a5) )
	ROM_LOAD16_BYTE( "020.c3", 0x200000, 0x100000, CRC(d1e42fd0) SHA1(f0d476aebbdc2ce008f5f0783be86d295b24aa44) )
	ROM_LOAD16_BYTE( "020.c4", 0x200001, 0x100000, CRC(edde439b) SHA1(79be7b10ecdab54c2f77062b8f5fda0e299fa982) )
ROM_END

/****************************************
 ID-0021
 . NGM-021
 NEO-MVS PROG-EP / NEO-MVS CHA-32
 . NGH-021
 NEO-AEG PROG B  / NEO-AEG CHA-32
****************************************/

ROM_START( joyjoy ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "021.p1", 0x000000, 0x080000, CRC(39c3478f) SHA1(06ebe54c9c4e14c5c31e770013d58b7162359ecc) )

	NEO_SFIX_128K( "021.s1", CRC(6956d778) SHA1(e3757776d60dc07d8e07c9ca61b223b14732f860) )

	NEO_BIOS_AUDIO_256K( "021.m1", CRC(5a4be5e8) SHA1(552f025ce0d51c25f42e1a81cf0d08376ca5475d) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "021.v11", 0x000000, 0x080000, CRC(66c1e5c4) SHA1(7e85420021d4c39c36ed75a1cec567c5610ffce0) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "021.v21", 0x000000, 0x080000, CRC(8ed20a86) SHA1(d15cba5eac19ea56fdd4877541f1bb3eb755ebba) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD16_BYTE( "021.c1", 0x000000, 0x080000, CRC(509250ec) SHA1(d6ddb16d8222088f153a85a905bcb99541a5f2cf) )
	ROM_LOAD16_BYTE( "021.c2", 0x000001, 0x080000, CRC(09ed5258) SHA1(6bf50cd10236e29146b49e714a0e0ebcfe30a682) )
ROM_END

/****************************************
 ID-0022
 . ALM-001
 NEO-MVS PROG8M42  / NEO-MVS CHA-8M
 . ALH-001
 NEO-AEG PROG 8M42 / NEO-AEG CHA-8M
****************************************/

ROM_START( bjourney ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "022.p1", 0x000000, 0x100000, CRC(6a2f6d4a) SHA1(b8ca548e56f1c7abcdce415ba7329e0cf698ee13) )

	NEO_SFIX_128K( "022.s1", CRC(843c3624) SHA1(dbdf86c193b7c1d795f8c21f2c103c1d3e18abbe) )

	NEO_BIOS_AUDIO_128K( "022.m1", CRC(8e1d4ab6) SHA1(deabc11ab81e7e68a3e041c03a127ae28d0d7264) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "022.v11", 0x000000, 0x100000, CRC(2cb4ad91) SHA1(169ec7303c4275155a66a88cc08270c24132bb36) )
	ROM_LOAD( "022.v22", 0x100000, 0x100000, CRC(65a54d13) SHA1(a591fbcedca8f679dacbebcd554e3aa3fd163e92) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "022.c1", 0x000000, 0x100000, CRC(4d47a48c) SHA1(6e282285be72583d828e7765b1c1695ecdc44777) )
	ROM_LOAD16_BYTE( "022.c2", 0x000001, 0x100000, CRC(e8c1491a) SHA1(c468d2556b3de095aaa05edd1bc16d71303e9478) )
	ROM_LOAD16_BYTE( "022.c3", 0x200000, 0x080000, CRC(66e69753) SHA1(974b823fc62236fbc23e727f25b61a805a707a9e) )
	ROM_LOAD16_BYTE( "022.c4", 0x200001, 0x080000, CRC(71bfd48a) SHA1(47288be69e6992d09ebef108b4de9ffab6293dc8) )
ROM_END

/****************************************
 ID-0023
 . NGM-023
 NEO-MVS PROG42G / NEO-MVS CHA42G
 NEO-MVS PROGTOP / NEO-MVS CHA-256
 Boards used for the Korean release
 . NGH-023
 NEO-AEG PROG42G-1 / NEO-AEG CHA42G-1
****************************************/

ROM_START( quizdais ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "023.p1", 0x000000, 0x100000, CRC(c488fda3) SHA1(4cdf2f1837fffd720efef42f81f933bdf2ef1402) )

	NEO_SFIX_128K( "023.s1", CRC(ac31818a) SHA1(93c8d67a93606a2e02f12ca4cab849dc3f3de286) )

	NEO_BIOS_AUDIO_128K( "023.m1", CRC(2a2105e0) SHA1(26fc13556fda2dbeb7b5b035abd994e302dc7662) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "023.v1", 0x000000, 0x100000, CRC(a53e5bd3) SHA1(cf115c6478ce155d889e6a5acb962339e08e024b) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "023.c1", 0x000000, 0x100000, CRC(2999535a) SHA1(0deabf771039987b559edc2444eea741bd7ba861) )
	ROM_LOAD16_BYTE( "023.c2", 0x000001, 0x100000, CRC(876a99e6) SHA1(8d1dcfc0927d7523f8be8203573192406ec654b4) )
ROM_END

ROM_START( quizdaisk ) /* KOREAN VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "123.p1", 0x000000, 0x100000, CRC(a6f35eae) SHA1(edd3fd5ba8eae2231e2b0a6605fa00e5c6de094a) )

	NEO_SFIX_128K( "123.s1", CRC(53de938a) SHA1(5024fee3b245f8a069d7ecfa6f033b70ed1a5fce) )

	NEO_BIOS_AUDIO_128K( "123.m1", CRC(d67f53f9) SHA1(73a1bd175ae29dd957a907a046884f8715bd0a34) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "123.v1", 0x000000, 0x200000, CRC(986f4af9) SHA1(9e15d2142ec5e5d076582dc1cecfd724b0924f54) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "123.c1", 0x000000, 0x100000, CRC(e579a606) SHA1(b9430ec157902f0707e5d52e69bd5d93792e7118) )
	ROM_LOAD16_BYTE( "123.c2", 0x000001, 0x100000, CRC(e182c837) SHA1(a8f7648bf21ebd3efe3a49606b53220815a60d0f) )
ROM_END

/****************************************
 ID-0024
 . NGM-024
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . NGH-024

 . prototype
 NEO-MVS PROG-EP / NEO-MVS CHA-EPG
****************************************/

ROM_START( lresort )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "024.p1", 0x000000, 0x080000, CRC(89c4ab97) SHA1(3a1817c427185ea1b44fe52f009c00b0a9007c85) )

	NEO_SFIX_128K( "024.s1", CRC(5cef5cc6) SHA1(9ec305007bdb356e9f8f279beae5e2bcb3f2cf7b) )

	NEO_BIOS_AUDIO_128K( "024.m1", CRC(cec19742) SHA1(ab6c6ba7737e68d2420a0617719c6d4c89039c45) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "024.v1", 0x000000, 0x100000, CRC(efdfa063) SHA1(e4609ecbcc1c820758f229da5145f51285b50555) )
	ROM_LOAD( "024.v2", 0x100000, 0x100000, CRC(3c7997c0) SHA1(8cb7e8e69892b19d318978370dbc510d51b06a69) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "024.c1", 0x000000, 0x100000, CRC(3617c2dc) SHA1(8de2643a618272f8aa1c705363edb007f4a5f5b7) )
	ROM_LOAD16_BYTE( "024.c2", 0x000001, 0x100000, CRC(3f0a7fd8) SHA1(d0c9c7a9dde9ce175fb243d33ec11fa719d0158c) )
	ROM_LOAD16_BYTE( "024.c3", 0x200000, 0x080000, CRC(e9f745f8) SHA1(bbe6141da28b0db7bf5cf321d69b7e613e2414d7) )
	ROM_LOAD16_BYTE( "024.c4", 0x200001, 0x080000, CRC(7382fefb) SHA1(e916dec5bb5462eb9ae9711f08c7388937abb980) )
ROM_END

ROM_START( lresortp ) /* prototype - all roms were hand labeled with CRCs */ /* MVS VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "024_p1_5937.podd",  0x000001, 0x080000, CRC(8e6008ee) SHA1(6779663118782207156dc9fa9e24e81e30c6391c) )
	ROM_LOAD16_BYTE( "024_p2_8d37.peven", 0x000000, 0x080000, CRC(6d9ee90f) SHA1(ecd42182988092417bc96db8301ea408e47735f2) )

	NEO_SFIX_128K( "024_s1_22fe.s1", CRC(5cef5cc6) SHA1(9ec305007bdb356e9f8f279beae5e2bcb3f2cf7b) )

	NEO_BIOS_AUDIO_128K( "024_m1_fc7a.m1", CRC(22122875) SHA1(540c21559163381467679f836cb068adaf526659) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "024_v11_b085.v11", 0x000000, 0x080000, CRC(0722da38) SHA1(66a9b463d5277908b3a01c03de82b3de9118f2cb) ) // 024_v11_b085.bin            024.v1    [1/2]      IDENTICAL
	ROM_LOAD( "024_v12_d3b7.v12", 0x080000, 0x080000, CRC(670ce3ec) SHA1(9004aa85d4a9b0ecf9cf9357b073ed55a98fdb02) ) // 024_v12_d3b7.bin            024.v1    [2/2]      IDENTICAL
	ROM_LOAD( "024_v13_a31e.v13", 0x100000, 0x080000, CRC(2e39462b) SHA1(b0a9b1a3377bf0369f3020192505c46ca52927d6) ) // 024_v13_a31e.bin            024.v2    [1/2]      IDENTICAL
	ROM_LOAD( "024_v24_2f0f.v24", 0x180000, 0x080000, CRC(7944754f) SHA1(d42a46c5127c6c62041ebffb0007af8a24abd360) ) // 024_v24_2f0f.bin            024.v2    [2/2]      IDENTICAL

	ROM_REGION( 0x400000, "sprites", 0 ) // note, ROM_LOAD32_BYTE
	ROM_LOAD32_BYTE( "024_c1_b764.c1", 0x000000, 0x80000, CRC(677749ec) SHA1(6f94675e037956a380652ab1056e6f1dec605bec) )
	ROM_LOAD32_BYTE( "024_c2_1951.c2", 0x000002, 0x80000, CRC(104d7b59) SHA1(404e8776ee8df4ca282eb7b747759af8628ddca1) )
	ROM_LOAD32_BYTE( "024_c3_0f63.c3", 0x000001, 0x80000, CRC(b0965a74) SHA1(e8026dd4f722ccab9c913261d09ab8843ef56a0e) )
	ROM_LOAD32_BYTE( "024_c4_c5b5.c4", 0x000003, 0x80000, CRC(dcfc3860) SHA1(8443b455ae8de656adab57f3b7e68919f22d3b9d) )
	ROM_LOAD32_BYTE( "024_c5_dd03.c5", 0x200000, 0x80000, CRC(50322397) SHA1(3308fbe48ad165b9894a52fc3a8d9898bbbc0c0e) )
	ROM_LOAD32_BYTE( "024_c6_c81a.c6", 0x200002, 0x80000, CRC(c3c93894) SHA1(f23b9d7e2b54d44c96370dde282bdf45cebd9cba) )
	ROM_LOAD32_BYTE( "024_c7_5edc.c7", 0x200001, 0x80000, CRC(21faf72b) SHA1(00bf257b06180ae6ede57744cea6257b3488d9f0) )
	ROM_LOAD32_BYTE( "024_c8_0850.c8", 0x200003, 0x80000, CRC(fb57217b) SHA1(607a98da754e8b1dd94a6432b21a36cc38e06a0f) )
ROM_END


/****************************************
 ID-0025
 . NGM-025
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . NGH-025
 NEO-AEG PROG42G / NEO-AEG CHA42G
****************************************/

ROM_START( eightman ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "025.p1", 0x000000, 0x080000, CRC(43344cb0) SHA1(29dfd699f35b0a74e20fedd6c9174c289f0ef6e0) )

	NEO_SFIX_128K( "025.s1", CRC(a402202b) SHA1(75c44e1af459af155f5b892fd18706268dd5e602) )

	NEO_BIOS_AUDIO_128K( "025.m1", CRC(9927034c) SHA1(205665361c5b2ab4f01ec480dd3c9b69db858d09) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "025.v1", 0x000000, 0x100000, CRC(4558558a) SHA1(a4b277703ed67225c652be0d618daeca65a27b88) )
	ROM_LOAD( "025.v2", 0x100000, 0x100000, CRC(c5e052e9) SHA1(fa1119c90ce4c706a6aa0c17d7bc06aa3068d9b2) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "025.c1", 0x000000, 0x100000, CRC(555e16a4) SHA1(1c96f3d2fd0991680fbf627a6cdd26ad2cd60319) )
	ROM_LOAD16_BYTE( "025.c2", 0x000001, 0x100000, CRC(e1ee51c3) SHA1(da8d074bb4e923ed7b8a154fd31b42f2d65b8e96) )
	ROM_LOAD16_BYTE( "025.c3", 0x200000, 0x080000, CRC(0923d5b0) SHA1(ab72ba1e3ebf56dd356f9ad181f986b1360a1089) )
	ROM_LOAD16_BYTE( "025.c4", 0x200001, 0x080000, CRC(e3eca67b) SHA1(88154cbc1a261c2f425430119ebc08a30adc9675) )
ROM_END

/****************************************
 ID-0026
 Fun Fun Brothers (prototype) 1991 Alpha
****************************************/

/****************************************
 ID-0027
 . MOM-001
 NEO-MVS PROG-8MB / NEO-MVS CHA-8M
 . MOH-001
 NEO-AEG PROG-8MB / NEO-AEG CHA-8M
****************************************/

ROM_START( minasan ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "027.p1", 0x000000, 0x080000, CRC(c8381327) SHA1(c8f8be0ba276c6d12ef13d05af3cf83a2b924894) )

	NEO_SFIX_128K( "027.s1", CRC(e5824baa) SHA1(8230ff7fe3cabeacecc762d90a084e893db84906) )

	NEO_BIOS_AUDIO_128K( "027.m1", CRC(add5a226) SHA1(99995bef2584abbba16777bac52f55523f7aa97d) )

	ROM_DEFAULT_BIOS( "japan" ) /* so the mahjong panel will work in the service menu */

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "027.v11", 0x000000, 0x100000, CRC(59ad4459) SHA1(bbb8ba8a8e337dd2946eefda4757e80d0547d54a) )

	ROM_REGION( 0x100000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "027.v21", 0x000000, 0x100000, CRC(df5b4eeb) SHA1(134f3bcc3bb82e2a5711496af1019f343f9c0f7e) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "027.c1", 0x000000, 0x100000, CRC(d0086f94) SHA1(7d6579530ccb5188f653be69b1df17e47e40e7a6) )
	ROM_LOAD16_BYTE( "027.c2", 0x000001, 0x100000, CRC(da61f5a6) SHA1(82c5b4e5c5c5e30a3fd1c2e11c6157f39d033c42) )
	ROM_LOAD16_BYTE( "027.c3", 0x200000, 0x100000, CRC(08df1228) SHA1(288b7ad328c2249f28d17df4dad3584995dca7bf) )
	ROM_LOAD16_BYTE( "027.c4", 0x200001, 0x100000, CRC(54e87696) SHA1(90816dc86be3983dc57f56ededf7738475c0c61e) )
ROM_END

/****************************************
 ID-0028
 Dunk Star (prototype) 1991 Sammy
****************************************/

/****************************************
 ID-0029
 . ??M-029
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . ??H-029
****************************************/

ROM_START( legendos )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "029.p1", 0x000000, 0x080000, CRC(9d563f19) SHA1(9bff7bf9fdcf81a0a6c4ce3e196097d4f05e67b6) )

	NEO_SFIX_128K( "029.s1", CRC(bcd502f0) SHA1(a3400f52c037aa6a42e59e602cc24fa45fcbc951) )

	NEO_BIOS_AUDIO_128K( "029.m1", CRC(6f2843f0) SHA1(975fb1598b87a2798fff05e951fca2e2e0329e79) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "029.v1", 0x000000, 0x100000, CRC(85065452) SHA1(7154b7c59b16c32753ac6b5790fb50b51ce30a20) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "029.c1", 0x000000, 0x100000, CRC(2f5ab875) SHA1(3e060973bba41a6c22ff7054104bdc5eee1fa13a) )
	ROM_LOAD16_BYTE( "029.c2", 0x000001, 0x100000, CRC(318b2711) SHA1(7014110cee98280317e1189f306ca40652b61f6f) )
	ROM_LOAD16_BYTE( "029.c3", 0x200000, 0x100000, CRC(6bc52cb2) SHA1(14323a4664b7dcbcde82e594168e535d7a921e44) )
	ROM_LOAD16_BYTE( "029.c4", 0x200001, 0x100000, CRC(37ef298c) SHA1(7a0c4c896dc3e730e06dcadbf00cf354f08a4466) )
ROM_END

/****************************************
 ID-0030
 . NGM-030
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . NGH-030
 NEO-AEG PROG42G-1 / NEO-AEG CHA42G-1
 NEO-AEG PROG42G   / NEO-AEG CHA42G
****************************************/

ROM_START( 2020bb )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "030.p1", 0x000000, 0x080000, CRC(d396c9cb) SHA1(47ba421d14d05b965a8d44e7475b227a208e5a07) )
	/* also found AES set with p1 label 030-P1 on TC534200 on NEO-AEG PROG42G and m1 label 030-M1 on TC531001 on NEO-AEG CHA42G; other chip labels are the same */

	NEO_SFIX_128K( "030.s1", CRC(7015b8fc) SHA1(8c09bc3e6c62e0f7c9557c1e10c901be325bae7f) )

	NEO_BIOS_AUDIO_128K( "030.m1", CRC(4cf466ec) SHA1(6a003b53c7a4af9d7529e2c10f27ffc4e58dcda5) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "030.v1", 0x000000, 0x100000, CRC(d4ca364e) SHA1(b0573744b0ea2ef1e2167a225f0d254883f5af04) )
	ROM_LOAD( "030.v2", 0x100000, 0x100000, CRC(54994455) SHA1(76eb62b86e8ed51a77f44313d5cc8091b3f58d57) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "030.c1", 0x000000, 0x100000, CRC(4f5e19bd) SHA1(ef7975c4b33a7aea4a25a385f604799f054d3200) )
	ROM_LOAD16_BYTE( "030.c2", 0x000001, 0x100000, CRC(d6314bf0) SHA1(0920cc580d7997fcb0170dd619af2f305d635577) )
	ROM_LOAD16_BYTE( "030.c3", 0x200000, 0x100000, CRC(47fddfee) SHA1(297c505a63448c999a2510c27bf4549102134db8) )
	ROM_LOAD16_BYTE( "030.c4", 0x200001, 0x100000, CRC(780d1c4e) SHA1(2e2cf9de828e3b48642dd2203637103438c62142) )
ROM_END

ROM_START( 2020bba ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "030a.p1", 0x000000, 0x080000, CRC(c59be3dd) SHA1(4fbd462c1c18e85a252c58b04b54fd3b82b46cb0) )
	/* P1 on eprom, correct chip label unknown */

	NEO_SFIX_128K( "030.s1", CRC(7015b8fc) SHA1(8c09bc3e6c62e0f7c9557c1e10c901be325bae7f) )

	NEO_BIOS_AUDIO_128K( "030.m1", CRC(4cf466ec) SHA1(6a003b53c7a4af9d7529e2c10f27ffc4e58dcda5) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "030.v1", 0x000000, 0x100000, CRC(d4ca364e) SHA1(b0573744b0ea2ef1e2167a225f0d254883f5af04) )
	ROM_LOAD( "030.v2", 0x100000, 0x100000, CRC(54994455) SHA1(76eb62b86e8ed51a77f44313d5cc8091b3f58d57) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "030.c1", 0x000000, 0x100000, CRC(4f5e19bd) SHA1(ef7975c4b33a7aea4a25a385f604799f054d3200) )
	ROM_LOAD16_BYTE( "030.c2", 0x000001, 0x100000, CRC(d6314bf0) SHA1(0920cc580d7997fcb0170dd619af2f305d635577) )
	ROM_LOAD16_BYTE( "030.c3", 0x200000, 0x100000, CRC(47fddfee) SHA1(297c505a63448c999a2510c27bf4549102134db8) )
	ROM_LOAD16_BYTE( "030.c4", 0x200001, 0x100000, CRC(780d1c4e) SHA1(2e2cf9de828e3b48642dd2203637103438c62142) )
ROM_END

ROM_START( 2020bbh )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "030.p1", 0x000000, 0x080000, BAD_DUMP CRC(12d048d7) SHA1(ee0d03a565b11ca3bee2d24f62ff46a85ef18d90) )
	/* Chip label p1h does not exist, renamed temporarly to pg1, marked BAD_DUMP. This needs to be verified. */

	NEO_SFIX_128K( "030.s1", CRC(7015b8fc) SHA1(8c09bc3e6c62e0f7c9557c1e10c901be325bae7f) )

	NEO_BIOS_AUDIO_128K( "030.m1", CRC(4cf466ec) SHA1(6a003b53c7a4af9d7529e2c10f27ffc4e58dcda5) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "030.v1", 0x000000, 0x100000, CRC(d4ca364e) SHA1(b0573744b0ea2ef1e2167a225f0d254883f5af04) )
	ROM_LOAD( "030.v2", 0x100000, 0x100000, CRC(54994455) SHA1(76eb62b86e8ed51a77f44313d5cc8091b3f58d57) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "030.c1", 0x000000, 0x100000, CRC(4f5e19bd) SHA1(ef7975c4b33a7aea4a25a385f604799f054d3200) )
	ROM_LOAD16_BYTE( "030.c2", 0x000001, 0x100000, CRC(d6314bf0) SHA1(0920cc580d7997fcb0170dd619af2f305d635577) )
	ROM_LOAD16_BYTE( "030.c3", 0x200000, 0x100000, CRC(47fddfee) SHA1(297c505a63448c999a2510c27bf4549102134db8) )
	ROM_LOAD16_BYTE( "030.c4", 0x200001, 0x100000, CRC(780d1c4e) SHA1(2e2cf9de828e3b48642dd2203637103438c62142) )
ROM_END

/****************************************
 ID-0031
 . NGM-031
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . NGH-031
 NEO-AEG PROG42G-1 / NEO-AEG CHA42G-1
****************************************/

ROM_START( socbrawl ) /* MVS VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "031.p1", 0x000000, 0x080000, CRC(17f034a7) SHA1(2e66c7bd93a08efe63c4894494db50bbf58f60e4) )

	NEO_SFIX_128K( "031.s1", CRC(4c117174) SHA1(26e52c4f628338a9aa1c159517cdf873f738fb98) )

	NEO_BIOS_AUDIO_128K( "031.m1", CRC(cb37427c) SHA1(99efe9600ebeda48331f396e3203c7588bdb7d24) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "031.v1", 0x000000, 0x100000, CRC(cc78497e) SHA1(895bd647150fae9b2259ef043ed681f4c4de66ea) )
	ROM_LOAD( "031.v2", 0x100000, 0x100000, CRC(dda043c6) SHA1(08165a59700ab6b1e523079dd2a3549e520cc594) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "031.c1", 0x000000, 0x100000, CRC(bd0a4eb8) SHA1(b67988cb3e550d083e81c9bd436da55b242785ed) )
	ROM_LOAD16_BYTE( "031.c2", 0x000001, 0x100000, CRC(efde5382) SHA1(e42789c8d87ee3d4549d0a903e990c03338cbbd8) )
	ROM_LOAD16_BYTE( "031.c3", 0x200000, 0x080000, CRC(580f7f33) SHA1(f4f95a7c8de00e1366a723fc4cd0e8c1905af636) )
	ROM_LOAD16_BYTE( "031.c4", 0x200001, 0x080000, CRC(ed297de8) SHA1(616f8fa4c86231f3e79faf9f69f8bb909cbc35f0) )
ROM_END

ROM_START( socbrawlh ) /* AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "031.p1", 0x000000, 0x080000, CRC(a2801c24) SHA1(627d76ff0740ca29586f37b268f47fb469822529) )

	NEO_SFIX_128K( "031.s1", CRC(4c117174) SHA1(26e52c4f628338a9aa1c159517cdf873f738fb98) )

	NEO_BIOS_AUDIO_128K( "031.m1", CRC(cb37427c) SHA1(99efe9600ebeda48331f396e3203c7588bdb7d24) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "031.v1", 0x000000, 0x100000, CRC(cc78497e) SHA1(895bd647150fae9b2259ef043ed681f4c4de66ea) )
	ROM_LOAD( "031.v2", 0x100000, 0x100000, CRC(dda043c6) SHA1(08165a59700ab6b1e523079dd2a3549e520cc594) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "031.c1", 0x000000, 0x100000, CRC(bd0a4eb8) SHA1(b67988cb3e550d083e81c9bd436da55b242785ed) )
	ROM_LOAD16_BYTE( "031.c2", 0x000001, 0x100000, CRC(efde5382) SHA1(e42789c8d87ee3d4549d0a903e990c03338cbbd8) )
	ROM_LOAD16_BYTE( "031.c3", 0x200000, 0x080000, CRC(580f7f33) SHA1(f4f95a7c8de00e1366a723fc4cd0e8c1905af636) )
	ROM_LOAD16_BYTE( "031.c4", 0x200001, 0x080000, CRC(ed297de8) SHA1(616f8fa4c86231f3e79faf9f69f8bb909cbc35f0) )
ROM_END

/****************************************
 ID-0032
 . NGM-032
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . NGH-032
 NEO-AEG PROG42G-1 / NEO-AEG CHA42G-1
****************************************/

ROM_START( roboarmy )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "032.p1", 0x000000, 0x080000, CRC(cd11cbd4) SHA1(23163e3da2f07e830a7f4a02aea1cb01a54ccbf3) )
	/* also found AES and MVS set with p1 on eprom on NEO-AEG PROG42G-1 and NEO-MVS PROG42G-COM; correct chip label unknown */

	NEO_SFIX_128K( "032.s1", CRC(ac0daa1b) SHA1(93bae4697dc403fce19422752a514326ccf66a91) )

	NEO_BIOS_AUDIO_128K( "032.m1", CRC(35ec952d) SHA1(8aed30e26d7e2c70dbce5de752df416091066f7b) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "032.v1", 0x000000, 0x100000, CRC(63791533) SHA1(4479e9308cdc906b9e03b985303f4ebedd00512f) )
	ROM_LOAD( "032.v2", 0x100000, 0x100000, CRC(eb95de70) SHA1(b34885201116d2b3bbdee15ec7b5961cf5c069e1) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "032.c1", 0x000000, 0x100000, CRC(97984c6c) SHA1(deea59c0892f05dc7db98cb57b3eb83688dc57f0) )
	ROM_LOAD16_BYTE( "032.c2", 0x000001, 0x100000, CRC(65773122) SHA1(2c0162a8e971e5e57933e4ae16040bf824ffdefe) )
	ROM_LOAD16_BYTE( "032.c5", 0x200000, 0x080000, CRC(40adfccd) SHA1(b11f866dd70ba0ed9123424508355cb948b19bdc) )
	ROM_LOAD16_BYTE( "032.c6", 0x200001, 0x080000, CRC(462571de) SHA1(5c3d610d492f91564423873b3b434dcda700373f) )
ROM_END

/****************************************
 ID-0033
 . NGM-033
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . NGH-033
 NEO-AEG PROG42G-1 / NEO-AEG CHA42G-1
****************************************/

ROM_START( fatfury1 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "033.p1", 0x000000, 0x080000, CRC(47ebdc2f) SHA1(d46786502920fb510f1999db00c5e09fb641c0bd) )
	ROM_LOAD16_WORD_SWAP( "033.p2", 0x080000, 0x020000, CRC(c473af1c) SHA1(4919eeca20abe807493872ca7c79a5d1f496fe68) )

	NEO_SFIX_128K( "033.s1", CRC(3c3bdf8c) SHA1(2f3e5feed6c27850b2a0f6fae0b97041690e944c) )

	NEO_BIOS_AUDIO_128K( "033.m1", CRC(5be10ffd) SHA1(90a5e6cbbc58a7883cd2a3a597180d631a466882) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "033.v1", 0x000000, 0x100000, CRC(212fd20d) SHA1(120c040db8c01a6f140eea03725448bfa9ca98c2) )
	ROM_LOAD( "033.v2", 0x100000, 0x100000, CRC(fa2ae47f) SHA1(80d0ba4cd30aab59b6f0db8fa341387bd7388afc) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "033.c1", 0x000000, 0x100000, CRC(74317e54) SHA1(67b9c2814a12603b959612456f59de55f9bf6f57) )
	ROM_LOAD16_BYTE( "033.c2", 0x000001, 0x100000, CRC(5bb952f3) SHA1(ea964bbcc0408b6ae07cbb5043d003281b1aca15) )
	ROM_LOAD16_BYTE( "033.c3", 0x200000, 0x100000, CRC(9b714a7c) SHA1(b62bdcede3207d062a89e0a4a9adf706101bb681) )
	ROM_LOAD16_BYTE( "033.c4", 0x200001, 0x100000, CRC(9397476a) SHA1(a12dbb74020aeb6ebf24ec2abbfba5129cabcb7d) )
ROM_END

/****************************************
 ID-0034
 . NGM-034
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . NGH-034
 NEO-AEG PROG42G-1 / NEO-AEG CHA42G-1
****************************************/

ROM_START( fbfrenzy ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "034.p1", 0x000000, 0x080000, CRC(cdef6b19) SHA1(97482db0dffc6d625fb41fa38449c0a74d741a72) )

	NEO_SFIX_128K( "034.s1", CRC(8472ed44) SHA1(42e1a9671dddd090d2a634cff986f6c73ba08b70) )

	NEO_BIOS_AUDIO_128K( "034.m1", CRC(f41b16b8) SHA1(f3e1cfc4cd2c5baece176f169906aa796367d303) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "034.v1", 0x000000, 0x100000, CRC(50c9d0dd) SHA1(2b3f2875b00e5f307d274128bd73c1521a7d901b) )
	ROM_LOAD( "034.v2", 0x100000, 0x100000, CRC(5aa15686) SHA1(efe47954827a98d539ba719347c5f8aa60e6338b) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "034.c1", 0x000000, 0x100000, CRC(91c56e78) SHA1(2944d49ebfc71239d345209ca7f25993c2cc5a77) )
	ROM_LOAD16_BYTE( "034.c2", 0x000001, 0x100000, CRC(9743ea2f) SHA1(cf4fccdf10d521d555e92bc24123142393c2b3bb) )
	ROM_LOAD16_BYTE( "034.c3", 0x200000, 0x080000, CRC(e5aa65f5) SHA1(714356a2cee976ec0f515b1034ce971018e5c02e) )
	ROM_LOAD16_BYTE( "034.c4", 0x200001, 0x080000, CRC(0eb138cc) SHA1(21d31e1f136c674caa6dd44073281cd07b72ea9b) )
ROM_END

/****************************************
 ID-0035
 Mystic Wand (prototype) 1991 Alpha
****************************************/

/****************************************
 ID-0036
 . MOM-002
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 NEO-MVS PROG42G-COM / NEO-MVS CHA42G-1
 . MOH-002
 NEO-AEG PROG42G / NEO-AEG CHA42G
****************************************/

ROM_START( bakatono ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "036.p1", 0x000000, 0x080000, CRC(1c66b6fa) SHA1(6c50cc452971c46c763ae0b2def95792671a1798) )

	NEO_SFIX_128K( "036.s1", CRC(f3ef4485) SHA1(c30bfceed7e669e4c97b0b3ec2e9f4271e5b6662) )

	NEO_BIOS_AUDIO_128K( "036.m1", CRC(f1385b96) SHA1(e7e3d1484188a115e262511116aaf466b8b1f428) )

	ROM_DEFAULT_BIOS( "japan" ) /* so the mahjong panel will work in the service menu */

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "036.v1", 0x000000, 0x100000, CRC(1c335dce) SHA1(493c273fa71bf81861a20af4c4eaae159e169f39) )
	ROM_LOAD( "036.v2", 0x100000, 0x100000, CRC(bbf79342) SHA1(45a4f40e415cdf35c3073851506648c8f7d53958) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "036.c1", 0x000000, 0x100000, CRC(fe7f1010) SHA1(5b6f5053821f4da8dc3768371e2cd51bb29da963) )
	ROM_LOAD16_BYTE( "036.c2", 0x000001, 0x100000, CRC(bbf003f5) SHA1(054b2a3327e038836eece652055bb84c115cf8ed) )
	ROM_LOAD16_BYTE( "036.c3", 0x200000, 0x100000, CRC(9ac0708e) SHA1(8decfe06d73a3dd3c3cf280719978fcf6d559d29) )
	ROM_LOAD16_BYTE( "036.c4", 0x200001, 0x100000, CRC(f2577d22) SHA1(a37db8055ca4680e244c556dc6df8bdba16c2083) )
ROM_END

/****************************************
 ID-0037
 . ALM-002
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . ALH-002
 NEO-AEG PROG42G / NEO-AEG CHA42G
****************************************/

ROM_START( crsword ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "037.p1", 0x000000, 0x080000, CRC(e7f2553c) SHA1(8469ecb900477feed05ae3311fe9515019bbec2a) )

	NEO_SFIX_128K( "037.s1", CRC(74651f27) SHA1(bff7ff2429d2be82c1647abac2ee45b339b3b310) )

	NEO_BIOS_AUDIO_128K( "037.m1", CRC(9504b2c6) SHA1(9ce8e681b9df6eacd0d23a36bad836bd5074233d) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "037.v1", 0x000000, 0x100000, CRC(61fedf65) SHA1(98f31d1e23bf7c1f7844e67f14707a704134042e) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "037.c1", 0x000000, 0x100000, CRC(09df6892) SHA1(df2579dcf9c9dc88d461212cb74de106be2983c1) )
	ROM_LOAD16_BYTE( "037.c2", 0x000001, 0x100000, CRC(ac122a78) SHA1(7bfa4d29b7d7d9443f64d81caeafa74fe05c606e) )
	ROM_LOAD16_BYTE( "037.c3", 0x200000, 0x100000, CRC(9d7ed1ca) SHA1(2bbd25dc3a3f825d0af79a418f06a23a1bf03cc0) )
	ROM_LOAD16_BYTE( "037.c4", 0x200001, 0x100000, CRC(4a24395d) SHA1(943f911f40985db901eaef4c28dfcda299fca73e) )
ROM_END

/****************************************
 ID-0038
 . ALM-003
 NEO-MVS PROG42G-COM / NEO-MVS CHA42G-1
 . ALH-003
 NEO-AEG PROG42G-COM / NEO-AEG CHA42G-1
****************************************/

ROM_START( trally ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "038.p1", 0x000000, 0x080000, CRC(1e52a576) SHA1(a1cb56354c3378e955b0cd482c3c41ae15add952) )
	ROM_LOAD16_WORD_SWAP( "038.p2", 0x080000, 0x080000, CRC(a5193e2f) SHA1(96803480439e90da23cdca70d59ff519ee85beeb) )

	ROM_REGION( 0x1000, "mcu", 0 )    /* Hitachi HD6301V1 MCU */
	ROM_LOAD( "hd6301v1p.hd6301v1", 0x0000, 0x1000, NO_DUMP )

	NEO_SFIX_128K( "038.s1", CRC(fff62ae3) SHA1(6510a762ea41557a8938cbfc0557cd5921306061) )

	NEO_BIOS_AUDIO_128K( "038.m1", CRC(0908707e) SHA1(df7489ea6abf84d7f137ba7a8f52a4fd1b088fd7) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "038.v1", 0x000000, 0x100000, CRC(5ccd9fd5) SHA1(c3c8c758a320c39e4ceb0b6d9f188ed6d122eec4) )
	ROM_LOAD( "038.v2", 0x100000, 0x080000, CRC(ddd8d1e6) SHA1(65c819fa2392f264f5a1a0a4967c96775732500b) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "038.c1", 0x000000, 0x100000, CRC(c58323d4) SHA1(a6bd277471a4b612d165f8b804f3cb662f499b70) )
	ROM_LOAD16_BYTE( "038.c2", 0x000001, 0x100000, CRC(bba9c29e) SHA1(b70bbfdfa8c4f9ea76406530e86b16e42498d284) )
	ROM_LOAD16_BYTE( "038.c3", 0x200000, 0x080000, CRC(3bb7b9d6) SHA1(bc1eae6181ad5abf79736afc8db4ca34113d43f8) )
	ROM_LOAD16_BYTE( "038.c4", 0x200001, 0x080000, CRC(a4513ecf) SHA1(934aa103c226eac55157b44d7b4dfa35515322c3) )
ROM_END

/****************************************
 ID-0039
 . NGM-039
 NEO-MVS PROG16 / NEO-MVS CHA42G-1
 . NGH-039
 NEO-AEG PROG16 / NEO-AEG CHA42G-1
****************************************/

ROM_START( kotm2 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "039.p1", 0x000000, 0x080000, CRC(b372d54c) SHA1(b70fc6f72e16a66b6e144cc01370548e3398b8b8) )
	ROM_LOAD16_WORD_SWAP( "039.p2", 0x080000, 0x080000, CRC(28661afe) SHA1(6c85ff6ab334b1ca744f726f42dac211537e7315) )

	NEO_SFIX_128K( "039.s1", CRC(63ee053a) SHA1(7d4b92bd022708975b1470e8f24d1f5a712e1b94) )

	NEO_BIOS_AUDIO_128K( "039.m1", CRC(0c5b2ad5) SHA1(15eb5ea10fecdbdbcfd06225ae6d88bb239592e7) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "039.v2", 0x000000, 0x200000, CRC(86d34b25) SHA1(89bdb614b0c63d678962da52e2f596750d20828c) )
	ROM_LOAD( "039.v4", 0x200000, 0x100000, CRC(8fa62a0b) SHA1(58ac2fdd73c542eb8178cfc4adfa0e5940183283) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD16_BYTE( "039.c1", 0x000000, 0x100000, CRC(6d1c4aa9) SHA1(4fbc9d7cb37522ec298eefbe38c75a2d050fbb4a) )
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_LOAD16_BYTE( "039.c2", 0x000001, 0x100000, CRC(f7b75337) SHA1(4d85f85948c3e6ed38b0b0ccda79de3ce026e2d9) )
	ROM_CONTINUE( 0x400001, 0x100000 )
	ROM_LOAD16_BYTE( "039.c3", 0x200000, 0x080000, CRC(bfc4f0b2) SHA1(f4abe2b52882b966412f3b503b8f2c8f49b57968) )
	ROM_LOAD16_BYTE( "039.c4", 0x200001, 0x080000, CRC(81c9c250) SHA1(e3a34ff69081a8681b5ca895915892dcdccfa7aa) )
ROM_END

ROM_START( kotm2p ) /* fairly late prototype release, only the code differs from the main set */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "proto_039.p1", 0x000001, 0x080000, CRC(3c1d17e7) SHA1(aeaff465fafa46ded903ed4e8cb8cd05de8dc096) )
	ROM_LOAD16_BYTE( "proto_039.p2", 0x000000, 0x080000, CRC(bc9691f0) SHA1(3854659b952d4f8c2edd5d59858a61ce6d518604) )

	NEO_SFIX_128K( "039.s1", CRC(63ee053a) SHA1(7d4b92bd022708975b1470e8f24d1f5a712e1b94) )

	NEO_BIOS_AUDIO_128K( "039.m1", CRC(0c5b2ad5) SHA1(15eb5ea10fecdbdbcfd06225ae6d88bb239592e7) )

	// same data as main set, but prototype board layout
	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "proto_039.v1", 0x000000, 0x080000, CRC(dd3566f1) SHA1(f7c2a3747aaab2bc57cdfa33d8bb9fab057b5214) )
	ROM_LOAD( "proto_039.v2", 0x080000, 0x080000, CRC(57f60274) SHA1(7e17740aa05cf7ad4f9084e147600a8eb82c7284) )
	ROM_LOAD( "proto_039.v3", 0x100000, 0x080000, CRC(0f008a07) SHA1(ed243a0449232bbea409308c3fec7e057fcd8501) )
	ROM_LOAD( "proto_039.v4", 0x180000, 0x080000, CRC(1943d0fe) SHA1(47fb716c76ea6b5fe64204ff6d72b7feea10bda9) )
	ROM_LOAD( "proto_039-v5.v5", 0x200000, 0x080000, CRC(13be045b) SHA1(0e3713ae6b164ebae434c0f18c466365b26b9a77) )
	ROM_LOAD( "proto_039-v6.v6", 0x280000, 0x080000, CRC(d1dd3fd6) SHA1(052b92168a76cf3a97c8cacebcc3ebab228726df) )

	// same data as main set, but prototype board layout
	ROM_REGION( 0x600000, "sprites", 0 ) // note, ROM_LOAD32_BYTE
	ROM_LOAD32_BYTE( "proto_039.c1", 0x000000, 0x100000, CRC(7192a787) SHA1(7bef6ce79c618103485480aee3c6f856968eb51f) )
	ROM_LOAD32_BYTE( "proto_039.c2", 0x000002, 0x100000, CRC(7157eca1) SHA1(65f36c6a3834775b04076d2c38a6047bffe9a8cf) )
	ROM_LOAD32_BYTE( "proto_039.c3", 0x000001, 0x100000, CRC(11d75727) SHA1(5a4c7b5ca3f1195e7853b45c5e71c13fe74d16e9) )
	ROM_LOAD32_BYTE( "proto_039.c4", 0x000003, 0x100000, CRC(7ad48b28) SHA1(27e65d948f08c231107cb1a810e2b06731091fc3) )
	ROM_LOAD32_BYTE( "proto_039.c5", 0x400000, 0x080000, CRC(5bdaf9ca) SHA1(60620d42ac6cd0e5da019fede2814a2f4171ff3f) )
	ROM_LOAD32_BYTE( "proto_039.c6", 0x400002, 0x080000, CRC(21d4be8c) SHA1(f1b19d37d52d21584f304b7d37d5c096b58219d6) )
	ROM_LOAD32_BYTE( "proto_039.c7", 0x400001, 0x080000, CRC(da55fd00) SHA1(52804f955597591fdd1d7478dc340b36d3c08c4a) )
	ROM_LOAD32_BYTE( "proto_039.c8", 0x400003, 0x080000, CRC(592e9267) SHA1(0d27de59970ccbcaa1d47909ea3d741ffb0d9e07) )
ROM_END

/****************************************
 ID-0040
 . NGM-040
 NEO-MVS PROG 4096 / NEO-MVS CHA 42G-2
 . NGH-040
 NEO-AEG PROG16 / NEO-AEG CHA42G-1
****************************************/

ROM_START( sengoku2 )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "040.p1", 0x000000, 0x100000, CRC(6dde02c2) SHA1(e432e63feb88c71629ec96aa84650dcfe356a551) )

	NEO_SFIX_128K( "040.s1", CRC(cd9802a3) SHA1(f685d4638f4f68e7e3f101c0c39128454536721b) )

	NEO_BIOS_AUDIO_128K( "040.m1", CRC(d4de4bca) SHA1(ecf604d06f01d40b04e285facef66a6ae2d35661) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "040.v1", 0x000000, 0x200000, CRC(71cb4b5d) SHA1(56d9aca1d476c19c7d0f707176a8fed53e0189b7) )
	// AES has different label, data is the same: 040-v1.v2
	ROM_LOAD( "040.v2", 0x200000, 0x100000, CRC(c5cece01) SHA1(923a3377dac1919e8c3d9ab316902250caa4785f) )
	// AES has different label, data is the same: 040-v2.v4

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD16_BYTE( "040.c1", 0x000000, 0x100000, CRC(faa8ea99) SHA1(714575e57ea1990612f960ec42b38d2e157ad400) )
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_LOAD16_BYTE( "040.c2", 0x000001, 0x100000, CRC(87d0ec65) SHA1(23645e0cf859fb4cec3745b3846ca0ef64c689fb) )
	ROM_CONTINUE( 0x400001, 0x100000 )
	ROM_LOAD16_BYTE( "040.c3", 0x200000, 0x080000, CRC(24b5ba80) SHA1(29d58a6b56bd24ee2046a8d45e023b4d7ab7685b) )
	ROM_LOAD16_BYTE( "040.c4", 0x200001, 0x080000, CRC(1c9e9930) SHA1(d017474873750a7602b7708c663d29b25ef7bb63) )
ROM_END

/****************************************
 ID-0041
 . NGM-041
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . NGH-041
 NEO-AEG PROG42G-1 / NEO-AEG CHA42G-1
****************************************/

ROM_START( bstars2 )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "041.p1", 0x000000, 0x080000, CRC(523567fd) SHA1(f1e81eb4678f586b214ea102cde6effea1b0f768) )

	NEO_SFIX_128K( "041.s1", CRC(015c5c94) SHA1(f1c60cd3dc54986b39f630ef3bf48f68c68695dc) )

	NEO_BIOS_AUDIO_128K( "041.m1", CRC(15c177a6) SHA1(3f4abed635102f9bc8b44809750828c82e79b44f) )

	ROM_REGION( 0x280000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "041.v1", 0x000000, 0x100000, CRC(cb1da093) SHA1(4f4d1d5fefa9dda372083c045bf0d268a57ce8f1) )
	ROM_LOAD( "041.v2", 0x100000, 0x100000, CRC(1c954a9d) SHA1(159bc6efdd531615461f6e16f83f6d4c4e67c237) )
	ROM_LOAD( "041.v3", 0x200000, 0x080000, CRC(afaa0180) SHA1(c4a047e21f093830498a163598ed7bd48a8cf9d1) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "041.c1", 0x000000, 0x100000, CRC(b39a12e1) SHA1(bafe383bd7c5a6aac4cb92dabbc56e3672fe174d) )
	ROM_LOAD16_BYTE( "041.c2", 0x000001, 0x100000, CRC(766cfc2f) SHA1(79e1063925d54a57df943019a88bea56c9152df3) )
	ROM_LOAD16_BYTE( "041.c3", 0x200000, 0x100000, CRC(fb31339d) SHA1(f4e821299680970b2e979acc4a170029b968c807) )
	ROM_LOAD16_BYTE( "041.c4", 0x200001, 0x100000, CRC(70457a0c) SHA1(a1e307f11ddab85d2e9c09d0428fac2e6da774b1) )
ROM_END

/****************************************
 ID-0042
 . NGM-042
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . NGH-042
 NEO-AEG PROG42G-1 / NEO-AEG CHA42G-1
****************************************/

ROM_START( quizdai2 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "042.p1", 0x000000, 0x100000, CRC(ed719dcf) SHA1(12baf2601e86c0e4358517b9fa1c55f2f5835f1d) )

	NEO_SFIX_128K( "042.s1", CRC(164fd6e6) SHA1(dad35bedc33d502a5ae745a45a972af8d901b160) )

	NEO_BIOS_AUDIO_128K( "042.m1", CRC(bb19995d) SHA1(ed458fad5a23c6bd0d099927d98c31e1e6562d1b) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "042.v1", 0x000000, 0x100000, CRC(af7f8247) SHA1(99a47014017c20e4e22010c60612b6b7f6efc9e5) )
	ROM_LOAD( "042.v2", 0x100000, 0x100000, CRC(c6474b59) SHA1(a6c5054032b698116247b2f09a8b94a1b588c4f1) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "042.c1", 0x000000, 0x100000, CRC(cb5809a1) SHA1(b53d06685246dd51b82b5c1d54d639d10e2ec26d) )
	ROM_LOAD16_BYTE( "042.c2", 0x000001, 0x100000, CRC(1436dfeb) SHA1(27d136fb1be793bd345a741f5e55a977275fff86) )
	ROM_LOAD16_BYTE( "042.c3", 0x200000, 0x080000, CRC(bcd4a518) SHA1(f355298fe0f2cf50ddcc0d613db56a5c04d7230f) )
	ROM_LOAD16_BYTE( "042.c4", 0x200001, 0x080000, CRC(d602219b) SHA1(34cf0f16db1e224396464ac838f4cd2e6d1c640e) )
ROM_END

/****************************************
 ID-0043
 . NGM-043
 NEO-MVS PROG 4096 / NEO-MVS CHA 42G-2
 NEO-MVS PROG-G2 / NEO-MVS CHA 42G-2
 . NGH-043
 NEO-AEG PROG16 / NEO-AEG CHA42G-1
****************************************/

ROM_START( 3countb ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "043.p1", 0x000000, 0x100000, CRC(ffbdd928) SHA1(05b24655ca32723661adc5509b450824deb0c176) )

	NEO_SFIX_128K( "043.s1", CRC(c362d484) SHA1(a3c029292572842feabe9aa8c3372628fb63978d) )

	NEO_BIOS_AUDIO_128K( "043.m1", CRC(7eab59cb) SHA1(5ae4107457e091f73960bfba39b589ae36d51ca3) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "043.v1", 0x000000, 0x200000, CRC(63688ce8) SHA1(5c6ac29a0cc0655a87cfe3ada8706838b86b86e4) )
	ROM_LOAD( "043.v2", 0x200000, 0x200000, CRC(c69a827b) SHA1(f5197ea87bb6573fa6aef3a1713c3679c58c1e74) )

	ROM_REGION( 0x0800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "043.c1", 0x000000, 0x100000, CRC(bad2d67f) SHA1(04928e50ca75b7fbc52b64e816ec5701901f5893) )
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_LOAD16_BYTE( "043.c2", 0x000001, 0x100000, CRC(a7fbda95) SHA1(9da3c5faf22592a7eaf8df9fa6454f48c2a927ae) )
	ROM_CONTINUE( 0x400001, 0x100000 )
	ROM_LOAD16_BYTE( "043.c3", 0x200000, 0x100000, CRC(f00be011) SHA1(2721cdba37a511a966a2a53b9bd6240f181d920c) )
	ROM_CONTINUE( 0x600000, 0x100000 )
	ROM_LOAD16_BYTE( "043.c4", 0x200001, 0x100000, CRC(1887e5c0) SHA1(9b915359add7c10c78d8b281b4084eceea8f0499) )
	ROM_CONTINUE( 0x600001, 0x100000 )
ROM_END

/****************************************
 ID-0044
 . NGM-044
 NEO-MVS PROG16 / NEO-MVS CHA42G-1
 NEO-MVS PROG4096 / NEO-MVS CHA42G-1
 . NGH-044
 NEO-AEG PROG16 / NEO-AEG CHA42G-1
****************************************/

ROM_START( aof ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "044.p1", 0x000000, 0x080000, CRC(ca9f7a6d) SHA1(4d28ef86696f7e832510a66d3e8eb6c93b5b91a1) )

	NEO_SFIX_128K( "044.s1", CRC(89903f39) SHA1(a04a0c244a5d5c7a595fcf649107969635a6a8b6) )

	NEO_BIOS_AUDIO_128K( "044.m1", CRC(0987e4bb) SHA1(8fae4b7fac09d46d4727928e609ed9d3711dbded) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "044.v2", 0x000000, 0x200000, CRC(3ec632ea) SHA1(e3f413f580b57f70d2dae16dbdacb797884d3fce) )
	ROM_LOAD( "044.v4", 0x200000, 0x200000, CRC(4b0f8e23) SHA1(105da0cc5ba19869c7147fba8b177500758c232b) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "044.c1", 0x000000, 0x100000, CRC(ddab98a7) SHA1(f20eb81ec431268798c142c482146c1545af1c24) )
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_LOAD16_BYTE( "044.c2", 0x000001, 0x100000, CRC(d8ccd575) SHA1(f697263fe92164e274bf34c55327b3d4a158b332) )
	ROM_CONTINUE( 0x400001, 0x100000 )
	ROM_LOAD16_BYTE( "044.c3", 0x200000, 0x100000, CRC(403e898a) SHA1(dd5888f8b24a33b2c1f483316fe80c17849ccfc4) )
	ROM_CONTINUE( 0x600000, 0x100000 )
	ROM_LOAD16_BYTE( "044.c4", 0x200001, 0x100000, CRC(6235fbaa) SHA1(9090e337d7beed25ba81ae0708d0aeb57e6cf405) )
	ROM_CONTINUE( 0x600001, 0x100000 )
ROM_END

/****************************************
 ID-0045
 . NGM-045
 NEO-MVS PROGGSC / NEO-MVS CHA 42G-3
 . NGH-045
 NEO-AEG PROGGS / NEO-AEG CHA42G-4
****************************************/

ROM_START( samsho ) /* MVS VERSION */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "045.p1",   0x000000, 0x100000, CRC(dfe51bf0) SHA1(2243af3770a516ae698b69bcd9daf53632d9128d) )
	ROM_LOAD16_WORD_SWAP( "045.p2", 0x100000, 0x100000, CRC(46745b94) SHA1(d9e959fd1f88c9402915c1d0dcdb4a9e3d49cdcb) )

	NEO_SFIX_128K( "045.s1", CRC(9142a4d3) SHA1(54088e99fcfd75fd0f94852890a56350066a05a3) )

	NEO_BIOS_AUDIO_128K( "045.m1", CRC(95170640) SHA1(125c502db0693e8d11cef619b090081c14a9a300) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "045.v1", 0x000000, 0x200000, CRC(37f78a9b) SHA1(6279b497d12fa90b49ab5ac3aae20fb302ec8b81) )
	ROM_LOAD( "045.v2", 0x200000, 0x200000, CRC(568b20cf) SHA1(61af858685472a1fad608e230cccc2b108509ddb) )

	ROM_REGION( 0xa00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "045.c1", 0x000000, 0x200000, CRC(2e5873a4) SHA1(65c74c1e2d34390666bbb630df7d1f4c9570c3db) )
	ROM_LOAD16_BYTE( "045.c2", 0x000001, 0x200000, CRC(04febb10) SHA1(16a8cbf0fd9468e81bf9eab6dbe7a8e3623a843e) )
	ROM_LOAD16_BYTE( "045.c3", 0x400000, 0x200000, CRC(f3dabd1e) SHA1(c80e52df42be9f8b2e89b467b11ab140a480cee8) )
	ROM_LOAD16_BYTE( "045.c4", 0x400001, 0x200000, CRC(935c62f0) SHA1(0053d40085fac14096b683f4341f65e543b71dc1) )
	ROM_LOAD16_BYTE( "045.c5", 0x800000, 0x100000, CRC(81932894) SHA1(550f15dc5892c4602422c51869f0d59f70f01e9e) )
	ROM_LOAD16_BYTE( "045.c6", 0x800001, 0x100000, CRC(be30612e) SHA1(5e8b785f917c176d6796eba0caed37b13ddb3e63) )
ROM_END

ROM_START( samshoh ) /* AES VERSION */
	ROM_REGION( 0x180000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "045.p1",  0x000000, 0x100000, CRC(dfe51bf0) SHA1(2243af3770a516ae698b69bcd9daf53632d9128d) )
	ROM_LOAD16_WORD_SWAP( "045h.p2", 0x100000, 0x080000, CRC(38ee9ba9) SHA1(48190699a6be83cb6257365ae81f93fdd23abe09) )

	NEO_SFIX_128K( "045.s1", CRC(9142a4d3) SHA1(54088e99fcfd75fd0f94852890a56350066a05a3) )

	NEO_BIOS_AUDIO_128K( "045.m1", CRC(95170640) SHA1(125c502db0693e8d11cef619b090081c14a9a300) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "045.v1", 0x000000, 0x200000, CRC(37f78a9b) SHA1(6279b497d12fa90b49ab5ac3aae20fb302ec8b81) )
	ROM_LOAD( "045.v2", 0x200000, 0x200000, CRC(568b20cf) SHA1(61af858685472a1fad608e230cccc2b108509ddb) )

	ROM_REGION( 0x900000, "sprites", 0 )
	ROM_LOAD16_BYTE( "045.c1", 0x000000, 0x200000, CRC(2e5873a4) SHA1(65c74c1e2d34390666bbb630df7d1f4c9570c3db) )
	ROM_LOAD16_BYTE( "045.c2", 0x000001, 0x200000, CRC(04febb10) SHA1(16a8cbf0fd9468e81bf9eab6dbe7a8e3623a843e) )
	ROM_LOAD16_BYTE( "045.c3", 0x400000, 0x200000, CRC(f3dabd1e) SHA1(c80e52df42be9f8b2e89b467b11ab140a480cee8) )
	ROM_LOAD16_BYTE( "045.c4", 0x400001, 0x200000, CRC(935c62f0) SHA1(0053d40085fac14096b683f4341f65e543b71dc1) )
	ROM_LOAD16_BYTE( "045h.c5", 0x800000, 0x080000, CRC(a2bb8284) SHA1(aa118e3b8c062daa219b36758b9a3814c08c69dc) )
	ROM_LOAD16_BYTE( "045h.c6", 0x800001, 0x080000, CRC(4fa71252) SHA1(afe374a9d1f2d955a59efe7b6196b89e021b164c) )
ROM_END

ROM_START( samshoa )
	ROM_REGION( 0x180000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "045b.p1", 0x000000, 0x080000, CRC(80aa6c97) SHA1(6e07a4aa7b4719ae487a10cee9389cb55a370a7a) )
	ROM_LOAD16_WORD_SWAP( "045b.p3", 0x080000, 0x080000, CRC(71768728) SHA1(9ff0e01d3fb73ad04279d4fdf4c53c3160888179) )
	ROM_LOAD16_WORD_SWAP( "045b.p2", 0x100000, 0x080000, CRC(38ee9ba9) SHA1(48190699a6be83cb6257365ae81f93fdd23abe09) )

	NEO_SFIX_128K( "045.s1", CRC(9142a4d3) SHA1(54088e99fcfd75fd0f94852890a56350066a05a3) )

	NEO_BIOS_AUDIO_128K( "045.m1", CRC(95170640) SHA1(125c502db0693e8d11cef619b090081c14a9a300) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "045.v1", 0x000000, 0x200000, CRC(37f78a9b) SHA1(6279b497d12fa90b49ab5ac3aae20fb302ec8b81) )
	ROM_LOAD( "045.v2", 0x200000, 0x200000, CRC(568b20cf) SHA1(61af858685472a1fad608e230cccc2b108509ddb) )

	ROM_REGION( 0x900000, "sprites", 0 )
	ROM_LOAD16_BYTE( "045.c1", 0x000000, 0x200000, CRC(2e5873a4) SHA1(65c74c1e2d34390666bbb630df7d1f4c9570c3db) )
	ROM_LOAD16_BYTE( "045.c2", 0x000001, 0x200000, CRC(04febb10) SHA1(16a8cbf0fd9468e81bf9eab6dbe7a8e3623a843e) )
	ROM_LOAD16_BYTE( "045.c3", 0x400000, 0x200000, CRC(f3dabd1e) SHA1(c80e52df42be9f8b2e89b467b11ab140a480cee8) )
	ROM_LOAD16_BYTE( "045.c4", 0x400001, 0x200000, CRC(935c62f0) SHA1(0053d40085fac14096b683f4341f65e543b71dc1) )
	ROM_LOAD16_BYTE( "045b.c5", 0x800000, 0x080000, CRC(a2bb8284) SHA1(aa118e3b8c062daa219b36758b9a3814c08c69dc) )
	ROM_LOAD16_BYTE( "045b.c6", 0x800001, 0x080000, CRC(4fa71252) SHA1(afe374a9d1f2d955a59efe7b6196b89e021b164c) )
ROM_END

/****************************************
 ID-0046
 . NGM-046
 NEO-MVS PROGTOP / NEO-MVS CHA256B
 . NGH-046
 NEO-AEG PROGTOP / NEO-AEG CHA256[B]
****************************************/

ROM_START( tophuntr ) /* MVS VERSION */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "046.p1",  0x000000, 0x100000, CRC(69fa9e29) SHA1(9a40a16163193bb506a32bd34f6323b25ec69622) )
	ROM_LOAD16_WORD_SWAP( "046.p2", 0x100000, 0x100000, CRC(f182cb3e) SHA1(6b4e0af5d4e623f0682f37ff5c69e5b705e20028) )

	NEO_SFIX_128K( "046.s1", CRC(14b01d7b) SHA1(618ce75c25d6cc86a3b46bd64a0aa34ab82f75ae) )

	NEO_BIOS_AUDIO_128K( "046.m1", CRC(3f84bb9f) SHA1(07446040871d11da3c2217ee9d1faf8c3cae7420) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "046.v1", 0x000000, 0x100000, CRC(c1f9c2db) SHA1(bed95a76afefa46503a12e0f0a9787c4c967ac50) )
	ROM_LOAD( "046.v2", 0x100000, 0x100000, CRC(56254a64) SHA1(1cf049cb4c414419859d2c8ee714317a35a85251) )
	ROM_LOAD( "046.v3", 0x200000, 0x100000, CRC(58113fb1) SHA1(40972982a63c7adecef840f9882f4165da723ab6) )
	ROM_LOAD( "046.v4", 0x300000, 0x100000, CRC(4f54c187) SHA1(63a76949301b83bdd44aa1a4462f642ab9ca3c0b) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "046.c1", 0x000000, 0x100000, CRC(fa720a4a) SHA1(364913b9fa40d46e4e39ae3cdae914cfd0de137d) )
	ROM_LOAD16_BYTE( "046.c2", 0x000001, 0x100000, CRC(c900c205) SHA1(50274e79aa26f334eb806288688b30720bade883) )
	ROM_LOAD16_BYTE( "046.c3", 0x200000, 0x100000, CRC(880e3c25) SHA1(b6974af0c833b766866919b6f15b6f8cef82530d) )
	ROM_LOAD16_BYTE( "046.c4", 0x200001, 0x100000, CRC(7a2248aa) SHA1(8af0b26025a54e3b91604dd24a3c1c518fbd8536) )
	ROM_LOAD16_BYTE( "046.c5", 0x400000, 0x100000, CRC(4b735e45) SHA1(2f8b46388c4696aee6a97e1e21cdadf6b142b01a) )
	ROM_LOAD16_BYTE( "046.c6", 0x400001, 0x100000, CRC(273171df) SHA1(9c35832221e016c12ef1ed71da167f565daaf86c) )
	ROM_LOAD16_BYTE( "046.c7", 0x600000, 0x100000, CRC(12829c4c) SHA1(ac5f3d848d7116fc35c97f53a72c85e049dd3a2f) )
	ROM_LOAD16_BYTE( "046.c8", 0x600001, 0x100000, CRC(c944e03d) SHA1(be23999b8ce09ee15ba500ce4d5e2a82a4f58d9b) )
ROM_END

ROM_START( tophuntrh ) /* AES VERSION */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "046.p1",0x000000, 0x100000, CRC(771e39bc) SHA1(c0e05fd1ca81926438bb75e2fa6894e40ab6521e) )
	ROM_LOAD16_WORD_SWAP( "046.p2",0x100000, 0x100000, CRC(f182cb3e) SHA1(6b4e0af5d4e623f0682f37ff5c69e5b705e20028) )

	NEO_SFIX_128K( "046-sg1.s1", CRC(92e9ac8c) SHA1(cab5c77c091e8d12d9c3a2cc8d741b74e4386efb) )

	NEO_BIOS_AUDIO_128K( "046.m1", CRC(3f84bb9f) SHA1(07446040871d11da3c2217ee9d1faf8c3cae7420) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "046.v1", 0x000000, 0x100000, CRC(c1f9c2db) SHA1(bed95a76afefa46503a12e0f0a9787c4c967ac50) )
	ROM_LOAD( "046.v2", 0x100000, 0x100000, CRC(56254a64) SHA1(1cf049cb4c414419859d2c8ee714317a35a85251) )
	ROM_LOAD( "046.v3", 0x200000, 0x100000, CRC(58113fb1) SHA1(40972982a63c7adecef840f9882f4165da723ab6) )
	ROM_LOAD( "046.v4", 0x300000, 0x100000, CRC(4f54c187) SHA1(63a76949301b83bdd44aa1a4462f642ab9ca3c0b) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "046.c1", 0x000000, 0x100000, CRC(fa720a4a) SHA1(364913b9fa40d46e4e39ae3cdae914cfd0de137d) )
	ROM_LOAD16_BYTE( "046.c2", 0x000001, 0x100000, CRC(c900c205) SHA1(50274e79aa26f334eb806288688b30720bade883) )
	ROM_LOAD16_BYTE( "046.c3", 0x200000, 0x100000, CRC(880e3c25) SHA1(b6974af0c833b766866919b6f15b6f8cef82530d) )
	ROM_LOAD16_BYTE( "046.c4", 0x200001, 0x100000, CRC(7a2248aa) SHA1(8af0b26025a54e3b91604dd24a3c1c518fbd8536) )
	ROM_LOAD16_BYTE( "046.c5", 0x400000, 0x100000, CRC(4b735e45) SHA1(2f8b46388c4696aee6a97e1e21cdadf6b142b01a) )
	ROM_LOAD16_BYTE( "046.c6", 0x400001, 0x100000, CRC(273171df) SHA1(9c35832221e016c12ef1ed71da167f565daaf86c) )
	ROM_LOAD16_BYTE( "046.c7", 0x600000, 0x100000, CRC(12829c4c) SHA1(ac5f3d848d7116fc35c97f53a72c85e049dd3a2f) )
	ROM_LOAD16_BYTE( "046.c8", 0x600001, 0x100000, CRC(c944e03d) SHA1(be23999b8ce09ee15ba500ce4d5e2a82a4f58d9b) )
ROM_END

/****************************************
 ID-0047
 . NGM-047
 NEO-MVS PROG-G2 (SNK-9201) / NEO-MVS CHA42G-1
 . NGH-047
 NEO-AEG PROG-G2 (PRO-CT0) / NEO-AEG CHA42G-2B
 NEO-AEG PROG-G2 (PRO-CT0) / NEO-AEG CHA42G-2
****************************************/

ROM_START( fatfury2 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "047.p1", 0x000000, 0x100000, CRC(ecfdbb69) SHA1(59e2f137c6eaf043df4ddae865a9159a10265c60) )

	NEO_SFIX_128K( "047.s1", CRC(d7dbbf39) SHA1(29253e596f475ebd41a6e3bb53952e3a0ccd2eed) )

	NEO_BIOS_AUDIO_128K( "047.m1", CRC(820b0ba7) SHA1(5708248d89446e49184eaadb52f7c61b2b6c13c5) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "047.v1", 0x000000, 0x200000, CRC(d9d00784) SHA1(f6a91eada8c23aa4518c4b82eeebca69f79d845c) )
	ROM_LOAD( "047.v2", 0x200000, 0x200000, CRC(2c9a4b33) SHA1(d4a1c0951c02c8919b3ec32ed96933634ff9e54c) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "047.c1", 0x000000, 0x100000, CRC(f72a939e) SHA1(67fc398ec28061adca0d3be82bbe7297015800da) )
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_LOAD16_BYTE( "047.c2", 0x000001, 0x100000, CRC(05119a0d) SHA1(c2f100b73eb04f65b6ba6089d49aceb51b470ec6) )
	ROM_CONTINUE( 0x400001, 0x100000 )
	ROM_LOAD16_BYTE( "047.c3", 0x200000, 0x100000, CRC(01e00738) SHA1(79654f24d777dd5eb68bafc3b8cb9db71d5822e2) )
	ROM_CONTINUE( 0x600000, 0x100000 )
	ROM_LOAD16_BYTE( "047.c4", 0x200001, 0x100000, CRC(9fe27432) SHA1(89d22d77ba8bc6d1f6c974195c34ad61b9010de7) )
	ROM_CONTINUE( 0x600001, 0x100000 )
ROM_END

/****************************************
 ID-0048
 . ??M-048
 NEO-MVS PROGGSC / NEO-MVS CHA256
****************************************/

ROM_START( janshin ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "048.p1", 0x000000, 0x100000, CRC(fa818cbb) SHA1(afee2c897b766c84f13891fb52c574fb18df0951) )

	NEO_SFIX_128K( "048.s1", CRC(8285b25a) SHA1(d983640cda3e346e38469b4d3ec8048b116a7bb7) )

	NEO_BIOS_AUDIO_128K( "048.m1", CRC(310467c7) SHA1(c529961195c9bdf5d1ce70a38ad129002d1f3b5f) )

	ROM_DEFAULT_BIOS( "japan" ) /* so the mahjong panel will work in the service menu */

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "048.v1", 0x000000, 0x200000, CRC(f1947d2b) SHA1(955ff91ab24eb2a7ec51ff46c9f9f2ec060456b2) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "048.c1", 0x000000, 0x200000, CRC(3fa890e9) SHA1(e73d2802bacfbc2b2b16fbbedddde17488e4bbde) )
	ROM_LOAD16_BYTE( "048.c2", 0x000001, 0x200000, CRC(59c48ad8) SHA1(2630817e735a6d197377558f4324c1442803fe15) )
ROM_END

/****************************************
 ID-0049
 . NGM-049
 NEO-MVS PROG16 / NEO-MVS CHA42G-1
 . NGH-049
 NEO-AEG PROG16 / NEO-AEG CHA42G-1
****************************************/

ROM_START( androdun ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "049.p1", 0x000000, 0x080000, CRC(3b857da2) SHA1(4dd86c739944696c16c3cdd85935d6dfa9fdc276) )
	ROM_LOAD16_WORD_SWAP( "049.p2", 0x080000, 0x080000, CRC(2f062209) SHA1(991cf3e3677929b2cc0b2787b0c7b6ad3700f618) )

	NEO_SFIX_128K( "049.s1", CRC(6349de5d) SHA1(bcc44b9576d7bedd9a39294530bb66f707690c72) )

	NEO_BIOS_AUDIO_128K( "049.m1", CRC(edd2acf4) SHA1(c4ee6ba834d54b9fc5a854dbc41a05877e090371) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "049.v1", 0x000000, 0x100000, CRC(ce43cb89) SHA1(47f82e077abb6efc6b1b0490412ae147d5d2acef) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "049.c1", 0x000000, 0x100000, CRC(7ace6db3) SHA1(c41cc9de8c0788dcc49ca494fd3bb3124062d9dd) )
	ROM_LOAD16_BYTE( "049.c2", 0x000001, 0x100000, CRC(b17024f7) SHA1(fcf7efae48fcdccaf5255c145de414fb246128f0) )
ROM_END

/****************************************
 ID-0050
 . ALM-004
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . ALH-004
 NEO-AEG PROG42G-1 / NEO-AEG CHA42G-1
****************************************/

ROM_START( ncommand )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "050.p1", 0x000000, 0x100000, CRC(4e097c40) SHA1(43311a7ca14a14dcd4a99d8576a12e897b078643) )

	NEO_SFIX_128K( "050.s1", CRC(db8f9c8e) SHA1(11cb82cf3c4d0fc2da5df0c26410a64808093610) )

	NEO_BIOS_AUDIO_128K( "050.m1", CRC(6fcf07d3) SHA1(e9ecff4bfec1f5964bf06645f75d80d611b6231c) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "050.v1", 0x000000, 0x100000, CRC(23c3ab42) SHA1(b6c59bb180f1aa34c95f3ec923f3aafb689d57b0) )
	ROM_LOAD( "050.v2", 0x100000, 0x080000, CRC(80b8a984) SHA1(950cf0e78ceffa4037663f1086fbbc88588f49f2) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "050.c1", 0x000000, 0x100000, CRC(87421a0a) SHA1(1d8faaf03778f7c5b062554d7333bbd3f0ca12ad) )
	ROM_LOAD16_BYTE( "050.c2", 0x000001, 0x100000, CRC(c4cf5548) SHA1(ef9eca5aeff9dda2209a050c2af00ed8979ae2bc) )
	ROM_LOAD16_BYTE( "050.c3", 0x200000, 0x100000, CRC(03422c1e) SHA1(920e5015aebe2ffc5ce43a52365c7f0a705f3b9e) )
	ROM_LOAD16_BYTE( "050.c4", 0x200001, 0x100000, CRC(0845eadb) SHA1(3c71a02bf0e07a5381846bb6d75bbe7dd546adea) )
ROM_END

/****************************************
 ID-0051
 . AIM-051
 NEO-MVS PROG-G2 / NEO-MVS CHA42G-1
 NEO-MVS PROG 4096 / NEO-MVS CHA 42G-2
 . AIH-051
****************************************/

ROM_START( viewpoin )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "051.p1", 0x000000, 0x100000, CRC(17aa899d) SHA1(674cd8ace7acdf4f407de741e3d0071bcb49c902) )

	NEO_SFIX_128K( "051.s1", CRC(9fea5758) SHA1(5c6f01da89f2639cf741ee7c39e27023b8083052) )

	NEO_BIOS_AUDIO_128K( "051.m1", CRC(8e69f29a) SHA1(7a25f4997996434ea1b7d0d1ca9e7aaf966cbd03) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "051.v1", 0x000000, 0x200000, CRC(019978b6) SHA1(7896a551115fc6ed38b5944e0c8dcb2b2c1c077d) )
	ROM_LOAD( "051.v2", 0x200000, 0x200000, CRC(5758f38c) SHA1(da10f4b7d22d9139bbf068bd940be82168a74ca1) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD16_BYTE( "051.c1", 0x000000, 0x100000, CRC(d624c132) SHA1(49c7e9f020cba45d7083b45252bcc03397f8c286) )
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_LOAD16_BYTE( "051.c2", 0x000001, 0x100000, CRC(40d69f1e) SHA1(ec4a13582772594957f927622d50f54b0dfcd8d8) )
	ROM_CONTINUE( 0x400001, 0x100000 )
ROM_END

/****************************************
 ID-0052
 . NGM-052
 NEO-MVS PROG-G2 (SNK-9201) / NEO-MVS CHA 42G-2
 . NGH-052
 NEO-AEG PROG-G2 (SNK-9201) / NEO-AEG CHA42G-2
****************************************/

ROM_START( ssideki )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "052.p1", 0x000000, 0x080000, CRC(9cd97256) SHA1(1c780b711137fd79cc81b01941e84f3d59e0071f) )

	NEO_SFIX_128K( "052.s1", CRC(97689804) SHA1(fa8dab3b3353d7115a0368f3fc749950c0186fbc) )

	NEO_BIOS_AUDIO_128K( "052.m1", CRC(49f17d2d) SHA1(70971fcf71ae3a6b2e26e7ade8063941fb178ae5) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "052.v1", 0x000000, 0x200000, CRC(22c097a5) SHA1(328c4e6db0a026f54a633cff1443a3f964a8daea) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD16_BYTE( "052.c1", 0x000000, 0x100000, CRC(53e1c002) SHA1(2125b1be379ea7933893ffb1cd65d6c4bf8b03bd) )
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_LOAD16_BYTE( "052.c2", 0x000001, 0x100000, CRC(776a2d1f) SHA1(bca0bac87443e9e78c623d284f6cc96cc9c9098f) )
	ROM_CONTINUE( 0x400001, 0x100000 )
ROM_END

/****************************************
 ID-0053
 . ALM-005
 NEO-MVS PROG16 / NEO-MVS CHA42G-1
 . ALH-005
 NEO-AEG PROG16 / NEO-AEG CHA42G-1
 NEO-AEG PROG-G2 / NEO-AEG CHA42G-2C
****************************************/

ROM_START( wh1 ) /* MVS VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "053.p1", 0x000000, 0x080000, CRC(d42e1e9a) SHA1(9d1911fe4bf6202466ec45557dd008cbf01ca9c6) )
	ROM_LOAD16_WORD_SWAP( "053.p2", 0x080000, 0x080000, CRC(0e33e8a3) SHA1(4b7086edb504f3c30529d51ba8f453d48eba5164) )
	/* P's on eprom, correct chip label unknown */

	NEO_SFIX_128K( "053.s1", CRC(8c2c2d6b) SHA1(87fa79611c6f8886dcc8766814829c669c65b40f) )

	NEO_BIOS_AUDIO_128K( "053.m1", CRC(1bd9d04b) SHA1(65cd7b002123ed1a3111e3d942608d0082799ff3) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "053.v2", 0x000000, 0x200000, CRC(a68df485) SHA1(007fa715423fba72c899cd3db3f4bec13281cf7a) )
	ROM_LOAD( "053.v4", 0x200000, 0x100000, CRC(7bea8f66) SHA1(428e8721bd87f7faa756adb1e12672219be46c1d) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD16_BYTE( "053.c1", 0x000000, 0x100000, CRC(85eb5bce) SHA1(3d03d29296ca6e6b5106aac4aaeec9d4b4ed1313) )
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_LOAD16_BYTE( "053.c2", 0x000001, 0x100000, CRC(ec93b048) SHA1(d4159210df94e259f874a4671d271ec27be13451) )
	ROM_CONTINUE( 0x400001, 0x100000 )
	ROM_LOAD16_BYTE( "053.c3", 0x200000, 0x100000, CRC(0dd64965) SHA1(e97b3b8a461da5e8861b3dfdacb25e007ced37a1) )
	ROM_LOAD16_BYTE( "053.c4", 0x200001, 0x100000, CRC(9270d954) SHA1(a2ef909868f6b06cdcc22a63ddf6c96be12b999c) )
ROM_END

ROM_START( wh1h ) /* AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "053h.p1", 0x000000, 0x080000, CRC(95b574cb) SHA1(b7b7af6a04c3d902e7f8852897741ecaf0b1062c) )
	ROM_LOAD16_WORD_SWAP( "053h.p2", 0x080000, 0x080000, CRC(f198ed45) SHA1(24ccc091e97f63796562bb5b30df51f39bd504ef) )

	NEO_SFIX_128K( "053.s1", CRC(8c2c2d6b) SHA1(87fa79611c6f8886dcc8766814829c669c65b40f) )

	NEO_BIOS_AUDIO_128K( "053.m1", CRC(1bd9d04b) SHA1(65cd7b002123ed1a3111e3d942608d0082799ff3) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "053.v2", 0x000000, 0x200000, CRC(a68df485) SHA1(007fa715423fba72c899cd3db3f4bec13281cf7a) )
	ROM_LOAD( "053.v4", 0x200000, 0x100000, CRC(7bea8f66) SHA1(428e8721bd87f7faa756adb1e12672219be46c1d) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD16_BYTE( "053.c1", 0x000000, 0x100000, CRC(85eb5bce) SHA1(3d03d29296ca6e6b5106aac4aaeec9d4b4ed1313) )
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_LOAD16_BYTE( "053.c2", 0x000001, 0x100000, CRC(ec93b048) SHA1(d4159210df94e259f874a4671d271ec27be13451) )
	ROM_CONTINUE( 0x400001, 0x100000 )
	ROM_LOAD16_BYTE( "053.c3", 0x200000, 0x100000, CRC(0dd64965) SHA1(e97b3b8a461da5e8861b3dfdacb25e007ced37a1) )
	ROM_LOAD16_BYTE( "053.c4", 0x200001, 0x100000, CRC(9270d954) SHA1(a2ef909868f6b06cdcc22a63ddf6c96be12b999c) )
ROM_END

ROM_START( wh1ha )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "053ha.p1", 0x000000, 0x080000, CRC(ed29fde2) SHA1(52b8ca5b804f786f95e1dfb348d8c7b82f1d4ddf) )
	ROM_LOAD16_WORD_SWAP( "053ha.p2", 0x080000, 0x080000, CRC(98f2b158) SHA1(a64e1425970eb53cc910891db39973dee3d54ccc) )

	NEO_SFIX_128K( "053.s1", CRC(8c2c2d6b) SHA1(87fa79611c6f8886dcc8766814829c669c65b40f) )

	NEO_BIOS_AUDIO_128K( "053.m1", CRC(1bd9d04b) SHA1(65cd7b002123ed1a3111e3d942608d0082799ff3) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "053.v2", 0x000000, 0x200000, CRC(a68df485) SHA1(007fa715423fba72c899cd3db3f4bec13281cf7a) )
	ROM_LOAD( "053.v4", 0x200000, 0x100000, CRC(7bea8f66) SHA1(428e8721bd87f7faa756adb1e12672219be46c1d) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD16_BYTE( "053.c1", 0x000000, 0x100000, CRC(85eb5bce) SHA1(3d03d29296ca6e6b5106aac4aaeec9d4b4ed1313) )
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_LOAD16_BYTE( "053.c2", 0x000001, 0x100000, CRC(ec93b048) SHA1(d4159210df94e259f874a4671d271ec27be13451) )
	ROM_CONTINUE( 0x400001, 0x100000 )
	ROM_LOAD16_BYTE( "053.c3", 0x200000, 0x100000, CRC(0dd64965) SHA1(e97b3b8a461da5e8861b3dfdacb25e007ced37a1) )
	ROM_LOAD16_BYTE( "053.c4", 0x200001, 0x100000, CRC(9270d954) SHA1(a2ef909868f6b06cdcc22a63ddf6c96be12b999c) )
ROM_END

/****************************************
 ID-0054
 Crossed Swords 2 (CD only? not confirmed, MVS might exist)
****************************************/

/****************************************
 ID-0055
 . NGM-055
 NEO-MVS PROGTOP / NEO-MVS CHA256
 NEO-MVS PROGTOP / NEO-MVS CHA256B
 . NGH-055
 NEO-AEG PROGRK / NEO-AEG CHA256
****************************************/

ROM_START( kof94 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "055.p1", 0x100000, 0x100000, CRC(f10a2042) SHA1(d08a3f3c28be4b1793de7d362456281329fe1828) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "055.s1", CRC(825976c1) SHA1(cb6a70bdd95d449d25196ca269b621c362db6743) )

	NEO_BIOS_AUDIO_128K( "055.m1", CRC(f6e77cf5) SHA1(292a3e3a4918ffe72bd1c41acb927b91844e035e) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "055.v1", 0x000000, 0x200000, CRC(8889596d) SHA1(c9ce713b720511438dbd3fe3bcc7c246f475c6a2) )
	ROM_LOAD( "055.v2", 0x200000, 0x200000, CRC(25022b27) SHA1(2b040a831c3c92ac6e4719de38009a0d55b64f6b) )
	ROM_LOAD( "055.v3", 0x400000, 0x200000, CRC(83cf32c0) SHA1(34a31a37eb10945b5169e96321bcea06eec33a00) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "055.c1", 0x000000, 0x200000, CRC(b96ef460) SHA1(e52f5303c17b50ce165c008be2837336369c110b) )
	ROM_LOAD16_BYTE( "055.c2", 0x000001, 0x200000, CRC(15e096a7) SHA1(237c2a3d059de00bfca66e0016ed325d7a32bfec) )
	ROM_LOAD16_BYTE( "055.c3", 0x400000, 0x200000, CRC(54f66254) SHA1(c594384bcd8b03beb8c595591505fecc44b185ac) )
	ROM_LOAD16_BYTE( "055.c4", 0x400001, 0x200000, CRC(0b01765f) SHA1(ec1fdcc944611408367bf5023d4ebe7edd9dfa88) )
	ROM_LOAD16_BYTE( "055.c5", 0x800000, 0x200000, CRC(ee759363) SHA1(8a5621c1b1f8267b9b9b6a14ab4944de542e1945) )
	ROM_LOAD16_BYTE( "055.c6", 0x800001, 0x200000, CRC(498da52c) SHA1(1e6e6202ee053a5261db889177ce3a087e078bda) )
	ROM_LOAD16_BYTE( "055.c7", 0xc00000, 0x200000, CRC(62f66888) SHA1(ac91a0eab0753bee175ad40213a4ae5d38ed5b87) )
	ROM_LOAD16_BYTE( "055.c8", 0xc00001, 0x200000, CRC(fe0a235d) SHA1(a45c66836e4e3c77dfef9d4c6cc422cb59169149) )
ROM_END

/****************************************
 ID-0056
 . NGM-056
 NEO-MVS PROGGSC / NEO-MVS CHA256
 . NGH-056
 NEO-AEG PROGRKB / NEO-AEG CHA256[B]
****************************************/

ROM_START( aof2 ) /* MVS VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "056.p1", 0x000000, 0x100000, CRC(a3b1d021) SHA1(ee42f3ca4516226b0088d0303ed28e3ecdabcd71) )

	NEO_SFIX_128K( "056.s1", CRC(8b02638e) SHA1(aa4d28804ca602da776948b5f223ea89e427906b) )

	NEO_BIOS_AUDIO_128K( "056.m1", CRC(f27e9d52) SHA1(dddae733d87ce7c88ad2580a8f64cb6ff9572e67) )

	ROM_REGION( 0x500000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "056.v1", 0x000000, 0x200000, CRC(4628fde0) SHA1(ece2a50f5270d844d58401b1447d1d856d78ea45) )
	ROM_LOAD( "056.v2", 0x200000, 0x200000, CRC(b710e2f2) SHA1(df4da585203eea7554d3ce718eb107e9cb6a0254) )
	ROM_LOAD( "056.v3", 0x400000, 0x100000, CRC(d168c301) SHA1(969273d1d11943e81560959359a2c4e69522af0e) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "056.c1", 0x000000, 0x200000, CRC(17b9cbd2) SHA1(1eee81e02763d384bd1c10a6012473ca931e4093) )
	ROM_LOAD16_BYTE( "056.c2", 0x000001, 0x200000, CRC(5fd76b67) SHA1(11925a41a53b53c6df4a5ebd28f98300950f743b) )
	ROM_LOAD16_BYTE( "056.c3", 0x400000, 0x200000, CRC(d2c88768) SHA1(22e2d84aa0c095944190e249ce87ef50d3f7b8ce) )
	ROM_LOAD16_BYTE( "056.c4", 0x400001, 0x200000, CRC(db39b883) SHA1(59de86c513dc4e230ae25d9e3b7e84621b657b54) )
	ROM_LOAD16_BYTE( "056.c5", 0x800000, 0x200000, CRC(c3074137) SHA1(9a75e3d63cb98d54f900dcfb3a03e21f3148d32f) )
	ROM_LOAD16_BYTE( "056.c6", 0x800001, 0x200000, CRC(31de68d3) SHA1(13ba7046cdd6863125f8284e60f102d4720af5a4) )
	ROM_LOAD16_BYTE( "056.c7", 0xc00000, 0x200000, CRC(3f36df57) SHA1(79ee97e9ae811a51141b535633f90e1491209d54) )
	ROM_LOAD16_BYTE( "056.c8", 0xc00001, 0x200000, CRC(e546d7a8) SHA1(74a2fca994a5a93a5784a46c0f68193122456a09) )
ROM_END

ROM_START( aof2a ) /* AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "056.p1",  0x000000, 0x100000, CRC(a3b1d021) SHA1(ee42f3ca4516226b0088d0303ed28e3ecdabcd71) )
	/* the rom below acts as a patch to the program rom in the cart, replacing the first 512kb */
	ROM_LOAD16_WORD_SWAP( "056a.p1", 0x000000, 0x80000, CRC(75d6301c) SHA1(e72d15fba55f96be7b4fa29e705a7b78f56edf7d) )

	NEO_SFIX_128K( "056.s1", CRC(8b02638e) SHA1(aa4d28804ca602da776948b5f223ea89e427906b) )

	NEO_BIOS_AUDIO_128K( "056.m1", CRC(f27e9d52) SHA1(dddae733d87ce7c88ad2580a8f64cb6ff9572e67) )

	ROM_REGION( 0x500000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "056.v1", 0x000000, 0x200000, CRC(4628fde0) SHA1(ece2a50f5270d844d58401b1447d1d856d78ea45) )
	ROM_LOAD( "056.v2", 0x200000, 0x200000, CRC(b710e2f2) SHA1(df4da585203eea7554d3ce718eb107e9cb6a0254) )
	ROM_LOAD( "056.v3", 0x400000, 0x100000, CRC(d168c301) SHA1(969273d1d11943e81560959359a2c4e69522af0e) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "056.c1", 0x000000, 0x200000, CRC(17b9cbd2) SHA1(1eee81e02763d384bd1c10a6012473ca931e4093) )
	ROM_LOAD16_BYTE( "056.c2", 0x000001, 0x200000, CRC(5fd76b67) SHA1(11925a41a53b53c6df4a5ebd28f98300950f743b) )
	ROM_LOAD16_BYTE( "056.c3", 0x400000, 0x200000, CRC(d2c88768) SHA1(22e2d84aa0c095944190e249ce87ef50d3f7b8ce) )
	ROM_LOAD16_BYTE( "056.c4", 0x400001, 0x200000, CRC(db39b883) SHA1(59de86c513dc4e230ae25d9e3b7e84621b657b54) )
	ROM_LOAD16_BYTE( "056.c5", 0x800000, 0x200000, CRC(c3074137) SHA1(9a75e3d63cb98d54f900dcfb3a03e21f3148d32f) )
	ROM_LOAD16_BYTE( "056.c6", 0x800001, 0x200000, CRC(31de68d3) SHA1(13ba7046cdd6863125f8284e60f102d4720af5a4) )
	ROM_LOAD16_BYTE( "056.c7", 0xc00000, 0x200000, CRC(3f36df57) SHA1(79ee97e9ae811a51141b535633f90e1491209d54) )
	ROM_LOAD16_BYTE( "056.c8", 0xc00001, 0x200000, CRC(e546d7a8) SHA1(74a2fca994a5a93a5784a46c0f68193122456a09) )
ROM_END

/****************************************
 ID-0057
 . ALM-006
 NEO-MVS PROG 4096 B / NEO-MVS CHA 42G-3
 . ALH-006
 NEO-AEG PROG4096 B / NEO-AEG CHA42G-3
****************************************/

ROM_START( wh2 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "057.p1", 0x100000, 0x100000, CRC(65a891d9) SHA1(ff8d5ccb0dd22c523902bb3db3c645583a335056) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "057.s1", CRC(fcaeb3a4) SHA1(1f3f85e38b8552333261c04ae5af0d6e3b310622) )

	NEO_BIOS_AUDIO_128K( "057.m1", CRC(8fa3bc77) SHA1(982f92978671e4ee66630948e6bb7565b37b5dc0) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "057.v1", 0x000000, 0x200000, CRC(8877e301) SHA1(1bab988d74ea8fd12db201c257ec844622cf5f4e) )
	ROM_LOAD( "057.v2", 0x200000, 0x200000, CRC(c1317ff4) SHA1(4c28b2b5998abaeaa5143f2f3a9ba52c6041f4f3) )

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "057.c1", 0x000000, 0x200000, CRC(21c6bb91) SHA1(a2c17d0c91dd59528d8fa7fe110af8b20b25ff99) )
	ROM_LOAD16_BYTE( "057.c2", 0x000001, 0x200000, CRC(a3999925) SHA1(0ee861a77850d378d03c1bf00b9692abd860c759) )
	ROM_LOAD16_BYTE( "057.c3", 0x400000, 0x200000, CRC(b725a219) SHA1(4857687d156a9150a69b97d2729245a51c144a0c) )
	ROM_LOAD16_BYTE( "057.c4", 0x400001, 0x200000, CRC(8d96425e) SHA1(0f79c868a6a33ad25e38d842f30ec4440d809033) )
	ROM_LOAD16_BYTE( "057.c5", 0x800000, 0x200000, CRC(b20354af) SHA1(da7609fd467f2f4d71d92970f438a04d11ab1cc1) )
	ROM_LOAD16_BYTE( "057.c6", 0x800001, 0x200000, CRC(b13d1de3) SHA1(7d749c23a33d90fe50279e884540d71cf1aaaa6b) )
ROM_END

/****************************************
 ID-0058
 . NGM-058
 NEO-MVS PROGGSC / NEO-MVS CHA42G-3B
 NEO-MVS PROGGSC / NEO-MVS CHA 42G-3
 . NGH-058
 NEO-AEG PROGGS / NEO-AEG CHA42G-4
****************************************/

ROM_START( fatfursp ) /* MVS AND AES VERSION */
	ROM_REGION( 0x180000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "058.p1",  0x000000, 0x100000, CRC(2f585ba2) SHA1(429b4bf43fb9b1082c15d645ca328f9d175b976b) )
	ROM_LOAD16_WORD_SWAP( "058.p2", 0x100000, 0x080000, CRC(d7c71a6b) SHA1(b3428063031a2e5857da40a5d2ffa87fb550c1bb) )

	NEO_SFIX_128K( "058.s1", CRC(2df03197) SHA1(24083cfc97e720ac9e131c9fe37df57e27c49294) )

	NEO_BIOS_AUDIO_128K( "058.m1", CRC(ccc5186e) SHA1(cf9091c523c182aebfb928c91640b2d72fd70123) )

	ROM_REGION( 0x500000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "058.v1", 0x000000, 0x200000, CRC(55d7ce84) SHA1(05ac6a395d9bf9166925acca176a8d6129f533c8) )
	ROM_LOAD( "058.v2", 0x200000, 0x200000, CRC(ee080b10) SHA1(29814fc21bbe30d37745c8918fab00c83a309be4) )
	ROM_LOAD( "058.v3", 0x400000, 0x100000, CRC(f9eb3d4a) SHA1(d1747f9460b965f6daf4f881ed4ecd04c5253434) )

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "058.c1", 0x000000, 0x200000, CRC(044ab13c) SHA1(569d283638a132bc163faac2a9055497017ee0d2) )
	ROM_LOAD16_BYTE( "058.c2", 0x000001, 0x200000, CRC(11e6bf96) SHA1(c093a4f93f13e07b276e28b30c2a14dda9135d8f) )
	ROM_LOAD16_BYTE( "058.c3", 0x400000, 0x200000, CRC(6f7938d5) SHA1(be057b0a3faeb76d5fff161d3e6fea8a26e11d2c) )
	ROM_LOAD16_BYTE( "058.c4", 0x400001, 0x200000, CRC(4ad066ff) SHA1(4e304646d954d5f7bbabc5d068e85de31d38830f) )
	ROM_LOAD16_BYTE( "058.c5", 0x800000, 0x200000, CRC(49c5e0bf) SHA1(f3784178f90751990ea47a082a6aa869ee3566c9) )
	ROM_LOAD16_BYTE( "058.c6", 0x800001, 0x200000, CRC(8ff1f43d) SHA1(6180ceb5412a3e2e34e9513a3283b9f63087f747) )
ROM_END

ROM_START( fatfurspa ) /* MVS AND AES VERSION */
	ROM_REGION( 0x180000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "058.p1",  0x000000, 0x100000, CRC(2f585ba2) SHA1(429b4bf43fb9b1082c15d645ca328f9d175b976b) )
	ROM_LOAD16_WORD_SWAP( "058.p2", 0x100000, 0x080000, CRC(d7c71a6b) SHA1(b3428063031a2e5857da40a5d2ffa87fb550c1bb) )
	/* the rom below acts as a patch to the program rom in the cart, replacing the first 512kb */
	ROM_LOAD16_WORD_SWAP( "058a.p1", 0x000000, 0x080000, CRC(9f0c1e1a) SHA1(02861b0f230541becccc3df6a2c85dbe8733e7ce) )

	NEO_SFIX_128K( "058.s1", CRC(2df03197) SHA1(24083cfc97e720ac9e131c9fe37df57e27c49294) )

	NEO_BIOS_AUDIO_128K( "058.m1", CRC(ccc5186e) SHA1(cf9091c523c182aebfb928c91640b2d72fd70123) )

	ROM_REGION( 0x500000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "058.v1", 0x000000, 0x200000, CRC(55d7ce84) SHA1(05ac6a395d9bf9166925acca176a8d6129f533c8) )
	ROM_LOAD( "058.v2", 0x200000, 0x200000, CRC(ee080b10) SHA1(29814fc21bbe30d37745c8918fab00c83a309be4) )
	ROM_LOAD( "058.v3", 0x400000, 0x100000, CRC(f9eb3d4a) SHA1(d1747f9460b965f6daf4f881ed4ecd04c5253434) )

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "058.c1", 0x000000, 0x200000, CRC(044ab13c) SHA1(569d283638a132bc163faac2a9055497017ee0d2) )
	ROM_LOAD16_BYTE( "058.c2", 0x000001, 0x200000, CRC(11e6bf96) SHA1(c093a4f93f13e07b276e28b30c2a14dda9135d8f) )
	ROM_LOAD16_BYTE( "058.c3", 0x400000, 0x200000, CRC(6f7938d5) SHA1(be057b0a3faeb76d5fff161d3e6fea8a26e11d2c) )
	ROM_LOAD16_BYTE( "058.c4", 0x400001, 0x200000, CRC(4ad066ff) SHA1(4e304646d954d5f7bbabc5d068e85de31d38830f) )
	ROM_LOAD16_BYTE( "058.c5", 0x800000, 0x200000, CRC(49c5e0bf) SHA1(f3784178f90751990ea47a082a6aa869ee3566c9) )
	ROM_LOAD16_BYTE( "058.c6", 0x800001, 0x200000, CRC(8ff1f43d) SHA1(6180ceb5412a3e2e34e9513a3283b9f63087f747) )
ROM_END

/****************************************
 ID-0059
 . NGM-059
 NEO-MVS PROGTOP / NEO-MVS CHA256
 NEO-MVS PROG 4096 B / NEO-MVS CHA 42G-3
 . NGH-059
****************************************/

ROM_START( savagere )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "059.p1", 0x100000, 0x100000, CRC(01d4e9c0) SHA1(3179d2be59bf2de6918d506117cff50acf7e09f3) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "059.s1", CRC(e08978ca) SHA1(55152cb9bd0403ae8656b93a6b1522dba5db6d1a) )

	NEO_BIOS_AUDIO_128K( "059.m1", CRC(29992eba) SHA1(187be624abe8670503edb235ff21ae8fdc3866e0) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "059.v1", 0x000000, 0x200000, CRC(530c50fd) SHA1(29401cee7f7d2c199c7cb58092e86b28205e81ad) )
	ROM_LOAD( "059.v2", 0x200000, 0x200000, CRC(eb6f1cdb) SHA1(7a311388315ea543babf872f62219fdc4d39d013) )
	ROM_LOAD( "059.v3", 0x400000, 0x200000, CRC(7038c2f9) SHA1(c1d6f86b24feba03fe009b58199d2eeabe572f4e) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "059.c1", 0x000000, 0x200000, CRC(763ba611) SHA1(d3262e0332c894ee149c5963f882cc5e5562ee57) )
	ROM_LOAD16_BYTE( "059.c2", 0x000001, 0x200000, CRC(e05e8ca6) SHA1(986a9b16ff92bc101ab567d2d01348e093abea9a) )
	ROM_LOAD16_BYTE( "059.c3", 0x400000, 0x200000, CRC(3e4eba4b) SHA1(770adec719e63a30ebe9522cc7576caaca44f3b2) )
	ROM_LOAD16_BYTE( "059.c4", 0x400001, 0x200000, CRC(3c2a3808) SHA1(698adcec0715c9e78b6286be38debf0ce28fd644) )
	ROM_LOAD16_BYTE( "059.c5", 0x800000, 0x200000, CRC(59013f9e) SHA1(5bf48fcc450da72a8c4685f6e3887e67eae49988) )
	ROM_LOAD16_BYTE( "059.c6", 0x800001, 0x200000, CRC(1c8d5def) SHA1(475d89a5c4922a9f6bd756d23c2624d57b6e9d62) )
	ROM_LOAD16_BYTE( "059.c7", 0xc00000, 0x200000, CRC(c88f7035) SHA1(c29a428b741f4fe7b71a3bc23c87925b6bc1ca8f) )
	ROM_LOAD16_BYTE( "059.c8", 0xc00001, 0x200000, CRC(484ce3ba) SHA1(4f21ed20ce6e2b67e2b079404599310c94f591ff) )
ROM_END

/****************************************
 ID-0060
 . ??M-060
 NEO-MVS PROGGSC / NEO-MVS CHA256B
****************************************/

ROM_START( fightfev ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "060.p1", 0x0000000, 0x100000, CRC(2a104b50) SHA1(3eb663d3df7074e1cdf4c0e450a35c9cf55d8979) )

	NEO_SFIX_128K( "060.s1", CRC(d62a72e9) SHA1(a23e4c4fd4ec11a7467ce41227c418b4dd1ef649) )

	NEO_BIOS_AUDIO_128K( "060.m1", CRC(0b7c4e65) SHA1(999a1e784de18db3f1332b30bc425836ea6970be) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "060.v1", 0x000000, 0x200000, CRC(f417c215) SHA1(0f53b8dd056f43b5d880628e8b74c2b27881ffac) )
	ROM_LOAD( "060.v2", 0x200000, 0x100000, CRC(efcff7cf) SHA1(e8372303724284a750b706dc6bf7641e4c52bb95) )

	ROM_REGION( 0x0800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "060.c1", 0x0000000, 0x200000, CRC(8908fff9) SHA1(f8c16ab0248b60f3a62e0d4d65c456e2f8e4da49) )
	ROM_LOAD16_BYTE( "060.c2", 0x0000001, 0x200000, CRC(c6649492) SHA1(5d39b077387ed6897ac075ede4a2aa94bb64545e) )
	ROM_LOAD16_BYTE( "060.c3", 0x0400000, 0x200000, CRC(0956b437) SHA1(c70be8b5cebf321afe4c3f5e9a12413c3077694a) )
	ROM_LOAD16_BYTE( "060.c4", 0x0400001, 0x200000, CRC(026f3b62) SHA1(d608483b70d60e7aa0e41f25a8b3fed508129eb7) )
ROM_END

ROM_START( fightfeva ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "060.p1", 0x0000000, 0x100000, CRC(2a104b50) SHA1(3eb663d3df7074e1cdf4c0e450a35c9cf55d8979) )
	/* the rom below acts as a patch to the program rom in the cart, replacing the first 512kb */
	ROM_LOAD16_WORD_SWAP( "060a.p1", 0x000000, 0x080000, CRC(3032041b) SHA1(4b8ed2e6f74579ea35a53e06ccac42d6905b0f51) )

	NEO_SFIX_128K( "060.s1", CRC(d62a72e9) SHA1(a23e4c4fd4ec11a7467ce41227c418b4dd1ef649) )

	NEO_BIOS_AUDIO_128K( "060.m1", CRC(0b7c4e65) SHA1(999a1e784de18db3f1332b30bc425836ea6970be) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "060.v1", 0x000000, 0x200000, CRC(f417c215) SHA1(0f53b8dd056f43b5d880628e8b74c2b27881ffac) )
	ROM_LOAD( "060.v2", 0x200000, 0x100000, CRC(efcff7cf) SHA1(e8372303724284a750b706dc6bf7641e4c52bb95) )

	ROM_REGION( 0x0800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "060.c1", 0x0000000, 0x200000, CRC(8908fff9) SHA1(f8c16ab0248b60f3a62e0d4d65c456e2f8e4da49) )
	ROM_LOAD16_BYTE( "060.c2", 0x0000001, 0x200000, CRC(c6649492) SHA1(5d39b077387ed6897ac075ede4a2aa94bb64545e) )
	ROM_LOAD16_BYTE( "060.c3", 0x0400000, 0x200000, CRC(0956b437) SHA1(c70be8b5cebf321afe4c3f5e9a12413c3077694a) )
	ROM_LOAD16_BYTE( "060.c4", 0x0400001, 0x200000, CRC(026f3b62) SHA1(d608483b70d60e7aa0e41f25a8b3fed508129eb7) )
ROM_END

/****************************************
 ID-0061
 . NGM-061
 NEO-MVS PROGGSC / NEO-MVS CHA256
 NEO-MVS PROGTOP / NEO-MVS CHA256
 NEO-MVS PROG 4096 B / NEO-MVS CHA256
 . NGH-061
 NEO-AEG PROGRKB / NEO-AEG CHA256[B]
****************************************/

ROM_START( ssideki2 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "061.p1", 0x000000, 0x100000, CRC(5969e0dc) SHA1(78abea880c125ec5a85bef6404478512a34b5513) )

	NEO_SFIX_128K( "061.s1", CRC(226d1b68) SHA1(de010f6fda3ddadb181fe37daa6105f22e78b970) )

	NEO_BIOS_AUDIO_128K( "061.m1", CRC(156f6951) SHA1(49686f615f109a02b4f23931f1c84fee13872ffd) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "061.v1", 0x000000, 0x200000, CRC(f081c8d3) SHA1(fc9da0ddc1ddd1f9ae1443a726815c25e9dc38ae) )
	ROM_LOAD( "061.v2", 0x200000, 0x200000, CRC(7cd63302) SHA1(c39984c0ae0a8e76f1fc036344bbb83635c18937) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "061.c1", 0x000000, 0x200000, CRC(a626474f) SHA1(d695f0dcb9480088b3a7c1488bd541b4c159528a) )
	ROM_LOAD16_BYTE( "061.c2", 0x000001, 0x200000, CRC(c3be42ae) SHA1(7fa65538bd0a0a162e4d3e9f49913da59d915e02) )
	ROM_LOAD16_BYTE( "061.c3", 0x400000, 0x200000, CRC(2a7b98b9) SHA1(75e1019dca8a8583afcc53651ac856cba3a96315) )
	ROM_LOAD16_BYTE( "061.c4", 0x400001, 0x200000, CRC(c0be9a1f) SHA1(228f41eaefdf3e147761f8ef849e3b5f321877d4) )
ROM_END

/****************************************
 ID-0062
 . DEM-001
 NEO-MVS PROGGSC / NEO-MVS CHA256
 . DEH-001
****************************************/

ROM_START( spinmast )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "062.p1",  0x000000, 0x100000, CRC(37aba1aa) SHA1(1a2ab9593371cc2f665121d554eec3f6bb4d09ff) )
	ROM_LOAD16_WORD_SWAP( "062.p2", 0x100000, 0x100000, CRC(f025ab77) SHA1(4944be04648296d0b93cfe4c5ca7b9cede072cff) )

	NEO_SFIX_128K( "062.s1", CRC(289e2bbe) SHA1(f52c7f2bffc89df3130b3cabd200408509a28cdc) )

	NEO_BIOS_AUDIO_128K( "062.m1", CRC(76108b2f) SHA1(08c89a8b746dbb10ff885b41cde344173c2e3699) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "062.v1", 0x000000, 0x100000, CRC(cc281aef) SHA1(68be154b3e25f837afb4a477600dbe0ee69bec44) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "062.c1", 0x000000, 0x100000, CRC(a9375aa2) SHA1(69218d8f1361e9ea709da11e3f15fe46b1db7181) )
	ROM_LOAD16_BYTE( "062.c2", 0x000001, 0x100000, CRC(0e73b758) SHA1(a247f736fbca0b609818dca4844ebb8442753bc1) )
	ROM_LOAD16_BYTE( "062.c3", 0x200000, 0x100000, CRC(df51e465) SHA1(171953c7a870f3ab96e0f875117ee7343931fd38) )
	ROM_LOAD16_BYTE( "062.c4", 0x200001, 0x100000, CRC(38517e90) SHA1(f7c64b94ac20f5146f9bb48b53cb2b30fe5b8f8c) )
	ROM_LOAD16_BYTE( "062.c5", 0x400000, 0x100000, CRC(7babd692) SHA1(0d4cd5006baa8d951cd2b6194ace566fa2845b8a) )
	ROM_LOAD16_BYTE( "062.c6", 0x400001, 0x100000, CRC(cde5ade5) SHA1(5899ef5dfcdbb8cf8c6aba748dbb52f3c5fed5fe) )
	ROM_LOAD16_BYTE( "062.c7", 0x600000, 0x100000, CRC(bb2fd7c0) SHA1(cce11c4cf39ac60143235ff89261806df339dae5) )
	ROM_LOAD16_BYTE( "062.c8", 0x600001, 0x100000, CRC(8d7be933) SHA1(e7097cfa26a959f90721e2e8368ceb47ea9db661) )
ROM_END

/****************************************
 ID-0063
 . NGM-063
 NEO-MVS PROGTOP / NEO-MVS CHA256
 . NGH-063
 NEO-AEG PROGTOP2 / NEO-AEG CHA256 B
****************************************/

ROM_START( samsho2 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "063.p1", 0x100000, 0x100000, CRC(22368892) SHA1(0997f8284aa0f57a333be8a0fdea777d0d01afd6) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "063.s1", CRC(64a5cd66) SHA1(12cdfb27bf9ccd5a8df6ddd4628ef7cf2c6d4964) )

	NEO_BIOS_AUDIO_128K( "063.m1", CRC(56675098) SHA1(90429fc40d056d480d0e2bbefbc691d9fa260fc4) )

	ROM_REGION( 0x700000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "063.v1", 0x000000, 0x200000, CRC(37703f91) SHA1(a373ebef4c33ba1d8340e826981a58769aada238) )
	ROM_LOAD( "063.v2", 0x200000, 0x200000, CRC(0142bde8) SHA1(0be6c53acac44802bf70b6925452f70289a139d9) )
	ROM_LOAD( "063.v3", 0x400000, 0x200000, CRC(d07fa5ca) SHA1(1da7f081f8b8fc86a91feacf900f573218d82676) )
	ROM_LOAD( "063.v4", 0x600000, 0x100000, CRC(24aab4bb) SHA1(10ee4c5b3579865b93dcc1e4079963276aa700a6) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "063.c1", 0x000000, 0x200000, CRC(86cd307c) SHA1(0d04336f7c436d74638d8c1cd8651faf436a6bec) )
	ROM_LOAD16_BYTE( "063.c2", 0x000001, 0x200000, CRC(cdfcc4ca) SHA1(179dc81432424d68cefedd20cc1c4b2a95deb891) )
	ROM_LOAD16_BYTE( "063.c3", 0x400000, 0x200000, CRC(7a63ccc7) SHA1(49d97c543bc2860d493a353ab0d059088c6fbd21) )
	ROM_LOAD16_BYTE( "063.c4", 0x400001, 0x200000, CRC(751025ce) SHA1(e1bbaa7cd67fd04e4aab7f7ea77f63ae1cbc90d0) )
	ROM_LOAD16_BYTE( "063.c5", 0x800000, 0x200000, CRC(20d3a475) SHA1(28da44a136bd14c73c62c147c3f6e6bcfa1066de) )
	ROM_LOAD16_BYTE( "063.c6", 0x800001, 0x200000, CRC(ae4c0a88) SHA1(cc8a7d11daa3821f83a6fd0942534706f939e576) )
	ROM_LOAD16_BYTE( "063.c7", 0xc00000, 0x200000, CRC(2df3cbcf) SHA1(e54f9022359963711451c2025825b862d36c6975) )
	ROM_LOAD16_BYTE( "063.c8", 0xc00001, 0x200000, CRC(1ffc6dfa) SHA1(acea18aca76c072e0bac2a364fc96d49cfc86e77) )
ROM_END

ROM_START( samsho2k ) /* KOREAN VERSION */
	// This has corrupt text if used with the Japan bios due to the replacement of the s1 rom to contain the new logo
	ROM_REGION( 0x200000, "maincpu", ROMREGION_BE|ROMREGION_16BIT )
	ROM_LOAD16_WORD_SWAP( "063-p1-kan.p1", 0x100000, 0x100000, CRC(147cc6d7) SHA1(8e22305f41a0688786ff55437c25948e6c8fda58) )
	ROM_CONTINUE( 0x000000, 0x100000 )
	// the roms below apply as patch over the main program (I haven't checked what they change, the game boots as the Korean version even with just the above program)
	ROM_LOAD16_WORD_SWAP( "063-ep1-kan.ep1", 0x000000, 0x080000, CRC(fa32e2d8) SHA1(94f56759ec04ab3a1e557bc2dc51b92176b3c147) )
	ROM_LOAD16_WORD_SWAP( "063-ep2-kan.ep2", 0x080000, 0x080000, CRC(70b1a4d9) SHA1(387737e87a68d0ea4fd13693f1f30d3227a17c82) ) // this is exactly the same data anyway!

	NEO_SFIX_128K( "063-s1-kan.s1", CRC(ff08f80b) SHA1(240c6a1c52edebb49cc99ea08484c6a2d61ebf84) )

	NEO_BIOS_AUDIO_128K( "063-m1.m1", CRC(56675098) SHA1(90429fc40d056d480d0e2bbefbc691d9fa260fc4) ) /* TC531001 */

	ROM_REGION( 0x700000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "063-v1.v1", 0x000000, 0x200000, CRC(37703f91) SHA1(a373ebef4c33ba1d8340e826981a58769aada238) ) /* TC5316200 */
	ROM_LOAD( "063-v2.v2", 0x200000, 0x200000, CRC(0142bde8) SHA1(0be6c53acac44802bf70b6925452f70289a139d9) ) /* TC5316200 */
	ROM_LOAD( "063-v3.v3", 0x400000, 0x200000, CRC(d07fa5ca) SHA1(1da7f081f8b8fc86a91feacf900f573218d82676) ) /* TC5316200 */
	ROM_LOAD( "063-v4.v4", 0x600000, 0x100000, CRC(24aab4bb) SHA1(10ee4c5b3579865b93dcc1e4079963276aa700a6) ) /* TC538200 */

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "063-c1.c1", 0x000000, 0x200000, CRC(86cd307c) SHA1(0d04336f7c436d74638d8c1cd8651faf436a6bec) ) /* Plane 0,1 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "063-c2.c2", 0x000001, 0x200000, CRC(cdfcc4ca) SHA1(179dc81432424d68cefedd20cc1c4b2a95deb891) ) /* Plane 2,3 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "063-c3.c3", 0x400000, 0x200000, CRC(7a63ccc7) SHA1(49d97c543bc2860d493a353ab0d059088c6fbd21) ) /* Plane 0,1 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "063-c4.c4", 0x400001, 0x200000, CRC(751025ce) SHA1(e1bbaa7cd67fd04e4aab7f7ea77f63ae1cbc90d0) ) /* Plane 2,3 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "063-c5.c5", 0x800000, 0x200000, CRC(20d3a475) SHA1(28da44a136bd14c73c62c147c3f6e6bcfa1066de) ) /* Plane 0,1 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "063-c6.c6", 0x800001, 0x200000, CRC(ae4c0a88) SHA1(cc8a7d11daa3821f83a6fd0942534706f939e576) ) /* Plane 2,3 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "063-c7.c7", 0xc00000, 0x200000, CRC(2df3cbcf) SHA1(e54f9022359963711451c2025825b862d36c6975) ) /* Plane 0,1 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "063-c8.c8", 0xc00001, 0x200000, CRC(1ffc6dfa) SHA1(acea18aca76c072e0bac2a364fc96d49cfc86e77) ) /* Plane 2,3 */ /* TC5316200 */
ROM_END

ROM_START( samsho2ka ) /* KOREAN VERSION */
	// This has corrupt text if used with the Japan bios due to the replacement of the s1 rom to contain the new logo
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "063k.p1", 0x100000, 0x100000, CRC(147cc6d7) SHA1(8e22305f41a0688786ff55437c25948e6c8fda58) )
	ROM_CONTINUE( 0x000000, 0x100000 )
	// the roms below apply as patch over the main program (I haven't checked what they change, the game boots as the Korean version even with just the above program)
	ROM_LOAD16_WORD_SWAP( "063k.p2", 0x000000, 0x080000, CRC(fa32e2d8) SHA1(94f56759ec04ab3a1e557bc2dc51b92176b3c147) )
	ROM_LOAD16_WORD_SWAP( "063k.p3", 0x080000, 0x080000, CRC(70b1a4d9) SHA1(387737e87a68d0ea4fd13693f1f30d3227a17c82) ) // this is exactly the same data anyway!

	NEO_SFIX_128K( "063k.s1", CRC(ff08f80b) SHA1(240c6a1c52edebb49cc99ea08484c6a2d61ebf84) )

	NEO_BIOS_AUDIO_128K( "063.m1", CRC(56675098) SHA1(90429fc40d056d480d0e2bbefbc691d9fa260fc4) )

	ROM_REGION( 0x700000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "063.v1", 0x000000, 0x200000, CRC(37703f91) SHA1(a373ebef4c33ba1d8340e826981a58769aada238) )
	ROM_LOAD( "063.v2", 0x200000, 0x200000, CRC(0142bde8) SHA1(0be6c53acac44802bf70b6925452f70289a139d9) )
	ROM_LOAD( "063.v3", 0x400000, 0x200000, CRC(d07fa5ca) SHA1(1da7f081f8b8fc86a91feacf900f573218d82676) )
	ROM_LOAD( "063.v4", 0x600000, 0x100000, CRC(24aab4bb) SHA1(10ee4c5b3579865b93dcc1e4079963276aa700a6) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "063.c1", 0x000000, 0x200000, CRC(86cd307c) SHA1(0d04336f7c436d74638d8c1cd8651faf436a6bec) )
	ROM_LOAD16_BYTE( "063.c2", 0x000001, 0x200000, CRC(cdfcc4ca) SHA1(179dc81432424d68cefedd20cc1c4b2a95deb891) )
	ROM_LOAD16_BYTE( "063.c3", 0x400000, 0x200000, CRC(7a63ccc7) SHA1(49d97c543bc2860d493a353ab0d059088c6fbd21) )
	ROM_LOAD16_BYTE( "063.c4", 0x400001, 0x200000, CRC(751025ce) SHA1(e1bbaa7cd67fd04e4aab7f7ea77f63ae1cbc90d0) )
	ROM_LOAD16_BYTE( "063.c5", 0x800000, 0x200000, CRC(20d3a475) SHA1(28da44a136bd14c73c62c147c3f6e6bcfa1066de) )
	ROM_LOAD16_BYTE( "063.c6", 0x800001, 0x200000, CRC(ae4c0a88) SHA1(cc8a7d11daa3821f83a6fd0942534706f939e576) )
	ROM_LOAD16_BYTE( "063.c7", 0xc00000, 0x200000, CRC(2df3cbcf) SHA1(e54f9022359963711451c2025825b862d36c6975) )
	ROM_LOAD16_BYTE( "063.c8", 0xc00001, 0x200000, CRC(1ffc6dfa) SHA1(acea18aca76c072e0bac2a364fc96d49cfc86e77) )
ROM_END

/****************************************
 ID-0064
 . ADM-007
 NEO-MVS PROGGSC / NEO-MVS CHA256
 . ADH-007
 NEO-AEG PROGRK / NEO-AEG CHA256
 NEO-AEG PROGRKB / NEO-AEG CHA256[B]
****************************************/

ROM_START( wh2j ) /* MVS AND AES VERSION */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "064.p1", 0x100000, 0x100000, CRC(385a2e86) SHA1(cfde4a1aeae038a3d6ca9946065624f097682d3d) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "064.s1", CRC(2a03998a) SHA1(5e33f469982f12d4622a06d323a345f192bf88e6) )

	NEO_BIOS_AUDIO_128K( "064.m1", CRC(d2eec9d3) SHA1(09478787045f1448d19d064dd3d540d1741fd619) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "064.v1", 0x000000, 0x200000, CRC(aa277109) SHA1(35c22b15bb0a4d0ab118cb22a2d450d03995a17c) )
	ROM_LOAD( "064.v2", 0x200000, 0x200000, CRC(b6527edd) SHA1(2bcf5bfa6e117cf4a3728a5e5f5771313c93f22a) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "064.c1", 0x000000, 0x200000, CRC(2ec87cea) SHA1(e713ec7839a7665edee6ee3f82a6e530b3b4bd7c) )
	ROM_LOAD16_BYTE( "064.c2", 0x000001, 0x200000, CRC(526b81ab) SHA1(b5f0a2f04489539ed6b9d0810b12787356c64b23) )
	ROM_LOAD16_BYTE( "064.c3", 0x400000, 0x200000, CRC(436d1b31) SHA1(059776d77b91377ed0bcfc278802d659c917fc0f) )
	ROM_LOAD16_BYTE( "064.c4", 0x400001, 0x200000, CRC(f9c8dd26) SHA1(25a9eea1d49b21b4a988beb32c25bf2f7796f227) )
	ROM_LOAD16_BYTE( "064.c5", 0x800000, 0x200000, CRC(8e34a9f4) SHA1(67b839b426ef3fad0a85d951fdd44c0a45c55226) )
	ROM_LOAD16_BYTE( "064.c6", 0x800001, 0x200000, CRC(a43e4766) SHA1(54f282f2b1ff2934cca7acbb4386a2b99a29df3a) )
	ROM_LOAD16_BYTE( "064.c7", 0xc00000, 0x200000, CRC(59d97215) SHA1(85a960dc7f364df13ee0c2f99a4c53aefb081486) )
	ROM_LOAD16_BYTE( "064.c8", 0xc00001, 0x200000, CRC(fc092367) SHA1(69ff4ae909dd857de3ca8645d63f8b4bde117448) )
ROM_END

/****************************************
 ID-0065
 . DEM-002
 NEO-MVS PROG42G-1 / NEO-MVS CHA42G-1
 . DEH-002
 NEO-AEG PROG42G-1 / NEO-AEG CHA42G-1
****************************************/

ROM_START( wjammers )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "065.p1", 0x000000, 0x100000, CRC(6692c140) SHA1(5da574e906974fac92bb2f49bdeea257c014a897) )

	NEO_SFIX_128K( "065.s1", CRC(074b5723) SHA1(86d3b3bb5414f43e4d3b7a2af0db23cc71ce8412) )

	NEO_BIOS_AUDIO_128K( "065.m1", CRC(52c23cfc) SHA1(809a7e072ad9acbffc25e9bd27cdb97638d09d07) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "065.v1", 0x000000, 0x100000, CRC(ce8b3698) SHA1(7d75e2a5cf8c90be422f8b425447e81597fe145a) )
	ROM_LOAD( "065.v2", 0x100000, 0x100000, CRC(659f9b96) SHA1(62f40365212153bc3b92a1187fa44f6cdc7f7b83) )
	ROM_LOAD( "065.v3", 0x200000, 0x100000, CRC(39f73061) SHA1(ec57cd58e7f8569cff925d11e2320d588ce4fe49) )
	ROM_LOAD( "065.v4", 0x300000, 0x100000, CRC(5dee7963) SHA1(f8e6de73d65dd80b29c711f00835a574a770cb4e) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "065.c1", 0x000000, 0x100000, CRC(c7650204) SHA1(42918d700d59864f8ab15caf968a062a563c9b09) )
	ROM_LOAD16_BYTE( "065.c2", 0x000001, 0x100000, CRC(d9f3e71d) SHA1(fad1f64061eac1bf85bf6d75d2eae974a8c94069) )
	ROM_LOAD16_BYTE( "065.c3", 0x200000, 0x100000, CRC(40986386) SHA1(65795a50197049681265946713d416c9cdb68f08) )
	ROM_LOAD16_BYTE( "065.c4", 0x200001, 0x100000, CRC(715e15ff) SHA1(ac8b8b01f5c7384b883afbe0cf977430378e3fef) )
ROM_END

/****************************************
 ID-0066
 . DEM-003
 NEO-MVS PROGGSC / NEO-MVS CHA256
 . DEH-003
****************************************/

ROM_START( karnovr )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "066.p1", 0x000000, 0x100000, CRC(8c86fd22) SHA1(8cf97c6fb9c5717167ccc54bf5856248ccaf32c6) )

	NEO_SFIX_128K( "066.s1", CRC(bae5d5e5) SHA1(aa69d9b235b781ec51f72a528fada9cb12e72cbc) )

	NEO_BIOS_AUDIO_128K( "066.m1", CRC(030beae4) SHA1(ceb6ee6c09514504efacdbca7b280901e4c97084) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "066.v1", 0x000000, 0x200000, CRC(0b7ea37a) SHA1(34e7d4f6db053674a7e8c8b2e3e398777d5b02e6) )

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "066.c1", 0x000000, 0x200000, CRC(09dfe061) SHA1(ca4c0f0ce80967b4be2f18b72435c468bbfbac4c) )
	ROM_LOAD16_BYTE( "066.c2", 0x000001, 0x200000, CRC(e0f6682a) SHA1(addb4fbc30da2b8ffc86819d92a874eb232f67dd) )
	ROM_LOAD16_BYTE( "066.c3", 0x400000, 0x200000, CRC(a673b4f7) SHA1(d138f5b38fd65c61549ce36f5c4983f7c8a3e7f6) )
	ROM_LOAD16_BYTE( "066.c4", 0x400001, 0x200000, CRC(cb3dc5f4) SHA1(865d9ccfc3df517c341d6aac16120f6b6aa759fe) )
	ROM_LOAD16_BYTE( "066.c5", 0x800000, 0x200000, CRC(9a28785d) SHA1(19723e1f7ff429e8a038d89488b279f830dfaf6e) )
	ROM_LOAD16_BYTE( "066.c6", 0x800001, 0x200000, CRC(c15c01ed) SHA1(7cf5583e6610bcdc3b332896cefc71df84fb3f19) )
ROM_END

/****************************************
 ID-0067
 . ??M-067
 NEO-MVS PROG16 / NEO-MVS CHA256B
 NEO-MVS PROG16 / NEO-MVS CHA256
****************************************/

ROM_START( gururin ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "067.p1", 0x000000, 0x80000, CRC(4cea8a49) SHA1(cea4a35db8de898e30eb40dd339b3cbe77ac0856) )

	NEO_SFIX_128K( "067.s1", CRC(b119e1eb) SHA1(f63a68a71aea220d3d4475847652e2a1f68b2b6f) )

	NEO_BIOS_AUDIO_128K( "067.m1", CRC(9e3c6328) SHA1(17e8479c258f28a01d2283be9e692ff7685898cc) )

	ROM_REGION( 0x80000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "067.v1", 0x000000, 0x80000, CRC(cf23afd0) SHA1(10f87014ee10613f92b04f482f449721a6379db7) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "067.c1", 0x000000, 0x200000, CRC(35866126) SHA1(e4b24670ccc7901af5f66b11b15fae4e67f843ab) )
	ROM_LOAD16_BYTE( "067.c2", 0x000001, 0x200000, CRC(9db64084) SHA1(68a43c12f63f5e98d68ad0902a6551c5d30f8543) )
ROM_END

/****************************************
 ID-0068
 . NGM-068
 NEO-MVS PROGTOP / NEO-MVS CHA256
****************************************/

ROM_START( pspikes2 ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "068.p1", 0x000000, 0x100000, CRC(105a408f) SHA1(2ee51defa1c24c66c63a6498ee542ac26de3cfbb) )

	NEO_SFIX_128K( "068-sg1.s1", CRC(18082299) SHA1(efe93fabe6a76a5dc8cf12f255e571480afb40a0) )

	NEO_BIOS_AUDIO_128K( "068-mg1.m1", CRC(b1c7911e) SHA1(27b298e7d50981331e17aa642e2e363ffac4333a) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "068.v1", 0x000000, 0x100000, CRC(2ced86df) SHA1(d6b73d1f31efbd74fb745200d4dade5f80b71541) )
	ROM_LOAD( "068.v2", 0x100000, 0x100000, CRC(970851ab) SHA1(6c9b04e9cc6b92133f1154e5bdd9d38d8ef050a7) )
	ROM_LOAD( "068.v3", 0x200000, 0x100000, CRC(81ff05aa) SHA1(d74302f38c59055bfc83b39dff798a585314fecd) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD16_BYTE( "068.c1", 0x000000, 0x100000, CRC(7f250f76) SHA1(5109a41adcb7859e24dc43d88842d4cc18cd3305) )
	ROM_LOAD16_BYTE( "068.c2", 0x000001, 0x100000, CRC(20912873) SHA1(2df8766b531e47ffc30457e41c63b83557b4f468) )
	ROM_LOAD16_BYTE( "068.c3", 0x200000, 0x100000, CRC(4b641ba1) SHA1(7a9c42a30163eda455f7bde2302402b1a5de7178) )
	ROM_LOAD16_BYTE( "068.c4", 0x200001, 0x100000, CRC(35072596) SHA1(4150a21041f06514c97592bd8af686504b06e187) )
	ROM_LOAD16_BYTE( "068.c5", 0x400000, 0x100000, CRC(151dd624) SHA1(f2690a3fe9c64f70f283df785a5217d5b92a289f) )
	ROM_LOAD16_BYTE( "068.c6", 0x400001, 0x100000, CRC(a6722604) SHA1(b40c57fb4be93ac0b918829f88393ced3d4f8bde) )
ROM_END

/****************************************
 ID-0069
 . NGM-069
 NEO-MVS PROGBK1 / NEO-MVS CHA256
. NGH-069
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( fatfury3 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "069.p1",   0x000000, 0x100000, CRC(a8bcfbbc) SHA1(519c4861151797e5f4d4f33432b83dfabed8e7c4) )
	ROM_LOAD16_WORD_SWAP( "069.p2", 0x100000, 0x200000, CRC(dbe963ed) SHA1(8ece7f663cfe8e563576a397e41161d392cee67e) )

	NEO_SFIX_128K( "069.s1", CRC(0b33a800) SHA1(b7d2cc97da4f30ddebc7b801f5e1d17d2306b2db) )

	NEO_BIOS_AUDIO_128K( "069.m1", CRC(fce72926) SHA1(a40c74f793900b8542f0b8383ce4bf46fca112d4) )

	ROM_REGION( 0xa00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "069.v1", 0x000000, 0x400000, CRC(2bdbd4db) SHA1(5f4fecf69c2329d699cbd45829c19303b1e2a80e) )
	ROM_LOAD( "069.v2", 0x400000, 0x400000, CRC(a698a487) SHA1(11b8bc53bc26a51f4a408e900e3769958625c4ed) )
	ROM_LOAD( "069.v3", 0x800000, 0x200000, CRC(581c5304) SHA1(e9550ec547b4f605afed996b22d711f49b48fa92) )

	ROM_REGION( 0x1400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "069.c1", 0x0000000, 0x400000, CRC(e302f93c) SHA1(d8610b14900b2b8fe691b67ca9b1abb335dbff74) )
	ROM_LOAD16_BYTE( "069.c2", 0x0000001, 0x400000, CRC(1053a455) SHA1(69501bfac68739e63d798045b812badd251d57b8) )
	ROM_LOAD16_BYTE( "069.c3", 0x0800000, 0x400000, CRC(1c0fde2f) SHA1(cf6c2ef56c03a861de3b0b6dc0d7c9204d947f9d) )
	ROM_LOAD16_BYTE( "069.c4", 0x0800001, 0x400000, CRC(a25fc3d0) SHA1(83cb349e2f1032652060b233e741fb893be5af16) )
	ROM_LOAD16_BYTE( "069.c5", 0x1000000, 0x200000, CRC(b3ec6fa6) SHA1(7e4c8ee9dd8d9a25ff183d9d8b05f38769348bc7) )
	ROM_LOAD16_BYTE( "069.c6", 0x1000001, 0x200000, CRC(69210441) SHA1(6d496c549dba65caabeaffe5b762e86f9d648a26) )
ROM_END

/****************************************
 ID-0070
 . ??M-070
 NEO-MVS PROGBK1 / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7042)
****************************************/

ROM_START( zupapa ) /* Original Version - Encrypted GFX */ /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "070.p1", 0x000000, 0x100000, CRC(5a96203e) SHA1(49cddec9ca6cc51e5ecf8a34e447a23e1f8a15a1) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_128K( "070.m1", CRC(5a3b3191) SHA1(fa9a9930e18c64e598841fb344c4471d3d2c1964) )

	ROM_REGION( 0x0200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "070.v1", 0x000000, 0x200000, CRC(d3a7e1ff) SHA1(4a4a227e10f4af58168f6c26011ea1d414253f92) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "070.c1", 0x0000000, 0x800000, CRC(f8ad02d8) SHA1(9be54532332a8e963ec35ff1e518947bb11ebade) )
	ROM_LOAD16_BYTE( "070.c2", 0x0000001, 0x800000, CRC(70156dde) SHA1(06286bf043d50199b47df9a76ca91f39cb28cb90) )
ROM_END

/****************************************
 ID-0071
 Bang Bang Busters (prototype) 1994 Visco
 Prepared for release in 2000/2001, but apparently Zupapa was favored
 The 2000 version was released in 2010 for MVS and AES (Releaser claims that it is officially licensed by VISCO)

 Reported UNIVERSE BIOS CRC32:
  ROM     EC861CAF
  BANK 0  NOT USED
  BANK 1  NOT USED
  BANK 2  NOT USED
  BANK 3  NOT USED
 ****************************************/
ROM_START( b2b )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "071.p1", 0x000000, 0x080000, CRC(7687197d) SHA1(4bb9cb7819807f7a7e1f85f1c4faac4a2f8761e8) )

	NEO_SFIX_128K( "071.s1", CRC(44e5f154) SHA1(b3f80051789e60e5d8c5df0408f1aba51616e92d) )

	NEO_BIOS_AUDIO_128K( "071.m1", CRC(6da739ad) SHA1(cbf5f55c54b4ee00943e2a411eeee4e465ce9c34) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "071.v1", 0x000000, 0x100000, CRC(50feffb0) SHA1(00127dae0130889995bfa7560bc4b0662f74fba5) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "071.c1", 0x000000, 0x200000, CRC(23d84a7a) SHA1(9034658ad40e2c45558abc3db312aa2764102fc4) )
	ROM_LOAD16_BYTE( "071.c2", 0x000001, 0x200000, CRC(ce7b6248) SHA1(ad1cd5adae5c151e183ff88b68afe10f7009f48e) )
ROM_END


/****************************************
 ID-0072
 Last Odyssey Pinball Fantasia (prototype) 1995 Monolith
 A video of this was on youtube in 2010/2011.
 ****************************************/

/****************************************
 ID-0073
 . ??M-073
 NEO-MVS PROGTOP / NEO-MVS CHA256
****************************************/

ROM_START( panicbom ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "073.p1", 0x000000, 0x080000, CRC(adc356ad) SHA1(801e0a54b65d7a3500e6cef2d6bba40c6356dc1f) )

	NEO_SFIX_128K( "073.s1", CRC(b876de7e) SHA1(910347d7657470da914fb0a6b0ea02891e13c081) )

	NEO_BIOS_AUDIO_128K( "073.m1", CRC(3cdf5d88) SHA1(6d8365a946fbd0b7c7b896536322638d80f6a764) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "073.v1", 0x000000, 0x200000, CRC(7fc86d2f) SHA1(aa4234d22157060e0ba97a09c4e85c5276b74099) )
	ROM_LOAD( "073.v2", 0x200000, 0x100000, CRC(082adfc7) SHA1(19c168e9a6cadcbed79033c320bcf3a45f846daf) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "073.c1", 0x000000, 0x100000, CRC(8582e1b5) SHA1(e17d8f57b8ebee14b8e705374b34abe928937258) )
	ROM_LOAD16_BYTE( "073.c2", 0x000001, 0x100000, CRC(e15a093b) SHA1(548a418c81af79cd7ab6ad165b8d6daee30abb49) )
ROM_END

/****************************************
 ID-0074
 . ADM-008
 NEO-MVS PROGTOP / NEO-MVS CHA256B
 . ADH-008
 NEO-AEG PROGRK / NEO-AEG CHA256
****************************************/

ROM_START( aodk ) /* MVS AND AES VERSION */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "074.p1", 0x100000, 0x100000, CRC(62369553) SHA1(ca4d561ee08d16fe6804249d1ba49188eb3bd606) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "074.s1", CRC(96148d2b) SHA1(47725a8059346ebe5639bbdbf62a2ac8028756a9) )

	NEO_BIOS_AUDIO_128K( "074.m1", CRC(5a52a9d1) SHA1(ef913a9a55d29d5dd3beab1ce6039d64ce9b1a5b) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "074.v1", 0x000000, 0x200000, CRC(7675b8fa) SHA1(29f4facf89d551237b31bf779693cbbbc94e1ede) )
	ROM_LOAD( "074.v2", 0x200000, 0x200000, CRC(a9da86e9) SHA1(ff65af61e42b79a75060a352b24077d1fa28c83f) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "074.c1", 0x000000, 0x200000, CRC(a0b39344) SHA1(adfff7b8836347abf030611563e6068a91164d0a) )
	ROM_LOAD16_BYTE( "074.c2", 0x000001, 0x200000, CRC(203f6074) SHA1(737f2d707d504df1da1ca5c5cf61cf489a33eb56) )
	ROM_LOAD16_BYTE( "074.c3", 0x400000, 0x200000, CRC(7fff4d41) SHA1(bebd18a75adeb34c3bbd49cfc8fd3d8c2bf9e475) )
	ROM_LOAD16_BYTE( "074.c4", 0x400001, 0x200000, CRC(48db3e0a) SHA1(a88505e001e01bb45fb26beda5af24943d02552a) )
	ROM_LOAD16_BYTE( "074.c5", 0x800000, 0x200000, CRC(c74c5e51) SHA1(0399c53e2a3d721901dddc073fda6ec22e02dfd4) )
	ROM_LOAD16_BYTE( "074.c6", 0x800001, 0x200000, CRC(73e8e7e0) SHA1(dd6580227743e6a3db4950456ebe870008e022b2) )
	ROM_LOAD16_BYTE( "074.c7", 0xc00000, 0x200000, CRC(ac7daa01) SHA1(78407a464f67d949933ce2ccaa23fbed80dff1ea) )
	ROM_LOAD16_BYTE( "074.c8", 0xc00001, 0x200000, CRC(14e7ad71) SHA1(d4583fbce361fd1a11ac6c1a27b0b669e8a5c718) )
ROM_END

/****************************************
 ID-0075
 . NGM-075
 NEO-MVS PROGGSC / NEO-MVS CHA256
 . NGH-075
 NEO-AEG PROGRK / NEO-AEG CHA256
****************************************/

ROM_START( sonicwi2 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "075.p1", 0x100000, 0x100000, CRC(92871738) SHA1(fed040a7c1ff9e495109813a702d09fb1d2ecf3a) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "075.s1", CRC(c9eec367) SHA1(574e1afe7e0d54610c145131106e59ba2894eeb7) )

	NEO_BIOS_AUDIO_128K( "075.m1", CRC(bb828df1) SHA1(eab8e2868173bdaac7c7ed97305a9aa1033fd303) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "075.v1", 0x000000, 0x200000, CRC(7577e949) SHA1(3ba9f11094dd0cf519f33a16016cfae0d2c6629c) )
	ROM_LOAD( "075.v2", 0x200000, 0x100000, CRC(021760cd) SHA1(8a24e38f1d4982c4dcd82718995571ac94cbb390) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "075.c1", 0x000000, 0x200000, CRC(3278e73e) SHA1(d9e6c8a3a5213690a1b8747d27806d8ac5aac405) )
	ROM_LOAD16_BYTE( "075.c2", 0x000001, 0x200000, CRC(fe6355d6) SHA1(ca72fff7a908b6d9325761079ff2a0e28f34cf89) )
	ROM_LOAD16_BYTE( "075.c3", 0x400000, 0x200000, CRC(c1b438f1) SHA1(b3751c5b426bca0fcc3a58bdb86712c22ef908ab) )
	ROM_LOAD16_BYTE( "075.c4", 0x400001, 0x200000, CRC(1f777206) SHA1(e29c5ae65ebdcc1167a894306d2446ce909639da) )
ROM_END

/****************************************
 ID-0076
 . ??M-076
 NEO-MVS PROGGSC / NEO-MVS CHA256
****************************************/

ROM_START( zedblade ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "076.p1", 0x000000, 0x080000, CRC(d7c1effd) SHA1(485c2308a40baecd122be9ab4996044622bdcc7e) )

	NEO_SFIX_128K( "076.s1", CRC(f4c25dd5) SHA1(8ec9026219f393930634f9170edbaaee479f875e) )

	NEO_BIOS_AUDIO_128K( "076.m1", CRC(7b5f3d0a) SHA1(4a301781a57ff236f49492b576ff4858b0ffbdf8) )

	ROM_REGION( 0x500000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "076.v1", 0x000000, 0x200000, CRC(1a21d90c) SHA1(4793ab06421228ad122e359653ed0f1339b90c7a) )
	ROM_LOAD( "076.v2", 0x200000, 0x200000, CRC(b61686c3) SHA1(5a3405e833ce36abb7421190438b5cccc8537919) )
	ROM_LOAD( "076.v3", 0x400000, 0x100000, CRC(b90658fa) SHA1(b9a4b34565ce3688495c47e35c9b888ef686ae9f) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "076.c1", 0x000000, 0x200000, CRC(4d9cb038) SHA1(c0b52b32e1fa719b99ae242d61d5dbea1437331c) )
	ROM_LOAD16_BYTE( "076.c2", 0x000001, 0x200000, CRC(09233884) SHA1(1895cd0d126a022bce1cc4c7a569032d89f35e3f) )
	ROM_LOAD16_BYTE( "076.c3", 0x400000, 0x200000, CRC(d06431e3) SHA1(643bd1ad74af272795b02143ba80a76e375036ab) )
	ROM_LOAD16_BYTE( "076.c4", 0x400001, 0x200000, CRC(4b1c089b) SHA1(cd63961d88c5be84673cce83c683a86b222a064d) )
ROM_END

/****************************************
 ID-0077
 The Warlocks of the Fates / Shinryu Senki (prototype) 1995 SNK/Astec21
 a video of intro and full gameplay was on youtube in 2014.
****************************************/

/****************************************
 ID-0078
 . NGM-078
 NEO-MVS PROGTOP / NEO-MVS CHA256
 . NGH-078
****************************************/

ROM_START( galaxyfg )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "078.p1", 0x100000, 0x100000, CRC(45906309) SHA1(cdcd96a564acf42e959193e139e149b29c103e25) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "078.s1", CRC(72f8923e) SHA1(da908bffc2b5d8baa2002dbb5bfb3aa17d2472b7) )

	NEO_BIOS_AUDIO_128K( "078.m1", CRC(8e9e3b10) SHA1(7c44d1dbd4f8d337c99e90361d1dab837df85e31) )

	ROM_REGION( 0x500000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "078.v1", 0x000000, 0x200000, CRC(e3b735ac) SHA1(e16dfac09aef8115a20bae0bef8c86d4e7d0dc4a) )
	ROM_LOAD( "078.v2", 0x200000, 0x200000, CRC(6a8e78c2) SHA1(f60b1f8a3a945f279a582745e82f37278ce5d83b) )
	ROM_LOAD( "078.v3", 0x400000, 0x100000, CRC(70bca656) SHA1(218b7079c90898e7faa382b386e77f81f415e7ac) )

	ROM_REGION( 0xe00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "078.c1", 0x000000, 0x200000, CRC(c890c7c0) SHA1(b96c18a41c34070a4f24ca77cb7516fae8b0fd0c) )
	ROM_LOAD16_BYTE( "078.c2", 0x000001, 0x200000, CRC(b6d25419) SHA1(e089df9c9a9645f706e501108d634f4d222622a2) )
	ROM_LOAD16_BYTE( "078.c3", 0x400000, 0x200000, CRC(9d87e761) SHA1(ea1b6d7c9d5ef3a9b48968bde5a52d5699d591cc) )
	ROM_LOAD16_BYTE( "078.c4", 0x400001, 0x200000, CRC(765d7cb8) SHA1(7b9c86714d688602064d928c9d2b49d70bb7541e) )
	ROM_LOAD16_BYTE( "078.c5", 0x800000, 0x200000, CRC(e6b77e6a) SHA1(db3b8fc62a6f21c6653621c0665450d5d9a9913d) )
	ROM_LOAD16_BYTE( "078.c6", 0x800001, 0x200000, CRC(d779a181) SHA1(2761026abd9698a7b56114b76631563abd41fd12) )
	ROM_LOAD16_BYTE( "078.c7", 0xc00000, 0x100000, CRC(4f27d580) SHA1(c0f12496b45b2fe6e94aa8ac52b0157063127e0a) )
	ROM_LOAD16_BYTE( "078.c8", 0xc00001, 0x100000, CRC(0a7cc0d8) SHA1(68aaee6341c87e56ce11acc1c4ec8047839fe70d) )
ROM_END

/****************************************
 ID-0079
 . DEM-004
 NEO-MVS PROGGSC / NEO-MVS CHA256
 . DEH-004
 NEO-AEG PROGRK  / NEO-AEG CHA256
****************************************/

ROM_START( strhoop ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "079.p1", 0x000000, 0x100000, CRC(5e78328e) SHA1(7a00b096ed6dd77afc3008c5a4c83686e475f323) )

	NEO_SFIX_128K( "079.s1", CRC(3ac06665) SHA1(ba9ab51eb95c3568304377ef6d7b5f32e8fbcde1) )

	NEO_BIOS_AUDIO_128K( "079.m1", CRC(bee3455a) SHA1(fd5345d9847982085a9b364fff542580889bf02f) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "079.v1", 0x000000, 0x200000, CRC(718a2400) SHA1(cefc5d0b302bd4a87ab1fa244ade4482c23c6806) )
	ROM_LOAD( "079.v2", 0x200000, 0x100000, CRC(720774eb) SHA1(e4926f01322d0a15e700fb150b368152f2091146) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "079.c1", 0x000000, 0x200000, CRC(0581c72a) SHA1(453f7a8474195a1120da5fa24337d79674563d9e) )
	ROM_LOAD16_BYTE( "079.c2", 0x000001, 0x200000, CRC(5b9b8fb6) SHA1(362aa0de0d2cf9aa03758363ffb1e15e046a3930) )
	ROM_LOAD16_BYTE( "079.c3", 0x400000, 0x200000, CRC(cd65bb62) SHA1(6f47d77d61d4289bcee82df7c4efa5346a6e4c80) )
	ROM_LOAD16_BYTE( "079.c4", 0x400001, 0x200000, CRC(a4c90213) SHA1(1b9f7b5f31acd6df2bdab81b849f32c13aa1b884) )
ROM_END

/****************************************
 ID-0080
 . SAM-080
 NEO-MVS PROGGSC / NEO-MVS CHA256
 NEO-MVS PROGTOP / NEO-MVS CHA256
 Boards used for the Korean release
 . SAH-080
 NEO-AEG PROGTOP2 / NEO-AEG CHA256 B
****************************************/

ROM_START( quizkof ) /* MVS AND AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "080.p1", 0x000000, 0x100000, CRC(4440315e) SHA1(f4adba8e341d64a1f6280dfd98ebf6918c00608d) )

	NEO_SFIX_128K( "080.s1", CRC(d7b86102) SHA1(09e1ca6451f3035ce476e3b045541646f860aad5) )

	NEO_BIOS_AUDIO_128K( "080.m1", CRC(f5f44172) SHA1(eaaba1781622901b91bce9257be4e05f84df053b) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "080.v1", 0x000000, 0x200000, CRC(0be18f60) SHA1(05c8b7d9f5a8583015f31902ad16d9c621f47d4e) )
	ROM_LOAD( "080.v2", 0x200000, 0x200000, CRC(4abde3ff) SHA1(0188bfcafa9a1aac302705736a2bcb26b9d684c2) )
	ROM_LOAD( "080.v3", 0x400000, 0x200000, CRC(f02844e2) SHA1(8c65ebe146f4ddb6c904f8125cb32767f74c24d5) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "080.c1", 0x000000, 0x200000, CRC(ea1d764a) SHA1(78cc1735624c37f90607baa92e110a3c5cc54c6f) )
	ROM_LOAD16_BYTE( "080.c2", 0x000001, 0x200000, CRC(d331d4a4) SHA1(94228d13fb1e30973eb54058e697f17456ee16ea) )
	ROM_LOAD16_BYTE( "080.c3", 0x400000, 0x200000, CRC(b4851bfe) SHA1(b8286c601de5755c1681ea46e177fc89006fc066) )
	ROM_LOAD16_BYTE( "080.c4", 0x400001, 0x200000, CRC(ca6f5460) SHA1(ed36e244c9335f4c0a97c57b7b7f1b849dd3a90d) )
ROM_END

ROM_START( quizkofk ) /* KOREAN VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "080k.p1", 0x000000, 0x100000, CRC(2589488e) SHA1(609f3095c1cf8b11335b56f23c5d955eebd66dd2) )

	NEO_SFIX_128K( "080k.s1", CRC(af72c30f) SHA1(f6a2c583f38295b7da2cbcf4b2c7ed3d3e01db4f) )

	NEO_BIOS_AUDIO_128K( "080k.m1", CRC(4f157e9a) SHA1(8397bfdd5738914670ada7cd8c611c20ed1f74da) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "080.v1", 0x000000, 0x200000, CRC(0be18f60) SHA1(05c8b7d9f5a8583015f31902ad16d9c621f47d4e) )
	ROM_LOAD( "080k.v2", 0x200000, 0x200000, CRC(719fee5b) SHA1(c94f8ca066c9693cd7c9fd311db1ad9b2665fc69) )
	ROM_LOAD( "080k.v3", 0x400000, 0x200000, CRC(64b7efde) SHA1(11727f9a3c4da17fa7b00559c7081b66e7211c49) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "080k.c1", 0x000000, 0x200000, CRC(94d90170) SHA1(4ab63dadc6ee0d32b8784c327681376f5fef0df9) )
	ROM_LOAD16_BYTE( "080k.c2", 0x000001, 0x200000, CRC(297f25a1) SHA1(0dd845726c640d70804b5fd5854921771e8dbf19) )
	ROM_LOAD16_BYTE( "080k.c3", 0x400000, 0x200000, CRC(cf484c4f) SHA1(f588908a693dbbb8362ffbfe5035dd5f867d9697) )
	ROM_LOAD16_BYTE( "080k.c4", 0x400001, 0x200000, CRC(36e5d997) SHA1(99955ff947e2e586e60c1146c978c70705787917) )
ROM_END

/****************************************
 ID-0081
 . NGM-081
 NEO-MVS PROGTOP / NEO-MVS CHA42G-3B
 NEO-MVS PROGTOP / NEO-MVS CHA256
 NEO-MVS PROG 4096 B / NEO-MVS CHA 42G-3
 NEO-MVS PROGBK1 / NEO-MVS CHA256B
 . NGH-081
 NEO-AEG PROGTOP2 / NEO-AEG CHA256 B
****************************************/

ROM_START( ssideki3 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "081.p1", 0x100000, 0x100000, CRC(6bc27a3d) SHA1(94692abe7343f9204a557acae4ab74d0af511ca3) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "081.s1", CRC(7626da34) SHA1(30bad65633d0035fd578323c22cbddb8c9d549a6) )

	NEO_BIOS_AUDIO_128K( "081.m1", CRC(82fcd863) SHA1(b219a5685450f9c24cc195f1c914bc3b292d72c0) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "081.v1", 0x000000, 0x200000, CRC(201fa1e1) SHA1(9c27cc1b1d075223ed4a90dd02571d09a2f0d076) )
	ROM_LOAD( "081.v2", 0x200000, 0x200000, CRC(acf29d96) SHA1(5426985c33aea2efc8ff774b59d34d8b03bd9a85) )
	ROM_LOAD( "081.v3", 0x400000, 0x200000, CRC(e524e415) SHA1(8733e1b63471381b16c2b7c64b909745d99c8925) )

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "081.c1", 0x000000, 0x200000, CRC(1fb68ebe) SHA1(abd9dbe7b7cbe0b6cd1d87e53c6bdc6edeccf83c) )
	ROM_LOAD16_BYTE( "081.c2", 0x000001, 0x200000, CRC(b28d928f) SHA1(9f05148e3e1e94339752658c066f47f133db8fbf) )
	ROM_LOAD16_BYTE( "081.c3", 0x400000, 0x200000, CRC(3b2572e8) SHA1(41aba1554bf59d4e5d5814249eaa0d531449e1de) )
	ROM_LOAD16_BYTE( "081.c4", 0x400001, 0x200000, CRC(47d26a7c) SHA1(591ef24a3d381163c5da80fa64e6883b8ea9abfb) )
	ROM_LOAD16_BYTE( "081.c5", 0x800000, 0x200000, CRC(17d42f0d) SHA1(7de7765bf43d390c50b2f59c2288502a7121d086) )
	ROM_LOAD16_BYTE( "081.c6", 0x800001, 0x200000, CRC(6b53fb75) SHA1(fadf7a12661d83ae35d9258aa4947969d51c08b8) )
ROM_END

/****************************************
 ID-0082
 . NGM-082
 NEO-MVS PROGTOP / NEO-MVS CHA256
 NEO-MVS PROGTOP / NEO-MVS CHA 42G-3
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 NEO-MVS PROGTOP / NEO-MVS CHA256B
 NEO-MVS PROG 4096 B / NEO-MVS CHA 42G-3
 . NGH-082
****************************************/

ROM_START( doubledr )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "082.p1", 0x100000, 0x100000, CRC(34ab832a) SHA1(fbb1bd195f5653f7b9c89648649f838eaf83cbe4) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "082.s1", CRC(bef995c5) SHA1(9c89adbdaa5c1f827632c701688563dac2e482a4) )

	NEO_BIOS_AUDIO_128K( "082.m1", CRC(10b144de) SHA1(cf1ed0a447da68240c62bcfd76b1569803f6bf76) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "082.v1", 0x000000, 0x200000, CRC(cc1128e4) SHA1(bfcfff24bc7fbde0b02b1bc0dffebd5270a0eb04) )
	ROM_LOAD( "082.v2", 0x200000, 0x200000, CRC(c3ff5554) SHA1(c685887ad64998e5572607a916b023f8b9efac49) )

	ROM_REGION( 0xe00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "082.c1", 0x000000, 0x200000, CRC(b478c725) SHA1(3a777c5906220f246a6dc06cb084e6ad650d67bb) )
	ROM_LOAD16_BYTE( "082.c2", 0x000001, 0x200000, CRC(2857da32) SHA1(9f13245965d23db86d46d7e73dfb6cc63e6f25a1) )
	ROM_LOAD16_BYTE( "082.c3", 0x400000, 0x200000, CRC(8b0d378e) SHA1(3a347215e414b738164f1fe4144102f07d4ffb80) )
	ROM_LOAD16_BYTE( "082.c4", 0x400001, 0x200000, CRC(c7d2f596) SHA1(e2d09d4d1b1fef9c0c53ecf3629e974b75e559f5) )
	ROM_LOAD16_BYTE( "082.c5", 0x800000, 0x200000, CRC(ec87bff6) SHA1(3fa86da93881158c2c23443855922a7b32e55135) )
	ROM_LOAD16_BYTE( "082.c6", 0x800001, 0x200000, CRC(844a8a11) SHA1(b2acbd4cacce66fb32c052b2fba9984904679bda) )
	ROM_LOAD16_BYTE( "082.c7", 0xc00000, 0x100000, CRC(727c4d02) SHA1(8204c7f037d46e0c58f269f9c7a535bc2589f526) )
	ROM_LOAD16_BYTE( "082.c8", 0xc00001, 0x100000, CRC(69a5fa37) SHA1(020e70e0e8b3c5d00a40fe97e418115a3187e50a) )
ROM_END

/****************************************
 ID-0083
 . NGM-083
 NEO-MVS PROGTOP / NEO-MVS CHA256
****************************************/

ROM_START( pbobblen ) /* MVS ONLY RELEASE */
	/* This set uses CHA and PROG board from Power Spikes II. Six Power Spikes II prom's are replaced with
	Puzzle Bobble prom's. Confirmed on several original carts. Do other layouts also exist? */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "083.p1", 0x000000, 0x080000, CRC(6102ca14) SHA1(328429d11de5b327a0654ae0548da4d0025a2ae6) )

	NEO_SFIX_128K( "083.s1", CRC(9caae538) SHA1(cf2d90a7c1a42107c0bb8b9a61397634286dbe0a) )

	NEO_BIOS_AUDIO_128K( "083.m1", CRC(f424368a) SHA1(5e5bbcaeb82bed2ee17df08f005ca20ad1030723) )

	ROM_REGION( 0x380000, "ymsnd:adpcma", 0 )
	//ROM_LOAD( "068.v1", 0x000000, 0x100000, CRC(2ced86df) SHA1(d6b73d1f31efbd74fb745200d4dade5f80b71541) ) /* unused */
	//ROM_LOAD( "068.v2", 0x100000, 0x100000, CRC(970851ab) SHA1(6c9b04e9cc6b92133f1154e5bdd9d38d8ef050a7) ) /* unused */
	ROM_LOAD( "083.v3", 0x200000, 0x100000, CRC(0840cbc4) SHA1(1adbd7aef44fa80832f63dfb8efdf69fd7256a57) )
	ROM_LOAD( "083.v4", 0x300000, 0x080000, CRC(0a548948) SHA1(e1e4afd17811cb60401c14fbcf0465035165f4fb) )

	ROM_REGION( 0x500000, "sprites", 0 )
	//ROM_LOAD16_BYTE( "068.c1", 0x000000, 0x100000, CRC(7f250f76) SHA1(5109a41adcb7859e24dc43d88842d4cc18cd3305) ) /* unused */
	//ROM_LOAD16_BYTE( "068.c2", 0x000001, 0x100000, CRC(20912873) SHA1(2df8766b531e47ffc30457e41c63b83557b4f468) ) /* unused */
	//ROM_LOAD16_BYTE( "068.c3", 0x200000, 0x100000, CRC(4b641ba1) SHA1(7a9c42a30163eda455f7bde2302402b1a5de7178) ) /* unused */
	//ROM_LOAD16_BYTE( "068.c4", 0x200001, 0x100000, CRC(35072596) SHA1(4150a21041f06514c97592bd8af686504b06e187) ) /* unused */
	ROM_LOAD16_BYTE( "083.c5", 0x400000, 0x080000, CRC(e89ad494) SHA1(69c9ea415773af94ac44c48af05d55ada222b138) )
	ROM_LOAD16_BYTE( "083.c6", 0x400001, 0x080000, CRC(4b42d7eb) SHA1(042ae50a528cea21cf07771d3915c57aa16fd5af) )
ROM_END

/****************************************
 ID-0084
 . NGM-084
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 NEO-MVS PROGSM / NEO-MVS CHA256
 . NGH-084
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( kof95 ) /* MVS VERSION */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "084.p1",0x100000, 0x100000, CRC(2cba2716) SHA1(f6c2d0537c9c3e0938065c65b1797c47198fcff8) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "084.s1", CRC(de716f8a) SHA1(f7386454a943ed5caf625f67ee1d0197b1c6fa13) )

	NEO_BIOS_AUDIO_128K( "084.m1", CRC(6f2d7429) SHA1(6f8462e4f07af82a5ca3197895d5dcbb67bdaa61) )

	ROM_REGION( 0x900000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "084.v1", 0x000000, 0x400000, CRC(84861b56) SHA1(1b6c91ddaed01f45eb9b7e49d9c2b9b479d50da6) )
	ROM_LOAD( "084.v2", 0x400000, 0x200000, CRC(b38a2803) SHA1(dbc2c8606ca09ed7ff20906b022da3cf053b2f09) )
	ROM_LOAD( "084.v3", 0x800000, 0x100000, CRC(d683a338) SHA1(eb9866b4b286edc09963cb96c43ce0a8fb09adbb) )

	ROM_REGION( 0x1a00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "084.c1", 0x0000000, 0x400000, CRC(fe087e32) SHA1(e8e89faa616027e4fb9b8a865c1a67f409c93bdf) )
	ROM_LOAD16_BYTE( "084.c2", 0x0000001, 0x400000, CRC(07864e09) SHA1(0817fcfd75d0735fd8ff27561eaec371e4ff5829) )
	ROM_LOAD16_BYTE( "084.c3", 0x0800000, 0x400000, CRC(a4e65d1b) SHA1(740a405b40b3a4b324697d2652cae29ffe0ac0bd) )
	ROM_LOAD16_BYTE( "084.c4", 0x0800001, 0x400000, CRC(c1ace468) SHA1(74ea2a3cfd7b744f0988a05baaff10016ca8f625) )
	ROM_LOAD16_BYTE( "084.c5", 0x1000000, 0x200000, CRC(8a2c1edc) SHA1(67866651bc0ce27122285a66b0aab108acf3d065) )
	ROM_LOAD16_BYTE( "084.c6", 0x1000001, 0x200000, CRC(f593ac35) SHA1(302c92c63f092a8d49429c3331e5e5678f0ea48d) )
	ROM_LOAD16_BYTE( "084.c7", 0x1800000, 0x100000, CRC(9904025f) SHA1(eec770746a0ad073f7d353ab16a2cc3a5278d307) )
	ROM_LOAD16_BYTE( "084.c8", 0x1800001, 0x100000, CRC(78eb0f9b) SHA1(2925ea21ed2ce167f08a25589e94f28643379034) )
ROM_END

ROM_START( kof95a ) /* MVS VERSION */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "084a.p1", 0x000000, 0x080000, CRC(577ca1bb) SHA1(0d9d8b6db8a5a4ea47fd6602bc77df68b74b1691) )
	ROM_LOAD16_WORD_SWAP( "084a.p2", 0x080000, 0x080000, CRC(30802a5d) SHA1(04109e7c4f8d171fcebbe1198f85a271b008f8f1) )
	ROM_LOAD16_WORD_SWAP( "084a.p3", 0x100000, 0x080000, CRC(21ae248a) SHA1(87318a1bc667f31a9824beefee94617b4724dc2d) )
	ROM_LOAD16_WORD_SWAP( "084a.p4", 0x180000, 0x080000, CRC(19d3fbee) SHA1(39225ec8a7ed5d2f5e83f5d575b9fa38800b0704) )

	NEO_SFIX_128K( "084.s1", CRC(de716f8a) SHA1(f7386454a943ed5caf625f67ee1d0197b1c6fa13) )

	NEO_BIOS_AUDIO_128K( "084.m1", CRC(6f2d7429) SHA1(6f8462e4f07af82a5ca3197895d5dcbb67bdaa61) )

	ROM_REGION( 0x900000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "084.v1", 0x000000, 0x400000, CRC(84861b56) SHA1(1b6c91ddaed01f45eb9b7e49d9c2b9b479d50da6) )
	ROM_LOAD( "084.v2", 0x400000, 0x200000, CRC(b38a2803) SHA1(dbc2c8606ca09ed7ff20906b022da3cf053b2f09) )
	ROM_LOAD( "084.v3", 0x800000, 0x100000, CRC(d683a338) SHA1(eb9866b4b286edc09963cb96c43ce0a8fb09adbb) )

	ROM_REGION( 0x1a00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "084.c1", 0x0000000, 0x400000, CRC(fe087e32) SHA1(e8e89faa616027e4fb9b8a865c1a67f409c93bdf) )
	ROM_LOAD16_BYTE( "084.c2", 0x0000001, 0x400000, CRC(07864e09) SHA1(0817fcfd75d0735fd8ff27561eaec371e4ff5829) )
	ROM_LOAD16_BYTE( "084.c3", 0x0800000, 0x400000, CRC(a4e65d1b) SHA1(740a405b40b3a4b324697d2652cae29ffe0ac0bd) )
	ROM_LOAD16_BYTE( "084.c4", 0x0800001, 0x400000, CRC(c1ace468) SHA1(74ea2a3cfd7b744f0988a05baaff10016ca8f625) )
	ROM_LOAD16_BYTE( "084.c5", 0x1000000, 0x200000, CRC(8a2c1edc) SHA1(67866651bc0ce27122285a66b0aab108acf3d065) )
	ROM_LOAD16_BYTE( "084.c6", 0x1000001, 0x200000, CRC(f593ac35) SHA1(302c92c63f092a8d49429c3331e5e5678f0ea48d) )
	ROM_LOAD16_BYTE( "084.c7", 0x1800000, 0x100000, CRC(9904025f) SHA1(eec770746a0ad073f7d353ab16a2cc3a5278d307) )
	ROM_LOAD16_BYTE( "084.c8", 0x1800001, 0x100000, CRC(78eb0f9b) SHA1(2925ea21ed2ce167f08a25589e94f28643379034) )
ROM_END

ROM_START( kof95h ) /* MVS AND AES VERSION */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "084.p1", 0x100000, 0x100000, CRC(5e54cf95) SHA1(41abe2042fdbb1526e92a0789976a9b1ac5e60f0) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "084.s1", CRC(de716f8a) SHA1(f7386454a943ed5caf625f67ee1d0197b1c6fa13) )

	NEO_BIOS_AUDIO_128K( "084.m1", CRC(6f2d7429) SHA1(6f8462e4f07af82a5ca3197895d5dcbb67bdaa61) )

	ROM_REGION( 0x900000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "084.v1", 0x000000, 0x400000, CRC(84861b56) SHA1(1b6c91ddaed01f45eb9b7e49d9c2b9b479d50da6) )
	ROM_LOAD( "084.v2", 0x400000, 0x200000, CRC(b38a2803) SHA1(dbc2c8606ca09ed7ff20906b022da3cf053b2f09) )
	ROM_LOAD( "084.v3", 0x800000, 0x100000, CRC(d683a338) SHA1(eb9866b4b286edc09963cb96c43ce0a8fb09adbb) )

	ROM_REGION( 0x1a00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "084.c1", 0x0000000, 0x400000, CRC(fe087e32) SHA1(e8e89faa616027e4fb9b8a865c1a67f409c93bdf) )
	ROM_LOAD16_BYTE( "084.c2", 0x0000001, 0x400000, CRC(07864e09) SHA1(0817fcfd75d0735fd8ff27561eaec371e4ff5829) )
	ROM_LOAD16_BYTE( "084.c3", 0x0800000, 0x400000, CRC(a4e65d1b) SHA1(740a405b40b3a4b324697d2652cae29ffe0ac0bd) )
	ROM_LOAD16_BYTE( "084.c4", 0x0800001, 0x400000, CRC(c1ace468) SHA1(74ea2a3cfd7b744f0988a05baaff10016ca8f625) )
	ROM_LOAD16_BYTE( "084.c5", 0x1000000, 0x200000, CRC(8a2c1edc) SHA1(67866651bc0ce27122285a66b0aab108acf3d065) )
	ROM_LOAD16_BYTE( "084.c6", 0x1000001, 0x200000, CRC(f593ac35) SHA1(302c92c63f092a8d49429c3331e5e5678f0ea48d) )
	ROM_LOAD16_BYTE( "084.c7", 0x1800000, 0x100000, CRC(9904025f) SHA1(eec770746a0ad073f7d353ab16a2cc3a5278d307) )
	ROM_LOAD16_BYTE( "084.c8", 0x1800001, 0x100000, CRC(78eb0f9b) SHA1(2925ea21ed2ce167f08a25589e94f28643379034) )
ROM_END

/****************************************
 ID-0085
 Shinsetsu Samurai Spirits Bushidoretsuden / Samurai Shodown RPG (CD only)
****************************************/

/****************************************
 ID-0086
 . ??M-086
 NEO-MVS PROGBK1 / NEO-MVS CHA256B
****************************************/

ROM_START( tws96 ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "086.p1", 0x000000, 0x100000, CRC(03e20ab6) SHA1(3a0a5a54649178ce7a6158980cb4445084b40fb5) )

	NEO_SFIX_128K( "086.s1", CRC(6f5e2b3a) SHA1(273341489f6625d35a4a920042a60e2b86373847) )

	NEO_BIOS_AUDIO_128K( "086.m1", CRC(cb82bc5d) SHA1(8e3ecabec25d89adb6e0eed0ef5f94d34a4d5fc0) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "086.v1", 0x000000, 0x200000, CRC(97bf1986) SHA1(b80d3a37e18d0a52f1e0092dc300989c9647efd1) )
	ROM_LOAD( "086.v2", 0x200000, 0x200000, CRC(b7eb05df) SHA1(ff2b55c7021c248cfdcfc9cd3658f2896bcbca38) )

	ROM_REGION( 0xa00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "086.c1", 0x000000, 0x400000, CRC(2611bc2a) SHA1(bb5a96acd4a90fcb41c49cc8e9f760c4a06d6b84) )
	ROM_LOAD16_BYTE( "086.c2", 0x000001, 0x400000, CRC(6b0d6827) SHA1(3cb2bbab381a26ec69f97c3d6116ce47254286b4) )
	ROM_LOAD16_BYTE( "086.c3", 0x800000, 0x100000, CRC(750ddc0c) SHA1(9304a83d81afd544d88be0cd3ee47ae401d2da0e) )
	ROM_LOAD16_BYTE( "086.c4", 0x800001, 0x100000, CRC(7a6e7d82) SHA1(b1bb82cec3d68367d5e01e63c44c11b67e577411) )
ROM_END

/****************************************
 ID-0087
 . NGM-087
 NEO-MVS PROGSS3 / NEO-MVS CHA256
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . NGH-087
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( samsho3 ) /* MVS VERSION */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "087.p1", 0x000000, 0x080000, CRC(23e09bb8) SHA1(79da99fa50a639fce9d1266699b5e53c9ac55642) )
	ROM_LOAD16_WORD_SWAP( "087.p2", 0x080000, 0x080000, CRC(256f5302) SHA1(e2d21b413a6059194a994b7902b2a7df98a15151) )
	ROM_LOAD16_WORD_SWAP( "087.p3", 0x100000, 0x080000, CRC(bf2db5dd) SHA1(b4fa1dc1eccc9eb1ce74f0a06992ef89b1cbc732) )
	ROM_LOAD16_WORD_SWAP( "087.p4", 0x180000, 0x080000, CRC(53e60c58) SHA1(f975e81cab6322d3260348402721c673023259fa) )
	ROM_LOAD16_WORD_SWAP( "087.p5",  0x200000, 0x100000, CRC(e86ca4af) SHA1(5246acbab77ac2f232b88b8522187764ff0872f0) )

	NEO_SFIX_128K( "087.s1", CRC(74ec7d9f) SHA1(d79c479838a7ca51735a44f91f1968ec5b3c6b91) )

	NEO_BIOS_AUDIO_128K( "087.m1", CRC(8e6440eb) SHA1(e3f72150af4e326543b29df71cda27d73ec087c1) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "087.v1", 0x000000, 0x400000, CRC(84bdd9a0) SHA1(adceceb00569eca13fcc2e0f0d9f0d9b06a06851) )
	ROM_LOAD( "087.v2", 0x400000, 0x200000, CRC(ac0f261a) SHA1(5411bdff24cba7fdbc3397d45a70fb468d7a44b3) )

	ROM_REGION( 0x1a00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "087.c1", 0x0000000, 0x400000, CRC(07a233bc) SHA1(654cb56cfd6eeebe6745c0b8b730317fb8ccd3d9) )
	ROM_LOAD16_BYTE( "087.c2", 0x0000001, 0x400000, CRC(7a413592) SHA1(b8c7a2d0d7a8b14d6cab94d7a5f347e73c6ab7a4) )
	ROM_LOAD16_BYTE( "087.c3", 0x0800000, 0x400000, CRC(8b793796) SHA1(053acc129ea56691607a5d255845703e61fd3ada) )
	ROM_LOAD16_BYTE( "087.c4", 0x0800001, 0x400000, CRC(728fbf11) SHA1(daa319d455f759bfc08a37b43218bdb48dc1c9e5) )
	ROM_LOAD16_BYTE( "087.c5", 0x1000000, 0x400000, CRC(172ab180) SHA1(a6122f683bdb78d0079e1e360c1b96ba28def7b7) )
	ROM_LOAD16_BYTE( "087.c6", 0x1000001, 0x400000, CRC(002ff8f3) SHA1(3a378708697d727796c4f702dd5bbf1c9eb4daec) )
	ROM_LOAD16_BYTE( "087.c7", 0x1800000, 0x100000, CRC(ae450e3d) SHA1(ec482632cc347ec3f9e68df0ebcaa16ebe41b9f9) )
	ROM_LOAD16_BYTE( "087.c8", 0x1800001, 0x100000, CRC(a9e82717) SHA1(e39ee15d5140dbe7f06eea945cce9984a5e8b06a) )
ROM_END

ROM_START( samsho3h ) /* AES VERSION */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "087h.p1", 0x000000, 0x100000, CRC(282a336e) SHA1(e062f1939d36a45f185b5dbd726cdd833dc7c28c) )
	ROM_LOAD16_WORD_SWAP( "087h.p2", 0x100000, 0x200000, CRC(9bbe27e0) SHA1(b18117102159903c8e8f4e4226e1cc91a400e816) )

	NEO_SFIX_128K( "087.s1", CRC(74ec7d9f) SHA1(d79c479838a7ca51735a44f91f1968ec5b3c6b91) )

	NEO_BIOS_AUDIO_128K( "087.m1", CRC(8e6440eb) SHA1(e3f72150af4e326543b29df71cda27d73ec087c1) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "087.v1", 0x000000, 0x400000, CRC(84bdd9a0) SHA1(adceceb00569eca13fcc2e0f0d9f0d9b06a06851) )
	ROM_LOAD( "087.v2", 0x400000, 0x200000, CRC(ac0f261a) SHA1(5411bdff24cba7fdbc3397d45a70fb468d7a44b3) )

	ROM_REGION( 0x1a00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "087.c1", 0x0000000, 0x400000, CRC(07a233bc) SHA1(654cb56cfd6eeebe6745c0b8b730317fb8ccd3d9) )
	ROM_LOAD16_BYTE( "087.c2", 0x0000001, 0x400000, CRC(7a413592) SHA1(b8c7a2d0d7a8b14d6cab94d7a5f347e73c6ab7a4) )
	ROM_LOAD16_BYTE( "087.c3", 0x0800000, 0x400000, CRC(8b793796) SHA1(053acc129ea56691607a5d255845703e61fd3ada) )
	ROM_LOAD16_BYTE( "087.c4", 0x0800001, 0x400000, CRC(728fbf11) SHA1(daa319d455f759bfc08a37b43218bdb48dc1c9e5) )
	ROM_LOAD16_BYTE( "087.c5", 0x1000000, 0x400000, CRC(172ab180) SHA1(a6122f683bdb78d0079e1e360c1b96ba28def7b7) )
	ROM_LOAD16_BYTE( "087.c6", 0x1000001, 0x400000, CRC(002ff8f3) SHA1(3a378708697d727796c4f702dd5bbf1c9eb4daec) )
	ROM_LOAD16_BYTE( "087.c7", 0x1800000, 0x100000, CRC(ae450e3d) SHA1(ec482632cc347ec3f9e68df0ebcaa16ebe41b9f9) )
	ROM_LOAD16_BYTE( "087.c8", 0x1800001, 0x100000, CRC(a9e82717) SHA1(e39ee15d5140dbe7f06eea945cce9984a5e8b06a) )
ROM_END

ROM_START( fswords ) /* KOREAN VERSION */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "187.p1", 0x000000, 0x100000, CRC(c8e7c075) SHA1(7b74f2917114460d79d8f46ee24829a4c08cbf2a) )
	ROM_LOAD16_WORD_SWAP( "087.p2", 0x100000, 0x200000, CRC(9bbe27e0) SHA1(b18117102159903c8e8f4e4226e1cc91a400e816) )

	NEO_SFIX_128K( "087.s1", CRC(74ec7d9f) SHA1(d79c479838a7ca51735a44f91f1968ec5b3c6b91) )

	NEO_BIOS_AUDIO_128K( "087.m1", CRC(8e6440eb) SHA1(e3f72150af4e326543b29df71cda27d73ec087c1) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "087.v1", 0x000000, 0x400000, CRC(84bdd9a0) SHA1(adceceb00569eca13fcc2e0f0d9f0d9b06a06851) )
	ROM_LOAD( "087.v2", 0x400000, 0x200000, CRC(ac0f261a) SHA1(5411bdff24cba7fdbc3397d45a70fb468d7a44b3) )

	ROM_REGION( 0x1a00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "087.c1", 0x0000000, 0x400000, CRC(07a233bc) SHA1(654cb56cfd6eeebe6745c0b8b730317fb8ccd3d9) )
	ROM_LOAD16_BYTE( "087.c2", 0x0000001, 0x400000, CRC(7a413592) SHA1(b8c7a2d0d7a8b14d6cab94d7a5f347e73c6ab7a4) )
	ROM_LOAD16_BYTE( "087.c3", 0x0800000, 0x400000, CRC(8b793796) SHA1(053acc129ea56691607a5d255845703e61fd3ada) )
	ROM_LOAD16_BYTE( "087.c4", 0x0800001, 0x400000, CRC(728fbf11) SHA1(daa319d455f759bfc08a37b43218bdb48dc1c9e5) )
	ROM_LOAD16_BYTE( "087.c5", 0x1000000, 0x400000, CRC(172ab180) SHA1(a6122f683bdb78d0079e1e360c1b96ba28def7b7) )
	ROM_LOAD16_BYTE( "087.c6", 0x1000001, 0x400000, CRC(002ff8f3) SHA1(3a378708697d727796c4f702dd5bbf1c9eb4daec) )
	ROM_LOAD16_BYTE( "087.c7", 0x1800000, 0x100000, CRC(ae450e3d) SHA1(ec482632cc347ec3f9e68df0ebcaa16ebe41b9f9) )
	ROM_LOAD16_BYTE( "087.c8", 0x1800001, 0x100000, CRC(a9e82717) SHA1(e39ee15d5140dbe7f06eea945cce9984a5e8b06a) )
ROM_END

/****************************************
 ID-0088
 . NGM-088
 NEO-MVS PROGBK1 / NEO-MVS CHA42-3B
 . NGH-088
 NEO-AEG PROGRKB / NEO-AEG CHA256[B]
****************************************/

ROM_START( stakwin )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "088.p1", 0x100000, 0x100000, CRC(bd5814f6) SHA1(95179a4dee61ae88bb5d9fd74af0c56c8c29f5ea) )
	ROM_CONTINUE( 0x000000, 0x100000)

	NEO_SFIX_128K( "088.s1", CRC(073cb208) SHA1(c5b4697d767575884dd49ae416c1fe4a4a92d3f6) )

	NEO_BIOS_AUDIO_128K( "088.m1", CRC(2fe1f499) SHA1(5b747eeef65be04423d2db05e086df9132758a47) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "088.v1", 0x000000, 0x200000, CRC(b7785023) SHA1(d11df1e623434669cd3f97f0feda747b24dac05d) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "088.c1", 0x000000, 0x200000, CRC(6e733421) SHA1(b67c5d2654a62cc4e44bd54d28e62c7da5eea424) )
	ROM_LOAD16_BYTE( "088.c2", 0x000001, 0x200000, CRC(4d865347) SHA1(ad448cf96f3dce44c83412ed6878c495eb4a8a1e) )
	ROM_LOAD16_BYTE( "088.c3", 0x400000, 0x200000, CRC(8fa5a9eb) SHA1(7bee19d8a2bccedd8e2cf0c0e9138902b9dafc23) )
	ROM_LOAD16_BYTE( "088.c4", 0x400001, 0x200000, CRC(4604f0dc) SHA1(ddf5dbb5e07313998a8f695ad19354ea54585dd6) )
ROM_END

/****************************************
 ID-0089
 . NGM-089
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . NGH-089
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( pulstar )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "089.p1",  0x000000, 0x100000, CRC(5e5847a2) SHA1(b864d0ec4184b785569ddbf67c2115b5ab86ee3e) )
	ROM_LOAD16_WORD_SWAP( "089.p2", 0x100000, 0x200000, CRC(028b774c) SHA1(fc5da2821a5072f2b78245fc59b6e3eeef116d16) )

	NEO_SFIX_128K( "089.s1", CRC(c79fc2c8) SHA1(914c224fb3c461a68d7425cae724cf22bd5f985d) )

	NEO_BIOS_AUDIO_128K( "089.m1", CRC(ff3df7c7) SHA1(59d2ef64f734f6026073b365300221909057a512) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "089.v1", 0x000000, 0x400000, CRC(6f726ecb) SHA1(e8e2a46af690ce6c7ee64a58ab5010d22df9548c) )
	ROM_LOAD( "089.v2", 0x400000, 0x400000, CRC(9d2db551) SHA1(83f7e5db7fb1502ceadcd334df90b11b1bba78e5) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "089.c1", 0x0000000, 0x400000, CRC(f4e97332) SHA1(54693827a99836e7d61c45d495dd78bf3fcf1544) )
	ROM_LOAD16_BYTE( "089.c2", 0x0000001, 0x400000, CRC(836d14da) SHA1(99cc4f9b764503eff7849ff2977d90bb47c5564a) )
	ROM_LOAD16_BYTE( "089.c3", 0x0800000, 0x400000, CRC(913611c4) SHA1(9664eb1fe1e6f8c3ddeeff872d38ea920ed38a82) )
	ROM_LOAD16_BYTE( "089.c4", 0x0800001, 0x400000, CRC(44cef0e3) SHA1(34f6f348ba86a2a06cb9c43a16b97cf6ee6158ac) )
	ROM_LOAD16_BYTE( "089.c5", 0x1000000, 0x400000, CRC(89baa1d7) SHA1(976c745c44967de61e2a23227835be580b1d283a) )
	ROM_LOAD16_BYTE( "089.c6", 0x1000001, 0x400000, CRC(b2594d56) SHA1(685c0bf8ff76c76e41c2ceaebb96349634cfdb2e) )
	ROM_LOAD16_BYTE( "089.c7", 0x1800000, 0x200000, CRC(6a5618ca) SHA1(9a1d5f998b0dfabacf9dad45c94bef2bb43e5e0c) )
	ROM_LOAD16_BYTE( "089.c8", 0x1800001, 0x200000, CRC(a223572d) SHA1(2791b1212f57937b2b2a95bc9e420c06d0c37669) )
ROM_END

/****************************************
 ID-0090
 . ADM-009
 NEO-MVS PROGTOP / NEO-MVS CHA256
 NEO-MVS PROGGSC / NEO-MVS CHA256
 NEO-MVS PROGGSC / NEO-MVS CHA256B
 NEO-MVS PROGBK1 / NEO-MVS CHA256B
 . ADH-009
****************************************/

ROM_START( whp )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "090.p1", 0x100000, 0x100000, CRC(afaa4702) SHA1(83d122fddf17d4774353abf4a0655f3939f7b752) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "090.s1", CRC(174a880f) SHA1(c35d315d728d119a6e9aa42e0593937c90897449) )

	NEO_BIOS_AUDIO_128K( "090.m1", CRC(28065668) SHA1(0c60d4afa1dccad0135e733104f056be73b54e4e) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "090.v1", 0x000000, 0x200000, CRC(30cf2709) SHA1(d1845033f16de2470afd3858ee0efb45176d9ed7) )
	ROM_LOAD( "064.v2", 0x200000, 0x200000, CRC(b6527edd) SHA1(2bcf5bfa6e117cf4a3728a5e5f5771313c93f22a) )
	ROM_LOAD( "090.v3", 0x400000, 0x200000, CRC(1908a7ce) SHA1(78f31bcfea33eb94752bbf5226c481baec1af5ac) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "090.c1", 0x0000000, 0x400000, CRC(cd30ed9b) SHA1(839c20f7ff31251acc875ae402b5d267e55510c7) )
	ROM_LOAD16_BYTE( "090.c2", 0x0000001, 0x400000, CRC(10eed5ee) SHA1(12131b1c8c017ea77a98c044b392a5db6aad0143) )
	ROM_LOAD16_BYTE( "064.c3", 0x0800000, 0x200000, CRC(436d1b31) SHA1(059776d77b91377ed0bcfc278802d659c917fc0f) )
	ROM_LOAD16_BYTE( "064.c4", 0x0800001, 0x200000, CRC(f9c8dd26) SHA1(25a9eea1d49b21b4a988beb32c25bf2f7796f227) )
	ROM_LOAD16_BYTE( "064.c5", 0x1000000, 0x200000, CRC(8e34a9f4) SHA1(67b839b426ef3fad0a85d951fdd44c0a45c55226) )
	ROM_LOAD16_BYTE( "064.c6", 0x1000001, 0x200000, CRC(a43e4766) SHA1(54f282f2b1ff2934cca7acbb4386a2b99a29df3a) )
	ROM_LOAD16_BYTE( "064.c7", 0x1800000, 0x200000, CRC(59d97215) SHA1(85a960dc7f364df13ee0c2f99a4c53aefb081486) )
	ROM_LOAD16_BYTE( "064.c8", 0x1800001, 0x200000, CRC(fc092367) SHA1(69ff4ae909dd857de3ca8645d63f8b4bde117448) )
ROM_END

/****************************************
 ID-0091
 ADK World / ADK Special 1995 ADK (CD only)
****************************************/

/****************************************
 ID-0092
 . NGM-092
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 NEO-MVS PROGTOP / NEO-MVS CHA256
 . NGH-092
****************************************/

ROM_START( kabukikl )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "092.p1", 0x100000, 0x100000, CRC(28ec9b77) SHA1(7cdc789a99f8127f437d68cbc41278c926be9efd) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "092.s1", CRC(a3d68ee2) SHA1(386f6110a16967a72fbf788f9d968fddcdcd2889) )

	NEO_BIOS_AUDIO_128K( "092.m1", CRC(91957ef6) SHA1(7b6907532a0e02ceb643623cbd689cf228776ed1) )

	ROM_REGION( 0x700000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "092.v1", 0x000000, 0x200000, CRC(69e90596) SHA1(1a2007d7784b3ce90d115980c3353862f1664d45) )
	ROM_LOAD( "092.v2", 0x200000, 0x200000, CRC(7abdb75d) SHA1(0bff764889fe02f37877514c7fc450250839f632) )
	ROM_LOAD( "092.v3", 0x400000, 0x200000, CRC(eccc98d3) SHA1(b0dfbdb1ea045cb961323ac6906ab342256c3dc7) )
	ROM_LOAD( "092.v4", 0x600000, 0x100000, CRC(a7c9c949) SHA1(574bc55b45e81ce357b14f5992426115de25cd35) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "092.c1", 0x000000, 0x400000, CRC(2a9fab01) SHA1(aa9f037df33ae0575b328734c76c0918ae1917e9) )
	ROM_LOAD16_BYTE( "092.c2", 0x000001, 0x400000, CRC(6d2bac02) SHA1(dfe96b62883333872be432e8af1ae617c9e62698) )
	ROM_LOAD16_BYTE( "092.c3", 0x800000, 0x400000, CRC(5da735d6) SHA1(f1c05a73794ece15576a0a30c81f4a44faac475a) )
	ROM_LOAD16_BYTE( "092.c4", 0x800001, 0x400000, CRC(de07f997) SHA1(c27a4d4bef868eed38dc152ff37d4135b16cc991) )
ROM_END

/****************************************
 ID-0093
 . ??M-093
 NEO-MVS PROGBK1 / NEO-MVS CHA256
****************************************/

ROM_START( neobombe ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "093.p1", 0x000000, 0x100000, CRC(a1a71d0d) SHA1(059284c84f61a825923d86d2f29c91baa2c439cd) )

	NEO_SFIX_128K( "093.s1", CRC(4b3fa119) SHA1(41cb0909bfb017eb6f2c530cb92a423319ed7ab1) )

	NEO_BIOS_AUDIO_128K( "093.m1", CRC(e81e780b) SHA1(c56c53984e0f92e180e850c60a75f550ee84917c) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "093.v1", 0x000000, 0x400000, CRC(02abd4b0) SHA1(6bf33ebc9b01cd4a029f6a555694a9835e30ca1b) )
	ROM_LOAD( "093.v2", 0x400000, 0x200000, CRC(a92b8b3d) SHA1(b672c97b85d2f52eba3cb26025008ebc7a18312a) )

	ROM_REGION( 0x900000, "sprites", 0 )
	ROM_LOAD16_BYTE( "093.c1", 0x000000, 0x400000, CRC(d1f328f8) SHA1(ddf71280c2ce85225f15fe9e973f330609281878) )
	ROM_LOAD16_BYTE( "093.c2", 0x000001, 0x400000, CRC(82c49540) SHA1(5f37c1bc0d63c98a13967b44da3d2c85e6dbbe50) )
	ROM_LOAD16_BYTE( "093.c3", 0x800000, 0x080000, CRC(e37578c5) SHA1(20024caa0f09ee887a6418dd02d02a0df93786fd) )
	ROM_LOAD16_BYTE( "093.c4", 0x800001, 0x080000, CRC(59826783) SHA1(0110a2b6186cca95f75225d4d0269d61c2ad25b1) )
ROM_END

/****************************************
 ID-0094
 . NGM-094
 NEO-MVS PROGBK1 / NEO-MVS CHA42G-3B
 . NGH-094
****************************************/

ROM_START( gowcaizr )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "094.p1", 0x100000, 0x100000, CRC(33019545) SHA1(213db6c0b7d24b74b809854f9c606dbea1d9ba00) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "094.s1", CRC(2f8748a2) SHA1(5cc723c4284120473d63d8b0c1a3b3be74bdc324) )

	NEO_BIOS_AUDIO_128K( "094.m1", CRC(78c851cb) SHA1(a9923c002e4e2171a564af45cff0958c5d57b275) )

	ROM_REGION( 0x500000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "094.v1", 0x000000, 0x200000, CRC(6c31223c) SHA1(ede3a2806d7d872a0f737626a23ecce200b534e6) )
	ROM_LOAD( "094.v2", 0x200000, 0x200000, CRC(8edb776c) SHA1(a9eac5e24f83ccdcf303d63261747b1bad876a24) )
	ROM_LOAD( "094.v3", 0x400000, 0x100000, CRC(c63b9285) SHA1(6bbbacfe899e204e74657d6c3f3d05ce75e432f1) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "094.c1", 0x000000, 0x200000, CRC(042f6af5) SHA1(1c50df6a1a53ffb3079ea0a19c746f5c9536a3ed) )
	ROM_LOAD16_BYTE( "094.c2", 0x000001, 0x200000, CRC(0fbcd046) SHA1(9a6dc920a877f27424477c3478907b23afbaa5ea) )
	ROM_LOAD16_BYTE( "094.c3", 0x400000, 0x200000, CRC(58bfbaa1) SHA1(4c6f9cf138c5e6dfe89a45e2a690a986c75f5bfc) )
	ROM_LOAD16_BYTE( "094.c4", 0x400001, 0x200000, CRC(9451ee73) SHA1(7befee4a886b1d7493c06cefb7abf4ec01c14a8b) )
	ROM_LOAD16_BYTE( "094.c5", 0x800000, 0x200000, CRC(ff9cf48c) SHA1(5f46fb5d0812275b0006919d8540f22be7c16492) )
	ROM_LOAD16_BYTE( "094.c6", 0x800001, 0x200000, CRC(31bbd918) SHA1(7ff8c5e3f17d40e7a8a189ad8f8026de55368810) )
	ROM_LOAD16_BYTE( "094.c7", 0xc00000, 0x200000, CRC(2091ec04) SHA1(a81d4bdbef1ac6ea49845dc30e31bf9745694100) )
	ROM_LOAD16_BYTE( "094.c8", 0xc00001, 0x200000, CRC(d80dd241) SHA1(1356a64e4d4e271f62cd0d83f79ee9c906440810) )
ROM_END

/****************************************
 dev board, same ID as gowcaizr
****************************************/

ROM_START( dragonsh )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "ep2.bin", 0x000000, 0x080000, CRC(f25c71ad) SHA1(803fb6cd6a7ada59678ad901ff9788b1e54ddd0c) )
	ROM_LOAD16_BYTE( "ep1.bin", 0x000001, 0x080000, CRC(f353448c) SHA1(f0f966ca15d503e01b40e901765ff0888463b65d) )

	NEO_SFIX_128K( "s1.s1", BAD_DUMP CRC(706477a7) SHA1(8cbee7f6832e7edd2dc792ca330420a6a984b879) ) // was a dead AXS512PC 512KB sram card, this data is handcrafted to make the set usable (hence BAD_DUMP)

	NEOGEO_BIOS
	ROM_REGION( 0x20000, "audiobios", 0 )
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) )
	ROM_REGION( 0x30000, "audiocpu", ROMREGION_ERASEFF )
	/* not present */

	ROM_REGION( 0x200000, "ymsnd:adpcma", ROMREGION_ERASE00 )
	ROM_LOAD( "sram.v1", 0x000000, 0x200000, NO_DUMP ) // was a dead AXS2000PC 2MB sram card, battery dead, data lost.

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "no3.bin", 0x000000, 0x1000000, CRC(81821826) SHA1(b7c1a53e32633383675206a16c68f6f2ff984865) )
	ROM_LOAD16_BYTE( "no4.bin", 0x000001, 0x1000000, CRC(3601d568) SHA1(800323e52f5d33b402f84d31850b42c688082d67) )
ROM_END

/****************************************
 ID-0095
 . NGM-095
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . NGH-095
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( rbff1 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "095.p1",  0x000000, 0x100000, CRC(63b4d8ae) SHA1(03aa9f6bab6aee685d1b57a52823797704eea845) )
	ROM_LOAD16_WORD_SWAP( "095.p2", 0x100000, 0x200000, CRC(cc15826e) SHA1(44d6ac6c0ca697a6f367dcfd809b1e1771cb0635) )

	NEO_SFIX_128K( "095.s1", CRC(b6bf5e08) SHA1(b527355c35ea097f3448676f2ffa65b8e56ae30c) )

	NEO_BIOS_AUDIO_128K( "095.m1", CRC(653492a7) SHA1(39e511fb9ed5d2135dc8428a31d0baafb2ab36e0) )

	ROM_REGION( 0xc00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "069.v1", 0x000000, 0x400000, CRC(2bdbd4db) SHA1(5f4fecf69c2329d699cbd45829c19303b1e2a80e) )
	ROM_LOAD( "069.v2", 0x400000, 0x400000, CRC(a698a487) SHA1(11b8bc53bc26a51f4a408e900e3769958625c4ed) )
	ROM_LOAD( "095.v3", 0x800000, 0x400000, CRC(189d1c6c) SHA1(f0b8cd1ee40ea3feeb2800f0723b451ec8240203) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "069.c1", 0x0000000, 0x400000, CRC(e302f93c) SHA1(d8610b14900b2b8fe691b67ca9b1abb335dbff74) )
	ROM_LOAD16_BYTE( "069.c2", 0x0000001, 0x400000, CRC(1053a455) SHA1(69501bfac68739e63d798045b812badd251d57b8) )
	ROM_LOAD16_BYTE( "069.c3", 0x0800000, 0x400000, CRC(1c0fde2f) SHA1(cf6c2ef56c03a861de3b0b6dc0d7c9204d947f9d) )
	ROM_LOAD16_BYTE( "069.c4", 0x0800001, 0x400000, CRC(a25fc3d0) SHA1(83cb349e2f1032652060b233e741fb893be5af16) )
	ROM_LOAD16_BYTE( "095.c5", 0x1000000, 0x400000, CRC(8b9b65df) SHA1(e2a7e20855501f240bcd22f5cc92fcb4a9806abe) )
	ROM_LOAD16_BYTE( "095.c6", 0x1000001, 0x400000, CRC(3e164718) SHA1(53217f938c8964c1ca68a6fd5249c4169a5ac8e6) )
	ROM_LOAD16_BYTE( "095.c7", 0x1800000, 0x200000, CRC(ca605e12) SHA1(5150b835247fd705bc1dece97d423d9c20a51416) )
	ROM_LOAD16_BYTE( "095.c8", 0x1800001, 0x200000, CRC(4e6beb6c) SHA1(c0ac7cfc832ace6ad52c58f5da3a8101baead749) )
ROM_END

ROM_START( rbff1a ) /* MVS VERSION */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "095.p1",  0x000000, 0x100000, CRC(63b4d8ae) SHA1(03aa9f6bab6aee685d1b57a52823797704eea845) )
	ROM_LOAD16_WORD_SWAP( "095.p2", 0x100000, 0x200000, CRC(cc15826e) SHA1(44d6ac6c0ca697a6f367dcfd809b1e1771cb0635) )
	/* the rom below acts as a patch to the program rom in the cart, replacing the first 512kb */
	ROM_LOAD16_WORD_SWAP( "095a.p1", 0x000000, 0x080000, CRC(be0060a3) SHA1(fa741d34898ad5004a23e280139d1446f1a082c7) )

	NEO_SFIX_128K( "095.s1", CRC(b6bf5e08) SHA1(b527355c35ea097f3448676f2ffa65b8e56ae30c) )

	NEO_BIOS_AUDIO_128K( "095.m1", CRC(653492a7) SHA1(39e511fb9ed5d2135dc8428a31d0baafb2ab36e0) )

	ROM_REGION( 0xc00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "069.v1", 0x000000, 0x400000, CRC(2bdbd4db) SHA1(5f4fecf69c2329d699cbd45829c19303b1e2a80e) )
	ROM_LOAD( "069.v2", 0x400000, 0x400000, CRC(a698a487) SHA1(11b8bc53bc26a51f4a408e900e3769958625c4ed) )
	ROM_LOAD( "095.v3", 0x800000, 0x400000, CRC(189d1c6c) SHA1(f0b8cd1ee40ea3feeb2800f0723b451ec8240203) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "069.c1", 0x0000000, 0x400000, CRC(e302f93c) SHA1(d8610b14900b2b8fe691b67ca9b1abb335dbff74) )
	ROM_LOAD16_BYTE( "069.c2", 0x0000001, 0x400000, CRC(1053a455) SHA1(69501bfac68739e63d798045b812badd251d57b8) )
	ROM_LOAD16_BYTE( "069.c3", 0x0800000, 0x400000, CRC(1c0fde2f) SHA1(cf6c2ef56c03a861de3b0b6dc0d7c9204d947f9d) )
	ROM_LOAD16_BYTE( "069.c4", 0x0800001, 0x400000, CRC(a25fc3d0) SHA1(83cb349e2f1032652060b233e741fb893be5af16) )
	ROM_LOAD16_BYTE( "095.c5", 0x1000000, 0x400000, CRC(8b9b65df) SHA1(e2a7e20855501f240bcd22f5cc92fcb4a9806abe) )
	ROM_LOAD16_BYTE( "095.c6", 0x1000001, 0x400000, CRC(3e164718) SHA1(53217f938c8964c1ca68a6fd5249c4169a5ac8e6) )
	ROM_LOAD16_BYTE( "095.c7", 0x1800000, 0x200000, CRC(ca605e12) SHA1(5150b835247fd705bc1dece97d423d9c20a51416) )
	ROM_LOAD16_BYTE( "095.c8", 0x1800001, 0x200000, CRC(4e6beb6c) SHA1(c0ac7cfc832ace6ad52c58f5da3a8101baead749) )
ROM_END

/****************************************
 ID-0096
 . NGM-096
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . NGH-096
****************************************/

ROM_START( aof3 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "096.p1",  0x000000, 0x100000, CRC(9edb420d) SHA1(150d80707325ece351c72c21c6186cfb5996adba) )
	ROM_LOAD16_WORD_SWAP( "096.p2", 0x100000, 0x200000, CRC(4d5a2602) SHA1(4c26d6135d2877d9c38169662033e9d0cc24d943) )

	NEO_SFIX_128K( "096.s1", CRC(cc7fd344) SHA1(2c6846cf8ea61fb192ba181dbccb63594d572c0e) )

	NEO_BIOS_AUDIO_128K( "096.m1", CRC(cb07b659) SHA1(940b379957c2987d7ab0443cb80c3ff58f6ba559) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "096.v1", 0x000000, 0x200000, CRC(e2c32074) SHA1(69426e7e63fc31a73d1cd056cc9ae6a2c4499407) )
	ROM_LOAD( "096.v2", 0x200000, 0x200000, CRC(a290eee7) SHA1(e66a98cd9740188bf999992b417f8feef941cede) )
	ROM_LOAD( "096.v3", 0x400000, 0x200000, CRC(199d12ea) SHA1(a883bf34e685487705a8dafdd0b8db15eb360e80) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "096.c1", 0x0000000, 0x400000, CRC(f17b8d89) SHA1(7180df23f7c7a964b0835fda76970b12f0aa9ea8) )
	ROM_LOAD16_BYTE( "096.c2", 0x0000001, 0x400000, CRC(3840c508) SHA1(55adc7cd26fec3e4dbd779df6701bc6eaba41b84) )
	ROM_LOAD16_BYTE( "096.c3", 0x0800000, 0x400000, CRC(55f9ee1e) SHA1(fbe1b7891beae66c5fcbc7e36168dc1b460ede91) )
	ROM_LOAD16_BYTE( "096.c4", 0x0800001, 0x400000, CRC(585b7e47) SHA1(d50ea91397fc53d86470ff5b493a44d57c010306) )
	ROM_LOAD16_BYTE( "096.c5", 0x1000000, 0x400000, CRC(c75a753c) SHA1(fc977f8710816a369a5d0d49ee84059380e93fb7) )
	ROM_LOAD16_BYTE( "096.c6", 0x1000001, 0x400000, CRC(9a9d2f7a) SHA1(a89a713bfcd93974c9acb21ce699d365b08e7e39) )
	ROM_LOAD16_BYTE( "096.c7", 0x1800000, 0x200000, CRC(51bd8ab2) SHA1(c8def9c64de64571492b5b7e14b794e3c18f1393) )
	ROM_LOAD16_BYTE( "096.c8", 0x1800001, 0x200000, CRC(9a34f99c) SHA1(fca72d95ec42790a7f1e771a1e25dbc5bec5fc19) )
ROM_END

ROM_START( aof3k ) /* KOREAN VERSION */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "196.p1", 0x000000, 0x100000, CRC(a0780789) SHA1(83657922a9a3502653ef8cda45b15d9f935aa96a) )
	ROM_LOAD16_WORD_SWAP( "096.p2", 0x100000, 0x200000, CRC(4d5a2602) SHA1(4c26d6135d2877d9c38169662033e9d0cc24d943) )

	NEO_SFIX_128K( "096.s1", CRC(cc7fd344) SHA1(2c6846cf8ea61fb192ba181dbccb63594d572c0e) )

	NEO_BIOS_AUDIO_128K( "096.m1", CRC(cb07b659) SHA1(940b379957c2987d7ab0443cb80c3ff58f6ba559) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "096.v1", 0x000000, 0x200000, CRC(e2c32074) SHA1(69426e7e63fc31a73d1cd056cc9ae6a2c4499407) )
	ROM_LOAD( "096.v2", 0x200000, 0x200000, CRC(a290eee7) SHA1(e66a98cd9740188bf999992b417f8feef941cede) )
	ROM_LOAD( "096.v3", 0x400000, 0x200000, CRC(199d12ea) SHA1(a883bf34e685487705a8dafdd0b8db15eb360e80) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "096.c1", 0x0000000, 0x400000, CRC(f17b8d89) SHA1(7180df23f7c7a964b0835fda76970b12f0aa9ea8) )
	ROM_LOAD16_BYTE( "096.c2", 0x0000001, 0x400000, CRC(3840c508) SHA1(55adc7cd26fec3e4dbd779df6701bc6eaba41b84) )
	ROM_LOAD16_BYTE( "096.c3", 0x0800000, 0x400000, CRC(55f9ee1e) SHA1(fbe1b7891beae66c5fcbc7e36168dc1b460ede91) )
	ROM_LOAD16_BYTE( "096.c4", 0x0800001, 0x400000, CRC(585b7e47) SHA1(d50ea91397fc53d86470ff5b493a44d57c010306) )
	ROM_LOAD16_BYTE( "096.c5", 0x1000000, 0x400000, CRC(c75a753c) SHA1(fc977f8710816a369a5d0d49ee84059380e93fb7) )
	ROM_LOAD16_BYTE( "096.c6", 0x1000001, 0x400000, CRC(9a9d2f7a) SHA1(a89a713bfcd93974c9acb21ce699d365b08e7e39) )
	ROM_LOAD16_BYTE( "096.c7", 0x1800000, 0x200000, CRC(51bd8ab2) SHA1(c8def9c64de64571492b5b7e14b794e3c18f1393) )
	ROM_LOAD16_BYTE( "096.c8", 0x1800001, 0x200000, CRC(9a34f99c) SHA1(fca72d95ec42790a7f1e771a1e25dbc5bec5fc19) )
ROM_END

/****************************************
 ID-0097
 . NGM-097
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . NGH-097
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( sonicwi3 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "097.p1", 0x100000, 0x100000, CRC(0547121d) SHA1(e0bb6c614f572b74ba9a9f0d3d5b69fbc91ebc52) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "097.s1", CRC(8dd66743) SHA1(39214bb25a1d5b44a8524010be05bf5a0211981f) )

	NEO_BIOS_AUDIO_128K( "097.m1", CRC(b20e4291) SHA1(0e891ab53f9fded510295dfc7818bc59b4a9dd97) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "097.v1", 0x000000, 0x400000, CRC(6f885152) SHA1(8175804d5c1420c5d37b733d4a8fa2aa81e59f1b) )
	ROM_LOAD( "097.v2", 0x400000, 0x200000, CRC(3359e868) SHA1(b7efd9f1a6dab33271fe8356bcc863aeae1d3ed8) )

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "097.c1", 0x000000, 0x400000, CRC(33d0d589) SHA1(fe4aa95555e478ceb2d28fd27d83ee06cd09520c) )
	ROM_LOAD16_BYTE( "097.c2", 0x000001, 0x400000, CRC(186f8b43) SHA1(f5cced93e21dc841b00ebeaa30786cb0e047bd9a) )
	ROM_LOAD16_BYTE( "097.c3", 0x800000, 0x200000, CRC(c339fff5) SHA1(58dfd1e30dc0ad3f816a5dbd1cc7e7ccbb792c53) )
	ROM_LOAD16_BYTE( "097.c4", 0x800001, 0x200000, CRC(84a40c6e) SHA1(061a13fba5fed883e5ee9566cedc208df2511bcf) )
ROM_END

/****************************************
 ID-0098
 Idol Mahjong - final romance 2 (CD only? not confirmed, MVS might exist)
****************************************/

/****************************************
 ID-0099
 Neo Pool Masters
****************************************/


/* ID range from 100 - 199 is used for Korean (some) and Neo Print carts */

/*
    The following ID's are used by Korean releases:

    ID-0122 - Pae Wang Jeon Seol / Legend of a Warrior (Korean censored Samurai Shodown IV)
    ID-0123 - Quiz Daisousa Sen - The Last Count Down (Korean release)
    ID-0124 - Real Bout Fatal Fury Special / Real Bout Garou Densetsu Special (Korean release)
    ID-0134 - The Last Soldier (Korean release of The Last Blade)
    ID-0140 - Real Bout Fatal Fury 2 - The Newcomers (Korean release)
    ID-0152 - The King of Fighters '99 - Millennium Battle (Korean release)
    ID-0163 - Saulabi Spirits / Jin Saulabi Tu Hon (Korean release of Samurai Shodown II)
    ID-0187 - Fighters Swords (Korean release of Samurai Shodown III)
    ID-0196 - Art of Fighting 3 - The Path of the Warrior (Korean release)
*/


/****************************************
 ID-0200
 . NGM-200
 NEO-MVS PROGBK1 / NEO-MVS CHA256B
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . NGH-200
****************************************/

ROM_START( turfmast )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "200.p1", 0x100000, 0x100000, CRC(28c83048) SHA1(e7ef87e1de21d2bb17ef17bb08657e92363f0e9a) )
	ROM_CONTINUE( 0x000000, 0x100000)

	NEO_SFIX_128K( "200.s1", CRC(9a5402b2) SHA1(ae1a0b5450869d61b2bb23671c744d3dda8769c4) )

	NEO_BIOS_AUDIO_128K( "200.m1", CRC(9994ac00) SHA1(7bded797f3b80fd00bcbe451ac0abe6646b19a14) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "200.v1", 0x000000, 0x200000, CRC(00fd48d2) SHA1(ddfee09328632e598fd51537b3ae8593219b2111) )
	ROM_LOAD( "200.v2", 0x200000, 0x200000, CRC(082acb31) SHA1(2f1c053040e9d50a6d45fd7bea1b96742bae694f) )
	ROM_LOAD( "200.v3", 0x400000, 0x200000, CRC(7abca053) SHA1(e229bc0ea82a371d6ee8fd9fe442b0fd141d0a71) )
	ROM_LOAD( "200.v4", 0x600000, 0x200000, CRC(6c7b4902) SHA1(d55e0f542d928a9a851133ff26763c8236cbbd4d) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "200.c1", 0x000000, 0x400000, CRC(8e7bf41a) SHA1(148eb747f2f4d8e921eb0411c88a636022ceab80) )
	ROM_LOAD16_BYTE( "200.c2", 0x000001, 0x400000, CRC(5a65a8ce) SHA1(d6c7afe035411f3eacdf6868d36f91572dd593e0) )
ROM_END

/****************************************
 ID-0201
 . NGM-201
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 NEO-MVS PROGBK1 / NEO-MVS CHA256B
 . NGH-201
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( mslug )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201.p1", 0x100000, 0x100000, CRC(08d8daa5) SHA1(b888993dbb7e9f0a28a01d7d2e1da00ef9cf6f38) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "201.s1", CRC(2f55958d) SHA1(550b53628daec9f1e1e11a398854092d90f9505a) )

	NEO_BIOS_AUDIO_128K( "201.m1", CRC(c28b3253) SHA1(fd75bd15aed30266a8b3775f276f997af57d1c06) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "201.v1", 0x000000, 0x400000, CRC(23d22ed1) SHA1(cd076928468ad6bcc5f19f88cb843ecb5e660681) )
	ROM_LOAD( "201.v2", 0x400000, 0x400000, CRC(472cf9db) SHA1(5f79ea9286d22ed208128f9c31ca75552ce08b57) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "201.c1", 0x000000, 0x400000, CRC(72813676) SHA1(7b045d1a48980cb1a140699011cb1a3d4acdc4d1) )
	ROM_LOAD16_BYTE( "201.c2", 0x000001, 0x400000, CRC(96f62574) SHA1(cb7254b885989223bba597b8ff0972dfa5957816) )
	ROM_LOAD16_BYTE( "201.c3", 0x800000, 0x400000, CRC(5121456a) SHA1(0a7a27d603d1bb2520b5570ebf5b34a106e255a6) )
	ROM_LOAD16_BYTE( "201.c4", 0x800001, 0x400000, CRC(f4ad59a3) SHA1(4e94fda8ee63abf0f92afe08060a488546e5c280) )
ROM_END

/****************************************
 ID-0202
 . ??M-202
 NEO-MVS PROG 4096 / NEO-MVS CHA 42G-2
****************************************/

ROM_START( puzzledp ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "202.p1", 0x000000, 0x080000, CRC(2b61415b) SHA1(0e3e4faf2fd6e63407425e1ac788003e75aeeb4f) )

	NEO_SFIX_128K( "202.s1", CRC(cd19264f) SHA1(531be2305cd56d332fb7a53ab924214ade34a9e8) )

	NEO_BIOS_AUDIO_128K( "202.m1", CRC(9c0291ea) SHA1(3fa67c62acba79be6b3a98cc1601e45569fa11ae) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "202.v1", 0x000000, 0x080000, CRC(debeb8fb) SHA1(49a3d3578c087f1a0050168571ef8d1b08c5dc05) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "202.c1", 0x000000, 0x100000, CRC(cc0095ef) SHA1(3d86f455e6db10a2449b775dc386f1826ba3b62e) )
	ROM_LOAD16_BYTE( "202.c2", 0x000001, 0x100000, CRC(42371307) SHA1(df794f989e2883634bf7ffeea48d6bc3854529af) )
ROM_END

/****************************************
 ID-0203
 . ADM-010
 NEO-MVS PROGTOP / NEO-MVS CHA42G-3B
 . ADH-010
****************************************/

ROM_START( mosyougi )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "203.p1", 0x000000, 0x100000, CRC(7ba70e2d) SHA1(945f472cc3e7706f613c52df18de35c986d166e7) )

	NEO_SFIX_128K( "203.s1", CRC(bfdc8309) SHA1(781337eab932a130b396a6c1080611d6f9c24c6e) )

	NEO_BIOS_AUDIO_128K( "203.m1", CRC(a602c2c2) SHA1(19fd5d0379244c528b58343f6cbf78b4766fb23d) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "203.v1", 0x000000, 0x200000, CRC(baa2b9a5) SHA1(914782b6c81d9a76ce02251575592b0648434ba3) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "203.c1", 0x000000, 0x200000, CRC(bba9e8c0) SHA1(db89b7275a59ae6104a8308025c7e142a67b947b) )
	ROM_LOAD16_BYTE( "203.c2", 0x000001, 0x200000, CRC(2574be03) SHA1(198cfd697c623022919ae4118928a7fe30cd6c46) )
ROM_END

/****************************************
 ID-0204
 QP (prototype) 1997 Success
****************************************/

/****************************************
 ID-0205
 Neo-Geo CD Special (CD only)
****************************************/

/****************************************
 ID-0206
 . ??M-206
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . ??H-206
****************************************/

ROM_START( marukodq )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "206.p1", 0x000000, 0x100000, CRC(c33ed21e) SHA1(bffff0d17e587e67672227e60c0ebd3f3a7193e6) )

	NEO_SFIX_128K( "206.s1", CRC(f0b68780) SHA1(3f60950b14d121a5af3e6a8155ae9832ddc6ec46) )

	NEO_BIOS_AUDIO_128K( "206.m1", CRC(0e22902e) SHA1(fb8466c342d4abd8bb4cad01c6ceab03f96cdad8) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "206.v1", 0x000000, 0x200000, CRC(5385eca8) SHA1(1ca171ce74a5885ae8841d0924de21dc0af2214e) )
	ROM_LOAD( "206.v2", 0x200000, 0x200000, CRC(f8c55404) SHA1(cecc41e9e08a7ff05b6f62e713fc86a816bf55a2) )

	ROM_REGION( 0xa00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "206.c1", 0x000000, 0x400000, CRC(846e4e8e) SHA1(ba9b96340aca7fadaff0e6d484391ddb5c5e7bd4) )
	ROM_LOAD16_BYTE( "206.c2", 0x000001, 0x400000, CRC(1cba876d) SHA1(3254ceb5a2f76c172930d9889d5d81e093e87628) )
	ROM_LOAD16_BYTE( "206.c3", 0x800000, 0x100000, CRC(79aa2b48) SHA1(31f94217cd35f48845c74a55256314c16fd26ed7) )
	ROM_LOAD16_BYTE( "206.c4", 0x800001, 0x100000, CRC(55e1314d) SHA1(fffbc9eb9000ff5b1063af1817de7ea4a267fedd) )
ROM_END

/****************************************
 ID-0207
 . ??M-207
 NEO-MVS PROGBK1 / NEO-MVS CHA42G-3B
 NEO-MVS PROG 4096 / NEO-MVS CHA42G-3B
****************************************/

ROM_START( neomrdo ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "207.p1", 0x000000, 0x100000, CRC(334ea51e) SHA1(0a642f8565ec6e9587ed767bcf177f4677547162) )

	NEO_SFIX_128K( "207.s1", CRC(6aebafce) SHA1(5db03715fbed62f2ff3cef7f93606f30261c0362) )

	NEO_BIOS_AUDIO_128K( "207.m1", CRC(b5b74a95) SHA1(7b01f3b87c247cc7472591f8cdcf0ae8065e31c6) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "207.v1", 0x000000, 0x200000, CRC(4143c052) SHA1(561b19bc8811b80f2f42ffc0b5df27132696470a) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "207.c1", 0x000000, 0x200000, CRC(c7541b9d) SHA1(25ca1a2b14cc2648d8dbe432cbd1396017af822c) )
	ROM_LOAD16_BYTE( "207.c2", 0x000001, 0x200000, CRC(f57166d2) SHA1(bf3aa47d17156485c2177fb63cba093f050abb98) )
ROM_END

/****************************************
 ID-0208
 . ??M-208
 NEO-MVS PROGBK1 / NEO-MVS CHA256B
****************************************/

ROM_START( sdodgeb ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "208.p1", 0x100000, 0x100000, CRC(127f3d32) SHA1(18e77b79b1197a89371533ef9b1e4d682c44d875) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "208.s1", CRC(64abd6b3) SHA1(0315d724e4d83a44ce84c531ff9b8c398363c039) )

	NEO_BIOS_AUDIO_128K( "208.m1", CRC(0a5f3325) SHA1(04e0236df478a5452654c823dcb42fea65b6a718) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "208.v1", 0x000000, 0x400000, CRC(e7899a24) SHA1(3e75b449898fee73fbacf58d70e3a460b9e0c573) )

	ROM_REGION( 0x0c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "208.c1", 0x0000000, 0x400000, CRC(93d8619b) SHA1(6588cb67e38722d5843fb29943d92e3905101aff) )
	ROM_LOAD16_BYTE( "208.c2", 0x0000001, 0x400000, CRC(1c737bb6) SHA1(8e341989981a713e61dfed8bde9a6459583ef46d) )
	ROM_LOAD16_BYTE( "208.c3", 0x0800000, 0x200000, CRC(14cb1703) SHA1(a46acec03c1b2351fe36810628f02b7c848d13db) )
	ROM_LOAD16_BYTE( "208.c4", 0x0800001, 0x200000, CRC(c7165f19) SHA1(221f03de893dca0e5305fa17aa94f96c67713818) )
ROM_END

/****************************************
 ID-0209
 . ??M-209
 NEO-MVS PROGBK1 / NEO-MVS CHA256
****************************************/

ROM_START( goalx3 ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "209.p1", 0x100000, 0x100000, CRC(2a019a79) SHA1(422a639e74284fef2e53e1b49cf8803b0a7e80c6) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "209.s1", CRC(c0eaad86) SHA1(99412093c9707d51817893971e73fb8469cdc9d0) )

	NEO_BIOS_AUDIO_128K( "209.m1", CRC(cd758325) SHA1(b51eac634fc646c07210dff993018ad9ebabd3f9) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "209.v1", 0x000000, 0x200000, CRC(ef214212) SHA1(3e05ccaa2d06decb18b379b96f900c0e6b39ce70) )

	ROM_REGION( 0xa00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "209.c1", 0x000000, 0x400000, CRC(b49d980e) SHA1(722d10074f16fa7f14c71270f43fdab427b85e2b) )
	ROM_LOAD16_BYTE( "209.c2", 0x000001, 0x400000, CRC(5649b015) SHA1(9c9674f3841e6becd3b8e63bae9b9df45ac9f11e) )
	ROM_LOAD16_BYTE( "209.c3", 0x800000, 0x100000, CRC(5f91bace) SHA1(3864be27dce6d8f8828d3bf09bfc8116116a2b56) )
	ROM_LOAD16_BYTE( "209.c4", 0x800001, 0x100000, CRC(1e9f76f2) SHA1(b57fdc226bfe328b8848127fb4292295f1287bf6) )
ROM_END

/****************************************
 ID-0210
 Karate Ninja Sho (prototype) 1995 Yumekobo
****************************************/

/****************************************
 ID-0211
 Oshidashi Zintrick (CD only? not confirmed, MVS might exist) 1996 SNK/ADK
****************************************/

/****************************************
 ID-0212
 . ADM-011
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . ADH-011
****************************************/

ROM_START( overtop )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "212.p1", 0x100000, 0x100000, CRC(16c063a9) SHA1(5432869f830eed816ee5ed71c7fd39f749d15619) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "212.s1", CRC(481d3ddc) SHA1(7b0df3fc5b19f282abfd0eb5a4c6ed836a536ece) )

	NEO_BIOS_AUDIO_128K( "212.m1", CRC(fcab6191) SHA1(488b8310b0957f0012fe50f73641b606f6ac4a57) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "212.v1", 0x000000, 0x400000, CRC(013d4ef9) SHA1(438a697c44525bdf78b54432c4f7217ab5667047) )

	ROM_REGION( 0x1400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "212.c1", 0x0000000, 0x400000, CRC(50f43087) SHA1(e5a8c914ef8e77c7a29bffdeb18f1877b5c2fc7d) )
	ROM_LOAD16_BYTE( "212.c2", 0x0000001, 0x400000, CRC(a5b39807) SHA1(e98e82cf99576cb48cc5e8dc655b7e9a428c2843) )
	ROM_LOAD16_BYTE( "212.c3", 0x0800000, 0x400000, CRC(9252ea02) SHA1(269066e0f893d3e8e7c308528026a486c2b023a2) )
	ROM_LOAD16_BYTE( "212.c4", 0x0800001, 0x400000, CRC(5f41a699) SHA1(abbb162658e06a37db8475b659ece7e1270ebb49) )
	ROM_LOAD16_BYTE( "212.c5", 0x1000000, 0x200000, CRC(fc858bef) SHA1(0031def13e7cf4a465a1eca7aa0d13d1b21427e2) )
	ROM_LOAD16_BYTE( "212.c6", 0x1000001, 0x200000, CRC(0589c15e) SHA1(b1167caf7cb61f3e05a5d342290bfe00e02e9d38) )
ROM_END

/****************************************
 ID-0213
 . ??M-213
 NEO-MVS PROGBK1 / NEO-MVS CHA256B
****************************************/

ROM_START( neodrift ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "213.p1", 0x100000, 0x100000, CRC(e397d798) SHA1(10f459111db4bab7aaa63ca47e83304a84300812) )
	ROM_CONTINUE( 0x000000, 0x100000)

	NEO_SFIX_128K( "213.s1", CRC(b76b61bc) SHA1(5fdb407d16ab9e33c4f26ee09ff70891ae1d2bd0) )

	NEO_BIOS_AUDIO_128K( "213.m1", CRC(200045f1) SHA1(7a6cd1c8d4447ea260d7ff4520c676b8d685f2e4) ) /* mask rom TC531001*/

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "213.v1", 0x000000, 0x200000, CRC(a421c076) SHA1(129f05c1a28a6493442f47a79c2d3577a1a43ef5) )
	ROM_LOAD( "213.v2", 0x200000, 0x200000, CRC(233c7dd9) SHA1(be7f980aa83831b6605aaaf4ec904180bb96c935) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "213.c1", 0x000000, 0x400000, CRC(3edc8bd3) SHA1(71dcba9afd3b08ebfa13294644dcb365c2740780) )
	ROM_LOAD16_BYTE( "213.c2", 0x000001, 0x400000, CRC(46ae5f16) SHA1(a01310632734e776e889af6a531063cb1661c33a) )
ROM_END

/****************************************
 ID-0214
 . NGM-214
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 NEO-MVS PROGSS3 / NEO-MVS CHA256
 . NGH-214
 NEO-AEG PROGBK1Y / NEO-GEO AEG CHA256RY
****************************************/

ROM_START( kof96 ) /* MVS VERSION */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "214.p1",  0x000000, 0x100000, CRC(52755d74) SHA1(4232d627f1d2e6ea9fc8cf01571d77d4d5b8a1bb) )
	ROM_LOAD16_WORD_SWAP( "214.p2", 0x100000, 0x200000, CRC(002ccb73) SHA1(3ae8df682c75027ca82db25491021eeba00a267e) )

	NEO_SFIX_128K( "214.s1", CRC(1254cbdb) SHA1(fce5cf42588298711a3633e9c9c1d4dcb723ac76) )

	NEO_BIOS_AUDIO_128K( "214.m1", CRC(dabc427c) SHA1(b76722ed142ee7addceb4757424870dbd003e8b3) )

	ROM_REGION( 0xa00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "214.v1", 0x000000, 0x400000, CRC(63f7b045) SHA1(1353715f1a8476dca6f8031d9e7a401eacab8159) )
	ROM_LOAD( "214.v2", 0x400000, 0x400000, CRC(25929059) SHA1(6a721c4cb8f8dc772774023877d4a9f50d5a9e31) )
	ROM_LOAD( "214.v3", 0x800000, 0x200000, CRC(92a2257d) SHA1(5064aec78fa0d104e5dd5869b95382aa170214ee) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "214.c1", 0x0000000, 0x400000, CRC(7ecf4aa2) SHA1(f773c4c1f05d58dd37e7bb2ac1d1e0ec43998a71) )
	ROM_LOAD16_BYTE( "214.c2", 0x0000001, 0x400000, CRC(05b54f37) SHA1(cc31653fe4cb05201fba234e080cb9c7a7592b1b) )
	ROM_LOAD16_BYTE( "214.c3", 0x0800000, 0x400000, CRC(64989a65) SHA1(e6f3749d43be0afa9dad7b085cb782ba694252ca) )
	ROM_LOAD16_BYTE( "214.c4", 0x0800001, 0x400000, CRC(afbea515) SHA1(ae875052728de33174827705646bd14cf3937b5c) )
	ROM_LOAD16_BYTE( "214.c5", 0x1000000, 0x400000, CRC(2a3bbd26) SHA1(7c1a7e50a10a1b082e0d0d515c34135ee9f995ac) )
	ROM_LOAD16_BYTE( "214.c6", 0x1000001, 0x400000, CRC(44d30dc7) SHA1(c8ae001e37224b55d9e4a4d99f6578b4f6eb055f) )
	ROM_LOAD16_BYTE( "214.c7", 0x1800000, 0x400000, CRC(3687331b) SHA1(2be95caab76d7af51674f93884330ba73a6053e4) )
	ROM_LOAD16_BYTE( "214.c8", 0x1800001, 0x400000, CRC(fa1461ad) SHA1(6c71a7f08e4044214223a6bf80984582ab5e0328) )
ROM_END

ROM_START( kof96h ) /* AES VERSION */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "214.p1", 0x000000, 0x100000, CRC(bd3757c9) SHA1(35392a044117e46c088ff0fdd07d69a3faa4f96e) )
	ROM_LOAD16_WORD_SWAP( "214.p2", 0x100000, 0x200000, CRC(002ccb73) SHA1(3ae8df682c75027ca82db25491021eeba00a267e) )

	NEO_SFIX_128K( "214.s1", CRC(1254cbdb) SHA1(fce5cf42588298711a3633e9c9c1d4dcb723ac76) )

	NEO_BIOS_AUDIO_128K( "214.m1", CRC(dabc427c) SHA1(b76722ed142ee7addceb4757424870dbd003e8b3) )

	ROM_REGION( 0xa00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "214.v1", 0x000000, 0x400000, CRC(63f7b045) SHA1(1353715f1a8476dca6f8031d9e7a401eacab8159) )
	ROM_LOAD( "214.v2", 0x400000, 0x400000, CRC(25929059) SHA1(6a721c4cb8f8dc772774023877d4a9f50d5a9e31) )
	ROM_LOAD( "214.v3", 0x800000, 0x200000, CRC(92a2257d) SHA1(5064aec78fa0d104e5dd5869b95382aa170214ee) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "214.c1", 0x0000000, 0x400000, CRC(7ecf4aa2) SHA1(f773c4c1f05d58dd37e7bb2ac1d1e0ec43998a71) )
	ROM_LOAD16_BYTE( "214.c2", 0x0000001, 0x400000, CRC(05b54f37) SHA1(cc31653fe4cb05201fba234e080cb9c7a7592b1b) )
	ROM_LOAD16_BYTE( "214.c3", 0x0800000, 0x400000, CRC(64989a65) SHA1(e6f3749d43be0afa9dad7b085cb782ba694252ca) )
	ROM_LOAD16_BYTE( "214.c4", 0x0800001, 0x400000, CRC(afbea515) SHA1(ae875052728de33174827705646bd14cf3937b5c) )
	ROM_LOAD16_BYTE( "214.c5", 0x1000000, 0x400000, CRC(2a3bbd26) SHA1(7c1a7e50a10a1b082e0d0d515c34135ee9f995ac) )
	ROM_LOAD16_BYTE( "214.c6", 0x1000001, 0x400000, CRC(44d30dc7) SHA1(c8ae001e37224b55d9e4a4d99f6578b4f6eb055f) )
	ROM_LOAD16_BYTE( "214.c7", 0x1800000, 0x400000, CRC(3687331b) SHA1(2be95caab76d7af51674f93884330ba73a6053e4) )
	ROM_LOAD16_BYTE( "214.c8", 0x1800001, 0x400000, CRC(fa1461ad) SHA1(6c71a7f08e4044214223a6bf80984582ab5e0328) )
ROM_END

/****************************************
 ID-0215
 . NGM-215
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . NGH-215
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( ssideki4 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "215.p1", 0x100000, 0x100000, CRC(519b4ba3) SHA1(5aa59514b23aa663f2c4014ee94a31e9f59151de) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "215.s1", CRC(f0fe5c36) SHA1(b7badd6d2ac3788ce5cace1fcf5cdad14734e4e6) )

	NEO_BIOS_AUDIO_128K( "215.m1", CRC(a932081d) SHA1(376a45e19edb780ac8798c41ae2260c8a8a4bba8) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "215.v1", 0x000000, 0x400000, CRC(877d1409) SHA1(77c58ebffe677ea6369c964ec7975b11df512fa1) )
	ROM_LOAD( "215.v2", 0x400000, 0x200000, CRC(1bfa218b) SHA1(344836a578bde3c0ab59b58c8734f868e7403c26) )

	ROM_REGION( 0x1400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "215.c1", 0x0000000, 0x400000, CRC(8ff444f5) SHA1(e2dc52d09512cb378df96ddf45435f9bcbbe9947) )
	ROM_LOAD16_BYTE( "215.c2", 0x0000001, 0x400000, CRC(5b155037) SHA1(68900c0fdcd35c9f38e0effdf27e1dbd3c53daf8) )
	ROM_LOAD16_BYTE( "215.c3", 0x0800000, 0x400000, CRC(456a073a) SHA1(3488013f371012eab4e788e1525c81260e0b7080) )
	ROM_LOAD16_BYTE( "215.c4", 0x0800001, 0x400000, CRC(43c182e1) SHA1(343f034c65ca498b437e22e06a866a5daf3b9602) )
	ROM_LOAD16_BYTE( "215.c5", 0x1000000, 0x200000, CRC(0c6f97ec) SHA1(b8d297f0ba2b04404eb0f7c6673ecc206fadae0c) )
	ROM_LOAD16_BYTE( "215.c6", 0x1000001, 0x200000, CRC(329c5e1b) SHA1(015c36b8d3efab9b4647f110ecb5c118a9c80f43) )
ROM_END

/****************************************
 ID-0216
 . ??M-216
 NEO-MVS PROGTOP / NEO-MVS CHA256
 . ??H-216
 NEO-AEG PROGTOP2Y / NEO-AEG CHA256BY
 NEO-AEG PROGTOP2Y / NEO-AEG CHA256[B]
****************************************/

ROM_START( kizuna )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "216.p1", 0x100000, 0x100000, CRC(75d2b3de) SHA1(ee778656c26828935ee2a2bfd0ce5a22aa681c10) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "216.s1", CRC(efdc72d7) SHA1(be37cbf1852e2e4c907cc799b754b538544b6703) )

	NEO_BIOS_AUDIO_128K( "216.m1", CRC(1b096820) SHA1(72852e78c620038f8dafde5e54e02e418c31be9c) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "059.v1", 0x000000, 0x200000, CRC(530c50fd) SHA1(29401cee7f7d2c199c7cb58092e86b28205e81ad) )
	ROM_LOAD( "216.v2", 0x200000, 0x200000, CRC(03667a8d) SHA1(3b0475e553a49f8788f32b0c84f82645cc6b4273) )
	ROM_LOAD( "059.v3", 0x400000, 0x200000, CRC(7038c2f9) SHA1(c1d6f86b24feba03fe009b58199d2eeabe572f4e) )
	ROM_LOAD( "216.v4", 0x600000, 0x200000, CRC(31b99bd6) SHA1(5871751f8e9e6b98337472c22b5e1c7ede0a9311) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "059.c1", 0x0000000, 0x200000, CRC(763ba611) SHA1(d3262e0332c894ee149c5963f882cc5e5562ee57) )
	ROM_LOAD16_BYTE( "059.c2", 0x0000001, 0x200000, CRC(e05e8ca6) SHA1(986a9b16ff92bc101ab567d2d01348e093abea9a) )
	ROM_LOAD16_BYTE( "216.c3", 0x0800000, 0x400000, CRC(665c9f16) SHA1(7ec781a49a462f395b450460b29493f55134eac2) )
	ROM_LOAD16_BYTE( "216.c4", 0x0800001, 0x400000, CRC(7f5d03db) SHA1(365ed266c121f4df0bb76898955a8ae0e668a216) )
	ROM_LOAD16_BYTE( "059.c5", 0x1000000, 0x200000, CRC(59013f9e) SHA1(5bf48fcc450da72a8c4685f6e3887e67eae49988) )
	ROM_LOAD16_BYTE( "059.c6", 0x1000001, 0x200000, CRC(1c8d5def) SHA1(475d89a5c4922a9f6bd756d23c2624d57b6e9d62) )
	ROM_LOAD16_BYTE( "059.c7", 0x1800000, 0x200000, CRC(c88f7035) SHA1(c29a428b741f4fe7b71a3bc23c87925b6bc1ca8f) )
	ROM_LOAD16_BYTE( "059.c8", 0x1800001, 0x200000, CRC(484ce3ba) SHA1(4f21ed20ce6e2b67e2b079404599310c94f591ff) )
ROM_END


ROM_START( kizuna4p ) /* same cartridge as kizuna - 4-player mode is enabled by an extension board that plugs into a compatible MVS */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "216.p1", 0x100000, 0x100000, CRC(75d2b3de) SHA1(ee778656c26828935ee2a2bfd0ce5a22aa681c10) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "216.s1", CRC(efdc72d7) SHA1(be37cbf1852e2e4c907cc799b754b538544b6703) )

	ROM_REGION16_BE( 0x80000, "mainbios", 0 )
	/* these two BIOSes are the only ones we have that are compatible with the 4-player extension board */
	ROM_SYSTEM_BIOS( 0, "asia",        "NEO-MVH MV1C" )
	ROM_LOAD16_WORD_SWAP_BIOS( 0, "sp-45.sp1",0x00000, 0x080000, CRC(03cc9f6a) SHA1(cdf1f49e3ff2bac528c21ed28449cf35b7957dc1) )
	ROM_SYSTEM_BIOS( 1, "japan",    "Japan MVS (J3)" )
	ROM_LOAD16_WORD_SWAP_BIOS( 1, "japan-j3.bin",0x00000, 0x020000, CRC(dff6d41f) SHA1(e92910e20092577a4523a6b39d578a71d4de7085) )

	ROM_REGION( 0x30000, "audiocpu", 0 )
	ROM_LOAD( "216.m1", 0x00000, 0x20000, CRC(1b096820) SHA1(72852e78c620038f8dafde5e54e02e418c31be9c) )
	ROM_RELOAD( 0x10000, 0x20000 )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "059.v1", 0x000000, 0x200000, CRC(530c50fd) SHA1(29401cee7f7d2c199c7cb58092e86b28205e81ad) )
	ROM_LOAD( "216.v2", 0x200000, 0x200000, CRC(03667a8d) SHA1(3b0475e553a49f8788f32b0c84f82645cc6b4273) )
	ROM_LOAD( "059.v3", 0x400000, 0x200000, CRC(7038c2f9) SHA1(c1d6f86b24feba03fe009b58199d2eeabe572f4e) )
	ROM_LOAD( "216.v4", 0x600000, 0x200000, CRC(31b99bd6) SHA1(5871751f8e9e6b98337472c22b5e1c7ede0a9311) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "059.c1", 0x0000000, 0x200000, CRC(763ba611) SHA1(d3262e0332c894ee149c5963f882cc5e5562ee57) )
	ROM_LOAD16_BYTE( "059.c2", 0x0000001, 0x200000, CRC(e05e8ca6) SHA1(986a9b16ff92bc101ab567d2d01348e093abea9a) )
	ROM_LOAD16_BYTE( "216.c3", 0x0800000, 0x400000, CRC(665c9f16) SHA1(7ec781a49a462f395b450460b29493f55134eac2) )
	ROM_LOAD16_BYTE( "216.c4", 0x0800001, 0x400000, CRC(7f5d03db) SHA1(365ed266c121f4df0bb76898955a8ae0e668a216) )
	ROM_LOAD16_BYTE( "059.c5", 0x1000000, 0x200000, CRC(59013f9e) SHA1(5bf48fcc450da72a8c4685f6e3887e67eae49988) )
	ROM_LOAD16_BYTE( "059.c6", 0x1000001, 0x200000, CRC(1c8d5def) SHA1(475d89a5c4922a9f6bd756d23c2624d57b6e9d62) )
	ROM_LOAD16_BYTE( "059.c7", 0x1800000, 0x200000, CRC(c88f7035) SHA1(c29a428b741f4fe7b71a3bc23c87925b6bc1ca8f) )
	ROM_LOAD16_BYTE( "059.c8", 0x1800001, 0x200000, CRC(484ce3ba) SHA1(4f21ed20ce6e2b67e2b079404599310c94f591ff) )
ROM_END


/****************************************
 ID-0217
 . ADM-012
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . ADH-012
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( ninjamas )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "217.p1",  0x000000, 0x100000, CRC(3e97ed69) SHA1(336bcae375a5109945d11356503bf0d9f4a9a50a) )
	ROM_LOAD16_WORD_SWAP( "217.p2", 0x100000, 0x200000, CRC(191fca88) SHA1(e318e5931704779bbe461719a5eeeba89bd83a5d) )

	NEO_SFIX_128K( "217.s1", CRC(8ff782f0) SHA1(90099c154357042ba658d4ef6abe4d9335bb7172) )

	NEO_BIOS_AUDIO_128K( "217.m1", CRC(d00fb2af) SHA1(6bcaa52e1641cc24288e1f22f4dc98e8d8921b90) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "217.v1", 0x000000, 0x400000, CRC(1c34e013) SHA1(5368e413d2188c4fd063b6bb7d5f498ff83ea812) )
	ROM_LOAD( "217.v2", 0x400000, 0x200000, CRC(22f1c681) SHA1(09da03b2e63d180e55173ff25e8735c4162f027b) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "217.c1", 0x0000000, 0x400000, CRC(5fe97bc4) SHA1(d76c955d83baa2b9fd24222a9b2852947b7b92f0) )
	ROM_LOAD16_BYTE( "217.c2", 0x0000001, 0x400000, CRC(886e0d66) SHA1(d407e1525e4ebe996e14f6e5c0396a10f736a50d) )
	ROM_LOAD16_BYTE( "217.c3", 0x0800000, 0x400000, CRC(59e8525f) SHA1(19f602c71545d6c021dc72e112d3a8b8efe7a9b7) )
	ROM_LOAD16_BYTE( "217.c4", 0x0800001, 0x400000, CRC(8521add2) SHA1(0d1a6f2979302c4c282e31ff334d2d887aec74f7) )
	ROM_LOAD16_BYTE( "217.c5", 0x1000000, 0x400000, CRC(fb1896e5) SHA1(777a8caa9ebdbddf89e3d5ab650c94a55228ce54) )
	ROM_LOAD16_BYTE( "217.c6", 0x1000001, 0x400000, CRC(1c98c54b) SHA1(cb1cad161d9b9f2f5a7cf8ae4d6d35b51acf90f5) )
	ROM_LOAD16_BYTE( "217.c7", 0x1800000, 0x400000, CRC(8b0ede2e) SHA1(ea632ac98291ddac95441b7fe2349974b2da8a42) )
	ROM_LOAD16_BYTE( "217.c8", 0x1800001, 0x400000, CRC(a085bb61) SHA1(6a3e9e6ba96072b8849b407f2b24103dc0852259) )
ROM_END

/****************************************
 ID-0218
 . NGM-218
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . NGH-218
****************************************/

ROM_START( ragnagrd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "218.p1", 0x100000, 0x100000, CRC(ca372303) SHA1(67991e4fef9b36bc7d909810eebb857ac2f906f1) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "218.s1", CRC(7d402f9a) SHA1(59ec29d03e62e7a8bef689a124a9164f43b2ace1) )

	NEO_BIOS_AUDIO_128K( "218.m1", CRC(17028bcf) SHA1(7a4e8f33ce9b41beac2152b8f6003f247699e2e1) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "218.v1", 0x000000, 0x400000, CRC(61eee7f4) SHA1(5b11b1a0b1b74dfbc2998cbda9f8f7a5e9059957) )
	ROM_LOAD( "218.v2", 0x400000, 0x400000, CRC(6104e20b) SHA1(18e8aae3e51e141977d523a10e737ff68fe81910) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "218.c1", 0x0000000, 0x400000, CRC(c31500a4) SHA1(cc82100038988872721028044ed2e9764bcc2fb0) )
	ROM_LOAD16_BYTE( "218.c2", 0x0000001, 0x400000, CRC(98aba1f9) SHA1(121276c569967e501d8e1b83747f1bdebff612ea) )
	ROM_LOAD16_BYTE( "218.c3", 0x0800000, 0x400000, CRC(833c163a) SHA1(b7e5356bbd9efab67fedb5bc671ba8bbd661fe0f) )
	ROM_LOAD16_BYTE( "218.c4", 0x0800001, 0x400000, CRC(c1a30f69) SHA1(f87ddda4695abcd14f5c2d4b7d41f72ad5b064cc) )
	ROM_LOAD16_BYTE( "218.c5", 0x1000000, 0x400000, CRC(6b6de0ff) SHA1(1abb24cb407258235f4a572cf101d0774823040b) )
	ROM_LOAD16_BYTE( "218.c6", 0x1000001, 0x400000, CRC(94beefcf) SHA1(d2ff0bac325c9c823dba68bd4f281b3b9f8f68e7) )
	ROM_LOAD16_BYTE( "218.c7", 0x1800000, 0x400000, CRC(de6f9b28) SHA1(455adb6bb986af8a00d7f32b7f4f3715fc3007f6) )
	ROM_LOAD16_BYTE( "218.c8", 0x1800001, 0x400000, CRC(d9b311f6) SHA1(ba61a7ab3f08bb7348ad6cd01e5d29ca5ee75074) )
ROM_END

/****************************************
 ID-0219
 . NGM-219
 NEO-MVS PROGBK1 / NEO-MVS CHA256
****************************************/

ROM_START( pgoal ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "219.p1", 0x100000, 0x100000, CRC(6af0e574) SHA1(c3f0fed0d942e48c99c80b1713f271c033ce0f4f) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "219.s1", CRC(002f3c88) SHA1(a8a5bbc5397c8ae9858e38997ebdc713b7b4f50a) )

	NEO_BIOS_AUDIO_128K( "219.m1", CRC(958efdc8) SHA1(aacc6056b1ff48cde8f241a11a27473cfb4b4aa3) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "219.v1", 0x000000, 0x400000, CRC(d0ae33d9) SHA1(cb21a91184d9d84ff25ca86c00dcadfc210272a8) )

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "219.c1", 0x0000000, 0x400000, CRC(67fec4dc) SHA1(b99767972a2a4fce2b704df8d08e6b092665a696) )
	ROM_LOAD16_BYTE( "219.c2", 0x0000001, 0x400000, CRC(86ed01f2) SHA1(9d7d1493946e8fbbd572503d2362b0156c023b76) )
	ROM_LOAD16_BYTE( "219.c3", 0x0800000, 0x200000, CRC(5fdad0a5) SHA1(56f6d2a7224aa4e82a1858079f918e85cadbd6c2) )
	ROM_LOAD16_BYTE( "219.c4", 0x0800001, 0x200000, CRC(f57b4a1c) SHA1(875ca69afbc5304ec23f4bc9186abe92f477f6c8) )
ROM_END

/****************************************
 ID-0220
 Choutetsu Brikin'ger - Iron clad (prototype) 1996 Saurus
****************************************/

ROM_START( ironclad ) /* Prototype - crcs should match the ones of the unreleased dump. */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proto_220.p1", 0x100000, 0x100000, CRC(62a942c6) SHA1(12aaa7d9bd84328d1bf4610e056b5c57d0252537) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "proto_220.s1", CRC(372fe217) SHA1(493433e682f519bf647e1481c8bdd3a980830ffb) )

	NEO_BIOS_AUDIO_128K( "proto_220.m1", CRC(3a08bb63) SHA1(d8fbbf42a006ccafc3cd99808d28c82dbaac4590) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "proto_220.v1", 0x000000, 0x400000, CRC(8f30a215) SHA1(0ee866a468c4c3608d55df2b5cb9243c8016d77c) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "proto_220.c1", 0x000000, 0x400000, CRC(9aa2b7dc) SHA1(6b3dff292c86f949890b1f8201bc5278f38c2668) )
	ROM_LOAD16_BYTE( "proto_220.c2", 0x000001, 0x400000, CRC(8a2ad708) SHA1(9568ac4cc0552e7fd3e50d3cd8d9f0f4fe7df1d4) )
	ROM_LOAD16_BYTE( "proto_220.c3", 0x800000, 0x400000, CRC(d67fb15a) SHA1(842971aeaf3c92e70f7c653bbf29058bc60f5b71) )
	ROM_LOAD16_BYTE( "proto_220.c4", 0x800001, 0x400000, CRC(e73ea38b) SHA1(27138d588e61e86c292f12d16e36c3681075c607) )
ROM_END

ROM_START( ironclado ) /* Prototype - bootleg/hack based on later release. */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proto_220-p1o.p1", 0x100000, 0x100000, CRC(ce37e3a0) SHA1(488f95fa15f56eea6666dda13d96ec29dba18e19) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "proto_220.s1", CRC(372fe217) SHA1(493433e682f519bf647e1481c8bdd3a980830ffb) )

	NEO_BIOS_AUDIO_128K( "proto_220.m1", CRC(3a08bb63) SHA1(d8fbbf42a006ccafc3cd99808d28c82dbaac4590) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "proto_220.v1", 0x000000, 0x400000, CRC(8f30a215) SHA1(0ee866a468c4c3608d55df2b5cb9243c8016d77c) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "proto_220.c1", 0x000000, 0x400000, CRC(9aa2b7dc) SHA1(6b3dff292c86f949890b1f8201bc5278f38c2668) )
	ROM_LOAD16_BYTE( "proto_220.c2", 0x000001, 0x400000, CRC(8a2ad708) SHA1(9568ac4cc0552e7fd3e50d3cd8d9f0f4fe7df1d4) )
	ROM_LOAD16_BYTE( "proto_220.c3", 0x800000, 0x400000, CRC(d67fb15a) SHA1(842971aeaf3c92e70f7c653bbf29058bc60f5b71) )
	ROM_LOAD16_BYTE( "proto_220.c4", 0x800001, 0x400000, CRC(e73ea38b) SHA1(27138d588e61e86c292f12d16e36c3681075c607) )
ROM_END

/****************************************
 ID-0221
 . NGM-221
 NEO-MVS PROGBK1 / NEO-MVS CHA256B
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . NGH-221
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( magdrop2 )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "221.p1", 0x000000, 0x80000, CRC(7be82353) SHA1(08ab39f52b893591c13a7d7aa26b20ce86e9ddf5) )

	NEO_SFIX_128K( "221.s1", CRC(2a4063a3) SHA1(0e09a7d88d85b1a2100888f4211960ea56ef978b) )

	NEO_BIOS_AUDIO_128K( "221.m1", CRC(bddae628) SHA1(02c77e6aaaed43e39778bf83a3184e7c21db63d4) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "221.v1", 0x000000, 0x200000, CRC(7e5e53e4) SHA1(72b063b2d4acaaf72a20d14ad5bfc90cb64d3fed) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "221.c1", 0x000000, 0x400000, CRC(1f862a14) SHA1(1253e8b65d863d552d00dbdbfc5c168f5fc7edd1) )
	ROM_LOAD16_BYTE( "221.c2", 0x000001, 0x400000, CRC(14b90536) SHA1(e0d41f6b84d8261729f154b44ddd95c9b9c0714a) )
ROM_END

/****************************************
 ID-0222
 . NGM-222
 NEO-MVS PROGBK1 / NEO-MVS CHA256B
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . NGH-222
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( samsho4 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "222.p1",  0x000000, 0x100000, CRC(1a5cb56d) SHA1(9a0a5a1c7c5d428829f22d3d17f7033d43a51b5b) )
	ROM_LOAD16_WORD_SWAP( "222.p2", 0x100000, 0x400000, CRC(b023cd8b) SHA1(35b4cec9858225f90acdfa16ed8a3017d0d08327) )

	NEO_SFIX_128K( "222.s1", CRC(8d3d3bf9) SHA1(9975ed9b458bdd14e23451d2534153f68a5e4e6c) )

	NEO_BIOS_AUDIO_128K( "222.m1", CRC(7615bc1b) SHA1(b936f7b341f6fe0921b4c41049734684583e3596) )

	ROM_REGION( 0xa00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "222.v1", 0x000000, 0x400000, CRC(7d6ba95f) SHA1(03cb4e0d770e0b332b07b64cacef624460b84c78) )
	ROM_LOAD( "222.v2", 0x400000, 0x400000, CRC(6c33bb5d) SHA1(fd5d4e08a962dd0d22c52c91bad5ec7f23cfb901) )
	ROM_LOAD( "222.v3", 0x800000, 0x200000, CRC(831ea8c0) SHA1(f2987b7d09bdc4311e972ce8a9ab7ca9802db4db) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "222.c1", 0x0000000, 0x400000, CRC(68f2ed95) SHA1(c0a02df012cd25bcfe341770ea861a80294148cb) )
	ROM_LOAD16_BYTE( "222.c2", 0x0000001, 0x400000, CRC(a6e9aff0) SHA1(15addca49951ed53fa3c000c8d7cd327d012a620) )
	ROM_LOAD16_BYTE( "222.c3", 0x0800000, 0x400000, CRC(c91b40f4) SHA1(dcda45e0336204e3e024de08edfd0a3217bc1fdd) )
	ROM_LOAD16_BYTE( "222.c4", 0x0800001, 0x400000, CRC(359510a4) SHA1(b6642677ebdff7788263266402080272b8a66b15) )
	ROM_LOAD16_BYTE( "222.c5", 0x1000000, 0x400000, CRC(9cfbb22d) SHA1(789c32f917d0c6e38601cd390a7bf9d803131a4a) )
	ROM_LOAD16_BYTE( "222.c6", 0x1000001, 0x400000, CRC(685efc32) SHA1(db21ba1c7e3631ce0f1cb6f503ae7e0e043ff71b) )
	ROM_LOAD16_BYTE( "222.c7", 0x1800000, 0x400000, CRC(d0f86f0d) SHA1(32502d71c2ab1469c492b6b382bf2bb3f85981d9) )
	ROM_LOAD16_BYTE( "222.c8", 0x1800001, 0x400000, CRC(adfc50e3) SHA1(7d7ee874355b5aa75ad9c9a5c9c3df98d098d85e) )
ROM_END

ROM_START( samsho4k ) /* KOREAN VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "222k.p1", 0x000000, 0x100000, CRC(06e0a25d) SHA1(81e6727e0acb67ae41383518c0fc07f28d232979) )
	ROM_LOAD16_WORD_SWAP( "222.p2", 0x100000, 0x400000, CRC(b023cd8b) SHA1(35b4cec9858225f90acdfa16ed8a3017d0d08327) )

	NEO_SFIX_128K( "222k.s1", CRC(d313687d) SHA1(9ba468a9d582ef76c863f57ad9a0f811f3f08bd9) )

	NEO_BIOS_AUDIO_128K( "222.m1", CRC(7615bc1b) SHA1(b936f7b341f6fe0921b4c41049734684583e3596) )

	ROM_REGION( 0xa00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "222.v1", 0x000000, 0x400000, CRC(7d6ba95f) SHA1(03cb4e0d770e0b332b07b64cacef624460b84c78) )
	ROM_LOAD( "222.v2", 0x400000, 0x400000, CRC(6c33bb5d) SHA1(fd5d4e08a962dd0d22c52c91bad5ec7f23cfb901) )
	ROM_LOAD( "222.v3", 0x800000, 0x200000, CRC(831ea8c0) SHA1(f2987b7d09bdc4311e972ce8a9ab7ca9802db4db) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "222.c1", 0x0000000, 0x400000, CRC(68f2ed95) SHA1(c0a02df012cd25bcfe341770ea861a80294148cb) )
	ROM_LOAD16_BYTE( "222.c2", 0x0000001, 0x400000, CRC(a6e9aff0) SHA1(15addca49951ed53fa3c000c8d7cd327d012a620) )
	ROM_LOAD16_BYTE( "222.c3", 0x0800000, 0x400000, CRC(c91b40f4) SHA1(dcda45e0336204e3e024de08edfd0a3217bc1fdd) )
	ROM_LOAD16_BYTE( "222.c4", 0x0800001, 0x400000, CRC(359510a4) SHA1(b6642677ebdff7788263266402080272b8a66b15) )
	ROM_LOAD16_BYTE( "222.c5", 0x1000000, 0x400000, CRC(9cfbb22d) SHA1(789c32f917d0c6e38601cd390a7bf9d803131a4a) )
	ROM_LOAD16_BYTE( "222.c6", 0x1000001, 0x400000, CRC(685efc32) SHA1(db21ba1c7e3631ce0f1cb6f503ae7e0e043ff71b) )
	ROM_LOAD16_BYTE( "222.c7", 0x1800000, 0x400000, CRC(d0f86f0d) SHA1(32502d71c2ab1469c492b6b382bf2bb3f85981d9) )
	ROM_LOAD16_BYTE( "222.c8", 0x1800001, 0x400000, CRC(adfc50e3) SHA1(7d7ee874355b5aa75ad9c9a5c9c3df98d098d85e) )
ROM_END

/****************************************
 ID-0223
 . NGM-223
 NEO-MVS PROGBK1 / NEO-MVS CHA256B
 . NGH-223
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( rbffspec )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "223.p1",  0x000000, 0x100000, CRC(f84a2d1d) SHA1(fc19225d9dbdb6bd0808023ee32c7829f6ffdef6) )
	ROM_LOAD16_WORD_SWAP( "223.p2", 0x100000, 0x400000, CRC(addd8f08) SHA1(abaf5b86c8ec915c07ef2d83fce9ad03acaa4817) )

	NEO_SFIX_128K( "223.s1", CRC(7ecd6e8c) SHA1(465455afc4d83cbb118142be4671b2539ffafd79) )

	NEO_BIOS_AUDIO_128K( "223.m1", CRC(3fee46bf) SHA1(e750f85233953853618fcdff980a4721af1710a3) )

	ROM_REGION( 0xc00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "223.v1", 0x000000, 0x400000, CRC(76673869) SHA1(78a26afa29f73de552ffabdbf3fc4bf26be8ae9e) )
	ROM_LOAD( "223.v2", 0x400000, 0x400000, CRC(7a275acd) SHA1(8afe87ce822614262b72a90b371fc79155ac0d0c) )
	ROM_LOAD( "223.v3", 0x800000, 0x400000, CRC(5a797fd2) SHA1(94958e334f86d4d71059af8138f255b8d97a3b01) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "223.c1", 0x0000000, 0x400000, CRC(ebab05e2) SHA1(0d60a8b631e3a3dcfbfdd7779dee081c9548ec39) )
	ROM_LOAD16_BYTE( "223.c2", 0x0000001, 0x400000, CRC(641868c3) SHA1(aa1aeb661842276b3326bfa4f1456f75bfecd52e) )
	ROM_LOAD16_BYTE( "223.c3", 0x0800000, 0x400000, CRC(ca00191f) SHA1(96977febfcc513e1848d7029ff169cdf51104038) )
	ROM_LOAD16_BYTE( "223.c4", 0x0800001, 0x400000, CRC(1f23d860) SHA1(e18df52f898a51074e07a0b8c6e75873e7cde35e) )
	ROM_LOAD16_BYTE( "223.c5", 0x1000000, 0x400000, CRC(321e362c) SHA1(39bd189334278f266124c97c6f70995f6f171cea) )
	ROM_LOAD16_BYTE( "223.c6", 0x1000001, 0x400000, CRC(d8fcef90) SHA1(bbccacb27f1e587bc144fe7ce68bd7b327ceaaee) )
	ROM_LOAD16_BYTE( "223.c7", 0x1800000, 0x400000, CRC(bc80dd2d) SHA1(086f372015eede88c6c578595fe915e28a589d2f) )
	ROM_LOAD16_BYTE( "223.c8", 0x1800001, 0x400000, CRC(5ad62102) SHA1(e28cc9840caed2a1a8bd65a03bef05231071040c) )
ROM_END

ROM_START( rbffspeck ) /* KOREAN VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "223k.p1", 0x000000, 0x100000, CRC(b78c8391) SHA1(936b356ac135331b10a37bc10882ec2e4f6b400b) )
	ROM_LOAD16_WORD_SWAP( "223.p2", 0x100000, 0x400000, CRC(addd8f08) SHA1(abaf5b86c8ec915c07ef2d83fce9ad03acaa4817) )

	NEO_SFIX_128K( "223.s1", CRC(7ecd6e8c) SHA1(465455afc4d83cbb118142be4671b2539ffafd79) )

	NEO_BIOS_AUDIO_128K( "223.m1", CRC(3fee46bf) SHA1(e750f85233953853618fcdff980a4721af1710a3) )

	ROM_REGION( 0xc00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "223.v1", 0x000000, 0x400000, CRC(76673869) SHA1(78a26afa29f73de552ffabdbf3fc4bf26be8ae9e) )
	ROM_LOAD( "223.v2", 0x400000, 0x400000, CRC(7a275acd) SHA1(8afe87ce822614262b72a90b371fc79155ac0d0c) )
	ROM_LOAD( "223.v3", 0x800000, 0x400000, CRC(5a797fd2) SHA1(94958e334f86d4d71059af8138f255b8d97a3b01) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "223.c1", 0x0000000, 0x400000, CRC(ebab05e2) SHA1(0d60a8b631e3a3dcfbfdd7779dee081c9548ec39) )
	ROM_LOAD16_BYTE( "223.c2", 0x0000001, 0x400000, CRC(641868c3) SHA1(aa1aeb661842276b3326bfa4f1456f75bfecd52e) )
	ROM_LOAD16_BYTE( "223.c3", 0x0800000, 0x400000, CRC(ca00191f) SHA1(96977febfcc513e1848d7029ff169cdf51104038) )
	ROM_LOAD16_BYTE( "223.c4", 0x0800001, 0x400000, CRC(1f23d860) SHA1(e18df52f898a51074e07a0b8c6e75873e7cde35e) )
	ROM_LOAD16_BYTE( "223.c5", 0x1000000, 0x400000, CRC(321e362c) SHA1(39bd189334278f266124c97c6f70995f6f171cea) )
	ROM_LOAD16_BYTE( "223.c6", 0x1000001, 0x400000, CRC(d8fcef90) SHA1(bbccacb27f1e587bc144fe7ce68bd7b327ceaaee) )
	ROM_LOAD16_BYTE( "223.c7", 0x1800000, 0x400000, CRC(bc80dd2d) SHA1(086f372015eede88c6c578595fe915e28a589d2f) )
	ROM_LOAD16_BYTE( "223.c8", 0x1800001, 0x400000, CRC(5ad62102) SHA1(e28cc9840caed2a1a8bd65a03bef05231071040c) )
ROM_END

/****************************************
 ID-0224
 . ADM-013
 NEO-MVS PROGBK1 / NEO-MVS CHA256B
 . ADH-013
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( twinspri )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "224.p1", 0x100000, 0x100000, CRC(7697e445) SHA1(5b55ca120f77a931d40719b14e0bfc8cac1d628c) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "224.s1", CRC(eeed5758) SHA1(24e48f396716e145b692468762cf595fb7267873) )

	NEO_BIOS_AUDIO_128K( "224.m1", CRC(364d6f96) SHA1(779b95a6476089b71f48c8368d9043ee1dba9032) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "224.v1", 0x000000, 0x400000, CRC(ff57f088) SHA1(1641989b8aac899dbd68aa2332bcdf9b90b33564) )
	ROM_LOAD( "224.v2", 0x400000, 0x200000, CRC(7ad26599) SHA1(822030037b7664795bf3d64e1452d0aecc22497e) )

	ROM_REGION( 0xa00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "224.c1", 0x000000, 0x400000, CRC(f7da64ab) SHA1(587a10ed9235c9046a3523fe80feba07764fac9b) )
	ROM_LOAD16_BYTE( "224.c2", 0x000001, 0x400000, CRC(4c09bbfb) SHA1(e781aafba3bdefb7ed152826f4c3eb441735331c) )
	ROM_LOAD16_BYTE( "224.c3", 0x800000, 0x100000, CRC(c59e4129) SHA1(93f02d1b4fbb152a9d336494fbff0d7642921de5) )
	ROM_LOAD16_BYTE( "224.c4", 0x800001, 0x100000, CRC(b5532e53) SHA1(7d896c25ba97f6e5d43c13d4df4ba72964a976ed) )
ROM_END

/****************************************
 ID-0225
 . SUM-225
 NEO-MVS PROGBK1 / NEO-MVS CHA256B
 . SUH-225
****************************************/

ROM_START( wakuwak7 )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "225.p1",  0x000000, 0x100000, CRC(b14da766) SHA1(bdffd72ff705fc6b085a4026217bac1c4bc93163) )
	ROM_LOAD16_WORD_SWAP( "225.p2", 0x100000, 0x200000, CRC(fe190665) SHA1(739d9a8fc2da34381654d9e291141eacc210ae5c) )

	NEO_SFIX_128K( "225.s1", CRC(71c4b4b5) SHA1(9410f13807f01082dc86f2d84051be4bed8e9f7c) )

	NEO_BIOS_AUDIO_128K( "225.m1", CRC(0634bba6) SHA1(153aaf016440500df7a4454f3f2f2911219cb7d8) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "225.v1", 0x000000, 0x400000, CRC(6195c6b4) SHA1(66c06b5904aedb256e3997bbec60f8ab50c6ff0c) )
	ROM_LOAD( "225.v2", 0x400000, 0x400000, CRC(6159c5fe) SHA1(9015e93416497f1ef877c717afed40f7ecfa42e4) )

	ROM_REGION( 0x1800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "225.c1", 0x0000000, 0x400000, CRC(ee4fea54) SHA1(314b513a52b2cc88cbf2409d1934c357269a8bb2) )
	ROM_LOAD16_BYTE( "225.c2", 0x0000001, 0x400000, CRC(0c549e2d) SHA1(d8c4626231c92e43d9bf183202553ee2b5c532e6) )
	ROM_LOAD16_BYTE( "225.c3", 0x0800000, 0x400000, CRC(af0897c0) SHA1(2b8ec19b9dd0bd1f1171fb01b915e9d25ec8c421) )
	ROM_LOAD16_BYTE( "225.c4", 0x0800001, 0x400000, CRC(4c66527a) SHA1(6c8c9342fad70b456e282b0d52e7ad890e4673d3) )
	ROM_LOAD16_BYTE( "225.c5", 0x1000000, 0x400000, CRC(8ecea2b5) SHA1(cad51e6e76d8258a78becb6f4096dd061f537494) )
	ROM_LOAD16_BYTE( "225.c6", 0x1000001, 0x400000, CRC(0eb11a6d) SHA1(c6d4f978ff3ca190a3060ac52bd7347189194f76) )
ROM_END

/****************************************
 ID-0226
 Pair Pair Wars (prototype) 1996 Sunsoft?
****************************************/

/****************************************
 ID-0227
 . NGM-227
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . NGH-227
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( stakwin2 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "227.p1", 0x100000, 0x100000, CRC(daf101d2) SHA1(96b90f884bae2969ebd8c04aba509928464e2433) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "227.s1", CRC(2a8c4462) SHA1(9155fbb5fee6d46a68d17ea780a7a92565f9aa47) )

	NEO_BIOS_AUDIO_128K( "227.m1", CRC(c8e5e0f9) SHA1(09bb05ae6f09b59b9e4871fae1fc7c3bafd07394) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "227.v1", 0x000000, 0x400000, CRC(b8f24181) SHA1(0a3af88d20ff65b82c58325d32c20b99fc07f7f3) )
	ROM_LOAD( "227.v2", 0x400000, 0x400000, CRC(ee39e260) SHA1(4ed6802564ce262ebe92c7276424056b70998758) )

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "227.c1", 0x0000000, 0x400000, CRC(7d6c2af4) SHA1(e54f0ab15c95d7a6f965b5d8ab28b5445100650b) )
	ROM_LOAD16_BYTE( "227.c2", 0x0000001, 0x400000, CRC(7e402d39) SHA1(9d3a44f98ddd0b606c8b3efa0c6b9d5a46c0bfeb) )
	ROM_LOAD16_BYTE( "227.c3", 0x0800000, 0x200000, CRC(93dfd660) SHA1(5b473c556ef919cd7a872351dbb20a636aae32b6) )
	ROM_LOAD16_BYTE( "227.c4", 0x0800001, 0x200000, CRC(7efea43a) SHA1(3f2b1718fe7be06b6d75ec34badc2de2a3554d3e) )
ROM_END

/****************************************
 ID-0228
 Ghostlop (prototype) 1996 Data East Corp.
****************************************/

ROM_START( ghostlop ) /* Prototype */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proto_228.p1", 0x000000, 0x100000, CRC(6033172e) SHA1(f57fb706aa8dd9e5f9e992a5d35c1799578b59f8) )

	NEO_SFIX_128K( "proto_228.s1", CRC(83c24e81) SHA1(585ef209d8bfc23bdccc1f37d8b764eeedfedc1c) )

	NEO_BIOS_AUDIO_128K( "proto_228.m1", CRC(fd833b33) SHA1(ab6c218c42cba821654cbdae154efecb69f844f6) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "proto_228.v1", 0x000000, 0x200000, CRC(c603fce6) SHA1(5a866471d35895b2ae13cbd5d1cb41bf2e72e1b8) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "proto_228.c1", 0x000000, 0x400000, CRC(bfc99efe) SHA1(5cd2545310142080b8286e787cf5b859f627b3db) )
	ROM_LOAD16_BYTE( "proto_228.c2", 0x000001, 0x400000, CRC(69788082) SHA1(c3ecb42ddcbd9e16d0018a0c3adb56a911d813ca) )
ROM_END

/****************************************
 ID-0229
 King of Fighters '96 CD Collection (CD only)
****************************************/


/* With ID-0230 the product ID code changed from xxM-xxx / xxH-xxx to xxM-xxx0 / xxH-xxx0 */


/****************************************
 ID-0230
 . NGM-2300
 NEO-MVS PROGBK1 / NEO-MVS CHA256B
 . NGH-2300
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( breakers )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "230.p1", 0x100000, 0x100000, CRC(ed24a6e6) SHA1(3fb77ae696d92d2f9a5d589e08b708545c7cda0a) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "230.s1", CRC(076fb64c) SHA1(c166038128d7004f69932141f83b320a35c2b4ca) )

	NEO_BIOS_AUDIO_128K( "230.m1", CRC(3951a1c1) SHA1(1e6442a7ea82ada9503d71045dd93e12bd05254f) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "230.v1", 0x000000, 0x400000, CRC(7f9ed279) SHA1(acd0558960ec29bfc3e3ee99d00e503bebff8513) )
	ROM_LOAD( "230.v2", 0x400000, 0x400000, CRC(1d43e420) SHA1(26d09b8b18b4b802dbda4d6f06626c24d0b7c512) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "230.c1", 0x000000, 0x400000, CRC(68d4ae76) SHA1(2e820067f6963669f104bebf19e865fe4127b4dd) )
	ROM_LOAD16_BYTE( "230.c2", 0x000001, 0x400000, CRC(fdee05cd) SHA1(efc4ffd790953ac7c25d5f045c64a9b49d24b096) )
	ROM_LOAD16_BYTE( "230.c3", 0x800000, 0x400000, CRC(645077f3) SHA1(0ae74f3b4b3b88f128c6d8c0f35ffa53f5d67ef2) )
	ROM_LOAD16_BYTE( "230.c4", 0x800001, 0x400000, CRC(63aeb74c) SHA1(9ff6930c0c3d79b46b86356e8565ce4fcd69ac38) )
ROM_END

/****************************************
 ID-0231
 . ??M-2310
 NEO-MVS PROGBK1 / NEO-MVS CHA42G-3B
****************************************/

ROM_START( miexchng ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "231.p1", 0x000000, 0x80000, CRC(61be1810) SHA1(1ab0e11352ca05329c6e3f5657b60e4a227fcbfb) )

	NEO_SFIX_128K( "231.s1", CRC(fe0c0c53) SHA1(54d56d4463db193e504658f4f6f4997a62ae3d95) )

	NEO_BIOS_AUDIO_128K( "231.m1", CRC(de41301b) SHA1(59ce3836ac8f064d56a446c9374f05bcb40fcfd8) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "231.v1", 0x000000, 0x400000, CRC(113fb898) SHA1(9168ba90c4aa969f69eb11ba3f4d76592d81e05a) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD16_BYTE( "231.c1", 0x000000, 0x200000, CRC(6c403ba3) SHA1(3830446fbd07d5a6564f9ac68a4bec5ff5b7d5c9) )
	ROM_LOAD16_BYTE( "231.c2", 0x000001, 0x200000, CRC(554bcd9b) SHA1(e658161618bd41a66f1040be409efdea28020cf6) )
	ROM_LOAD16_BYTE( "231.c3", 0x400000, 0x100000, CRC(4f6f7a63) SHA1(10935dbc1f52b95979a097b13a114cff18d4d446) )
	ROM_LOAD16_BYTE( "231.c4", 0x400001, 0x100000, CRC(2e35e71b) SHA1(6f248191c2c60ca1b1b4f2ebf08756e036682144) )
ROM_END

/****************************************
 ID-0232
 . NGM-2320
 NEO-MVS PROGBK1 / NEO-MVS CHA512Y
 . NGH-2320
 NEO-AEG PROGBK1Y / NEO-AEG CHA512Y
****************************************/

ROM_START( kof97 ) /* MVS VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "232.p1",  0x000000, 0x100000, CRC(7db81ad9) SHA1(8bc42be872fd497eb198ca13bf004852b88eb1dc) )
	ROM_LOAD16_WORD_SWAP( "232.p2", 0x100000, 0x400000, CRC(158b23f6) SHA1(9744620a70513490aaf9c5eda33e5ec31222be19) )

	NEO_SFIX_128K( "232.s1", CRC(8514ecf5) SHA1(18d8e7feb51ea88816f1c786932a53655b0de6a0) )

	NEO_BIOS_AUDIO_128K( "232.m1", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "232.v1", 0x000000, 0x400000, CRC(22a2b5b5) SHA1(ebdbc977332e6d93e266755000b43857e0082965) )
	ROM_LOAD( "232.v2", 0x400000, 0x400000, CRC(2304e744) SHA1(98d283e2bcc9291a53f52afd35ef76dfb0828432) )
	ROM_LOAD( "232.v3", 0x800000, 0x400000, CRC(759eb954) SHA1(54e77c4e9e6b89458e59824e478ddc33a9c72655) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "232.c1", 0x0000000, 0x800000, CRC(5f8bf0a1) SHA1(e8b63bbc814de171fd18c5864a7fc639970c1ecf) )
	ROM_LOAD16_BYTE( "232.c2", 0x0000001, 0x800000, CRC(e4d45c81) SHA1(fdb2b9326362e27b1c7a5beb977e0bc537488186) )
	ROM_LOAD16_BYTE( "232.c3", 0x1000000, 0x800000, CRC(581d6618) SHA1(14d3124a08ded59f86932c6b28e1a4e48c564ccd) )
	ROM_LOAD16_BYTE( "232.c4", 0x1000001, 0x800000, CRC(49bb1e68) SHA1(f769c1bd1b019521111ff3f0d22c63cb1f2640ef) )
	ROM_LOAD16_BYTE( "232.c5", 0x2000000, 0x400000, CRC(34fc4e51) SHA1(b39c65f27873f71a6f5a5d1d04e5435f874472ee) )
	ROM_LOAD16_BYTE( "232.c6", 0x2000001, 0x400000, CRC(4ff4d47b) SHA1(4d5689ede24a5fe4330bd85d4d3f4eb2795308bb) )
ROM_END

ROM_START( kof97h ) /* AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "232h.p1", 0x000000, 0x100000, CRC(5c2400b7) SHA1(49e23f80c012c62146a1bb8f254a7597823de430) )
	ROM_LOAD16_WORD_SWAP( "232.p2", 0x100000, 0x400000, CRC(158b23f6) SHA1(9744620a70513490aaf9c5eda33e5ec31222be19) )

	NEO_SFIX_128K( "232.s1", CRC(8514ecf5) SHA1(18d8e7feb51ea88816f1c786932a53655b0de6a0) )

	NEO_BIOS_AUDIO_128K( "232.m1", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "232.v1", 0x000000, 0x400000, CRC(22a2b5b5) SHA1(ebdbc977332e6d93e266755000b43857e0082965) )
	ROM_LOAD( "232.v2", 0x400000, 0x400000, CRC(2304e744) SHA1(98d283e2bcc9291a53f52afd35ef76dfb0828432) )
	ROM_LOAD( "232.v3", 0x800000, 0x400000, CRC(759eb954) SHA1(54e77c4e9e6b89458e59824e478ddc33a9c72655) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "232.c1", 0x0000000, 0x800000, CRC(5f8bf0a1) SHA1(e8b63bbc814de171fd18c5864a7fc639970c1ecf) )
	ROM_LOAD16_BYTE( "232.c2", 0x0000001, 0x800000, CRC(e4d45c81) SHA1(fdb2b9326362e27b1c7a5beb977e0bc537488186) )
	ROM_LOAD16_BYTE( "232.c3", 0x1000000, 0x800000, CRC(581d6618) SHA1(14d3124a08ded59f86932c6b28e1a4e48c564ccd) )
	ROM_LOAD16_BYTE( "232.c4", 0x1000001, 0x800000, CRC(49bb1e68) SHA1(f769c1bd1b019521111ff3f0d22c63cb1f2640ef) )
	ROM_LOAD16_BYTE( "232.c5", 0x2000000, 0x400000, CRC(34fc4e51) SHA1(b39c65f27873f71a6f5a5d1d04e5435f874472ee) )
	ROM_LOAD16_BYTE( "232.c6", 0x2000001, 0x400000, CRC(4ff4d47b) SHA1(4d5689ede24a5fe4330bd85d4d3f4eb2795308bb) )
ROM_END

ROM_START( kof97k ) /* KOREAN VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "232k.p1",  0x000000, 0x100000, CRC(7db81ad9) SHA1(8bc42be872fd497eb198ca13bf004852b88eb1dc) )
	ROM_LOAD16_WORD_SWAP( "232.p2", 0x100000, 0x400000, CRC(158b23f6) SHA1(9744620a70513490aaf9c5eda33e5ec31222be19) )

	NEO_SFIX_128K( "232.s1", CRC(8514ecf5) SHA1(18d8e7feb51ea88816f1c786932a53655b0de6a0) )

	NEO_BIOS_AUDIO_128K( "232k.m1", CRC(bbea9070) SHA1(c26c2e29fe90966dd574838be63f0037ea799aca) )

	ROM_REGION( 0xc00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "232.v1", 0x000000, 0x400000, CRC(22a2b5b5) SHA1(ebdbc977332e6d93e266755000b43857e0082965) )
	ROM_LOAD( "232.v2", 0x400000, 0x400000, CRC(2304e744) SHA1(98d283e2bcc9291a53f52afd35ef76dfb0828432) )
	ROM_LOAD( "232.v3", 0x800000, 0x400000, CRC(759eb954) SHA1(54e77c4e9e6b89458e59824e478ddc33a9c72655) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "232.c1", 0x0000000, 0x800000, CRC(5f8bf0a1) SHA1(e8b63bbc814de171fd18c5864a7fc639970c1ecf) )
	ROM_LOAD16_BYTE( "232.c2", 0x0000001, 0x800000, CRC(e4d45c81) SHA1(fdb2b9326362e27b1c7a5beb977e0bc537488186) )
	ROM_LOAD16_BYTE( "232.c3", 0x1000000, 0x800000, CRC(581d6618) SHA1(14d3124a08ded59f86932c6b28e1a4e48c564ccd) )
	ROM_LOAD16_BYTE( "232.c4", 0x1000001, 0x800000, CRC(49bb1e68) SHA1(f769c1bd1b019521111ff3f0d22c63cb1f2640ef) )
	ROM_LOAD16_BYTE( "232.c5", 0x2000000, 0x400000, CRC(34fc4e51) SHA1(b39c65f27873f71a6f5a5d1d04e5435f874472ee) )
	ROM_LOAD16_BYTE( "232.c6", 0x2000001, 0x400000, CRC(4ff4d47b) SHA1(4d5689ede24a5fe4330bd85d4d3f4eb2795308bb) )
ROM_END

/****************************************
 ID-0233
 . NGM-2330
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . NGH-2330
 NEO-AEG PROGBK1Y / NEO-AEG CHA256RY
****************************************/

ROM_START( magdrop3 )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "233.p1", 0x000000, 0x100000, CRC(931e17fa) SHA1(4a95c4b79d0878485ce272e9f4c4f647bec0e070) )

	NEO_SFIX_128K( "233.s1", CRC(7399e68a) SHA1(b535ee56a0f0995f04674e676f6aa636ffad26aa) )

	NEO_BIOS_AUDIO_128K( "233.m1", CRC(5beaf34e) SHA1(2905d26945932cddc2dd3a1dc5abba8aa3baee14) )

	ROM_REGION( 0x480000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "233.v1", 0x000000, 0x400000, CRC(58839298) SHA1(18cae7bba997c52780761cbf119c4e4b34397a61) )
	ROM_LOAD( "233.v2", 0x400000, 0x080000, CRC(d5e30df4) SHA1(bbbc0ff5b975471bd682f85976ac4a93f6d44f2e) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "233.c1", 0x000000, 0x400000, CRC(65e3f4c4) SHA1(a6deb75d802225327f8f1c2733a7f2b47e722e59) )
	ROM_LOAD16_BYTE( "233.c2", 0x000001, 0x400000, CRC(35dea6c9) SHA1(ea133bf947f950236f49d0ae0d1a9af3bc1a9a50) )
	ROM_LOAD16_BYTE( "233.c3", 0x800000, 0x400000, CRC(0ba2c502) SHA1(8e0f1e553aef04758aaaa14d5115f0ecace4391e) )
	ROM_LOAD16_BYTE( "233.c4", 0x800001, 0x400000, CRC(70dbbd6d) SHA1(32dd6a04c6329e89f4878e7a56f0d172a6388eea) )
ROM_END

/****************************************
 ID-0234
 . NGM-2340
 NEO-MVS PROGBK1 / NEO-MVS CHA512Y
 . NGH-2340
 NEO-AEG PROGBK1Y / NEO-AEG CHA512Y
****************************************/

ROM_START( lastblad ) /* MVS VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "234.p1",  0x000000, 0x100000, CRC(e123a5a3) SHA1(a3ddabc00feeb54272b145246612ad4632b0e413) )
	ROM_LOAD16_WORD_SWAP( "234.p2", 0x100000, 0x400000, CRC(0fdc289e) SHA1(1ff31c0b0f4f9ddbedaf4bcf927faaae81892ec7) )

	NEO_SFIX_128K( "234.s1", CRC(95561412) SHA1(995de272f572fd08d909d3d0af4251b9957b3640) )

	NEO_BIOS_AUDIO_128K( "234.m1", CRC(087628ea) SHA1(48dcf739bb16699af4ab8ed632b7dcb25e470e06) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "234.v1", 0x000000, 0x400000, CRC(ed66b76f) SHA1(8a05ff06d9b6f01c6c16b3026282eaabb0e25b44) )
	ROM_LOAD( "234.v2", 0x400000, 0x400000, CRC(a0e7f6e2) SHA1(753ff74fa9294f695aae511ae01ead119b114a57) )
	ROM_LOAD( "234.v3", 0x800000, 0x400000, CRC(a506e1e2) SHA1(b3e04ba1a5cb50b77c6fbe9fe353b9b64b6f3f74) )
	ROM_LOAD( "234.v4", 0xc00000, 0x400000, CRC(0e34157f) SHA1(20a1f4833e5e29ba0073c1712d7a17ab7a2a035c) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "234.c1", 0x0000000, 0x800000, CRC(9f7e2bd3) SHA1(2828aca0c0f5802110f10453c1cf640f69736554) )
	ROM_LOAD16_BYTE( "234.c2", 0x0000001, 0x800000, CRC(80623d3c) SHA1(ad460615115ec8fb25206f012da59ecfc8059b64) )
	ROM_LOAD16_BYTE( "234.c3", 0x1000000, 0x800000, CRC(91ab1a30) SHA1(e3cf9133784bef2c8f1bfe45f277ccf82cc6f6a1) )
	ROM_LOAD16_BYTE( "234.c4", 0x1000001, 0x800000, CRC(3d60b037) SHA1(78a50233bcd19e92c7b6f7ee1a53417d9db21f6a) )
	ROM_LOAD16_BYTE( "234.c5", 0x2000000, 0x400000, CRC(1ba80cee) SHA1(0c59057183b5279b747e73213b4cd3c6d7ad9eb1) )
	ROM_LOAD16_BYTE( "234.c6", 0x2000001, 0x400000, CRC(beafd091) SHA1(55df9cc128eb0f00856de3996c946e3efe8f09a5) )
ROM_END

ROM_START( lastbladh ) /* AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "234h.p1", 0x000000, 0x100000, CRC(cd01c06d) SHA1(d66142571afe07c6191b52f319f1bc8bc8541c14) )
	ROM_LOAD16_WORD_SWAP( "234.p2", 0x100000, 0x400000, CRC(0fdc289e) SHA1(1ff31c0b0f4f9ddbedaf4bcf927faaae81892ec7) )

	NEO_SFIX_128K( "234.s1", CRC(95561412) SHA1(995de272f572fd08d909d3d0af4251b9957b3640) )

	NEO_BIOS_AUDIO_128K( "234.m1", CRC(087628ea) SHA1(48dcf739bb16699af4ab8ed632b7dcb25e470e06) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "234.v1", 0x000000, 0x400000, CRC(ed66b76f) SHA1(8a05ff06d9b6f01c6c16b3026282eaabb0e25b44) )
	ROM_LOAD( "234.v2", 0x400000, 0x400000, CRC(a0e7f6e2) SHA1(753ff74fa9294f695aae511ae01ead119b114a57) )
	ROM_LOAD( "234.v3", 0x800000, 0x400000, CRC(a506e1e2) SHA1(b3e04ba1a5cb50b77c6fbe9fe353b9b64b6f3f74) )
	ROM_LOAD( "234.v4", 0xc00000, 0x400000, CRC(0e34157f) SHA1(20a1f4833e5e29ba0073c1712d7a17ab7a2a035c) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "234.c1", 0x0000000, 0x800000, CRC(9f7e2bd3) SHA1(2828aca0c0f5802110f10453c1cf640f69736554) )
	ROM_LOAD16_BYTE( "234.c2", 0x0000001, 0x800000, CRC(80623d3c) SHA1(ad460615115ec8fb25206f012da59ecfc8059b64) )
	ROM_LOAD16_BYTE( "234.c3", 0x1000000, 0x800000, CRC(91ab1a30) SHA1(e3cf9133784bef2c8f1bfe45f277ccf82cc6f6a1) )
	ROM_LOAD16_BYTE( "234.c4", 0x1000001, 0x800000, CRC(3d60b037) SHA1(78a50233bcd19e92c7b6f7ee1a53417d9db21f6a) )
	ROM_LOAD16_BYTE( "234.c5", 0x2000000, 0x400000, CRC(1ba80cee) SHA1(0c59057183b5279b747e73213b4cd3c6d7ad9eb1) )
	ROM_LOAD16_BYTE( "234.c6", 0x2000001, 0x400000, CRC(beafd091) SHA1(55df9cc128eb0f00856de3996c946e3efe8f09a5) )
ROM_END

ROM_START( lastsold ) /* KOREAN VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "134k.p1", 0x000000, 0x100000, CRC(906f3065) SHA1(25167665f1b8e82e13f7fcf4d0e3c54a925c2a58) )
	ROM_LOAD16_WORD_SWAP( "234.p2", 0x100000, 0x400000, CRC(0fdc289e) SHA1(1ff31c0b0f4f9ddbedaf4bcf927faaae81892ec7) )

	NEO_SFIX_128K( "234.s1", CRC(95561412) SHA1(995de272f572fd08d909d3d0af4251b9957b3640) )

	NEO_BIOS_AUDIO_128K( "234.m1", CRC(087628ea) SHA1(48dcf739bb16699af4ab8ed632b7dcb25e470e06) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "234.v1", 0x000000, 0x400000, CRC(ed66b76f) SHA1(8a05ff06d9b6f01c6c16b3026282eaabb0e25b44) )
	ROM_LOAD( "234.v2", 0x400000, 0x400000, CRC(a0e7f6e2) SHA1(753ff74fa9294f695aae511ae01ead119b114a57) )
	ROM_LOAD( "234.v3", 0x800000, 0x400000, CRC(a506e1e2) SHA1(b3e04ba1a5cb50b77c6fbe9fe353b9b64b6f3f74) )
	ROM_LOAD( "234.v4", 0xc00000, 0x400000, CRC(0e34157f) SHA1(20a1f4833e5e29ba0073c1712d7a17ab7a2a035c) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "234.c1", 0x0000000, 0x800000, CRC(9f7e2bd3) SHA1(2828aca0c0f5802110f10453c1cf640f69736554) )
	ROM_LOAD16_BYTE( "234.c2", 0x0000001, 0x800000, CRC(80623d3c) SHA1(ad460615115ec8fb25206f012da59ecfc8059b64) )
	ROM_LOAD16_BYTE( "234.c3", 0x1000000, 0x800000, CRC(91ab1a30) SHA1(e3cf9133784bef2c8f1bfe45f277ccf82cc6f6a1) )
	ROM_LOAD16_BYTE( "234.c4", 0x1000001, 0x800000, CRC(3d60b037) SHA1(78a50233bcd19e92c7b6f7ee1a53417d9db21f6a) )
	ROM_LOAD16_BYTE( "234.c5", 0x2000000, 0x400000, CRC(1ba80cee) SHA1(0c59057183b5279b747e73213b4cd3c6d7ad9eb1) )
	ROM_LOAD16_BYTE( "234.c6", 0x2000001, 0x400000, CRC(beafd091) SHA1(55df9cc128eb0f00856de3996c946e3efe8f09a5) )
ROM_END

/****************************************
 ID-0235
 . ??M-2350
 NEO-MVS PROG 4096 / NEO-MVS CHA 42G-2
****************************************/

ROM_START( puzzldpr ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "235.p1", 0x000000, 0x080000, CRC(afed5de2) SHA1(a5d82c6dbe687505e8c8d7339908da45cd379a0b) )

	NEO_SFIX_128K( "235.s1", CRC(3b13a22f) SHA1(4506fc340d9658a50fa415676564f10bbfba2703) )

	NEO_BIOS_AUDIO_128K( "202.m1", CRC(9c0291ea) SHA1(3fa67c62acba79be6b3a98cc1601e45569fa11ae) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "202.v1", 0x000000, 0x080000, CRC(debeb8fb) SHA1(49a3d3578c087f1a0050168571ef8d1b08c5dc05) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "202.c1", 0x000000, 0x100000, CRC(cc0095ef) SHA1(3d86f455e6db10a2449b775dc386f1826ba3b62e) )
	ROM_LOAD16_BYTE( "202.c2", 0x000001, 0x100000, CRC(42371307) SHA1(df794f989e2883634bf7ffeea48d6bc3854529af) )
ROM_END

/****************************************
 ID-0236
 . ??M-2360
 NEO-MVS PROGBK1 / NEO-MVS CHA512Y
****************************************/

ROM_START( irrmaze ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "236.p1", 0x100000, 0x100000, CRC(4c2ff660) SHA1(4a0cbd09044648ff9ec67723729f16d422c34bda) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "236.s1", CRC(5d1ca640) SHA1(40a9668a1742a44597a07ce72273d17119815637) )

	ROM_REGION16_BE( 0x20000, "mainbios", 0 )
	/* special BIOS with trackball support, we only have one Irritating Maze bios and thats asia */
	ROM_LOAD16_WORD_SWAP("236-bios.sp1", 0x00000, 0x020000, CRC(853e6b96) SHA1(de369cb4a7df147b55168fa7aaf0b98c753b735e) )

	ROM_REGION( 0x30000, "audiocpu", 0 )
	ROM_LOAD( "236.m1", 0x00000, 0x20000, CRC(880a1abd) SHA1(905afa157aba700e798243b842792e50729b19a0) )
	ROM_RELOAD( 0x10000, 0x20000 )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "236.v1", 0x000000, 0x200000, CRC(5f89c3b4) SHA1(dc8fd561cf8dfdd41696dcf14ea8d2d0ac4eec4b) )
	ROM_LOAD( "236.v2", 0x200000, 0x100000, CRC(72e3add7) SHA1(dc49f05274693255416d2e41ecc088027b798eb9) )

	ROM_REGION( 0x0800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "236.c1", 0x000000, 0x400000, CRC(c1d47902) SHA1(727001c34f979226fc8f581113ce2aaac4fc0d42) )
	ROM_LOAD16_BYTE( "236.c2", 0x000001, 0x400000, CRC(e15f972e) SHA1(6a329559c57a67be73a6733513b59e9e6c8d61cc) )
ROM_END

/****************************************
 ID-0237
 . ??M-2370
 NEO-MVS PROG 4096 / NEO-MVS CHA42G-3B
****************************************/

ROM_START( popbounc ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "237.p1", 0x000000, 0x100000, CRC(be96e44f) SHA1(43679da8664fbb491103a1108040ddf94d59fc2b) )

	NEO_SFIX_128K( "237.s1", CRC(b61cf595) SHA1(b14f8b78af7c634d41cf34d36b11b116e61f7342) )

	NEO_BIOS_AUDIO_128K( "237.m1", CRC(d4c946dd) SHA1(6ca09040b5db8d89511d627954c783154d58ab01) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "237.v1", 0x000000, 0x200000, CRC(edcb1beb) SHA1(62f086b9968b366b59276ee4ae3c32c4d76fc6ce) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "237.c1", 0x000000, 0x200000, CRC(eda42d66) SHA1(2735538fcb9dc0c16e043a8728c8b642650189f4) )
	ROM_LOAD16_BYTE( "237.c2", 0x000001, 0x200000, CRC(5e633c65) SHA1(9a82107caf027317c173c1c1ef676f0fdeea79b2) )
ROM_END

/****************************************
 ID-0238
 . ??M-2380
 NEO-MVS PROGBK1 / NEO-MVS CHA256
****************************************/

ROM_START( shocktro ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "238.p1",  0x000000, 0x100000, CRC(5677456f) SHA1(f76169fa5c90871d65e2a16fd1bb036c90533ac8) )
	ROM_LOAD16_WORD_SWAP( "238.p2", 0x100000, 0x400000, CRC(5b4a09c5) SHA1(de04036cba2da4bb2da73d902d1822b82b4f67a9) )

	NEO_SFIX_128K( "238.s1", CRC(1f95cedb) SHA1(adfa74868147fd260481e4c387d254d3b6de83f4) )

	NEO_BIOS_AUDIO_128K( "238.m1", CRC(075b9518) SHA1(ac21b88a860b9572bf24432b4cadcc96d108055d) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "238.v1", 0x000000, 0x400000, CRC(260c0bef) SHA1(9c4f80ce4bb205afed11bb8b8926d20748eb5512) )
	ROM_LOAD( "238.v2", 0x400000, 0x200000, CRC(4ad7d59e) SHA1(bfdf2684f7f38af4e75ad0068ff9463dc2601598) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "238.c1", 0x0000000, 0x400000, CRC(90c6a181) SHA1(a381bc8449718814ff12b3a4f7fc4d1bb7ea1631) )
	ROM_LOAD16_BYTE( "238.c2", 0x0000001, 0x400000, CRC(888720f0) SHA1(cd4d65df8d3ef0dbcca2b7f3f803f45c457f5beb) )
	ROM_LOAD16_BYTE( "238.c3", 0x0800000, 0x400000, CRC(2c393aa3) SHA1(1cd7cebe5861a2d65f1d6615dd7752162e573a02) )
	ROM_LOAD16_BYTE( "238.c4", 0x0800001, 0x400000, CRC(b9e909eb) SHA1(33cc9b2d13e4ed2ab6040ff582a53dc9bca402e0) )
	ROM_LOAD16_BYTE( "238.c5", 0x1000000, 0x400000, CRC(c22c68eb) SHA1(a4b04118b1b1909d3b76be8d9ee5d97db6120600) )
	ROM_LOAD16_BYTE( "238.c6", 0x1000001, 0x400000, CRC(119323cd) SHA1(05a9d4b1fb4cc963b25452ff6f81e296e0c0b2a1) )
	ROM_LOAD16_BYTE( "238.c7", 0x1800000, 0x400000, CRC(a72ce7ed) SHA1(05b151554bd7af09ccf554a17bc3c75a0512faaf) )
	ROM_LOAD16_BYTE( "238.c8", 0x1800001, 0x400000, CRC(1c7c2efb) SHA1(b055ee43cbdaf9a3cb19e4e1f9dd2c40bde69d70) )
ROM_END

ROM_START( shocktroa ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "238a.p1", 0x000000, 0x100000, CRC(efedf8dc) SHA1(f638df9bf7aa7d514ee2bccfc7f2adbf39ca83fc) )
	ROM_LOAD16_WORD_SWAP( "238.p2", 0x100000, 0x400000, CRC(5b4a09c5) SHA1(de04036cba2da4bb2da73d902d1822b82b4f67a9) )

	NEO_SFIX_128K( "238.s1", CRC(1f95cedb) SHA1(adfa74868147fd260481e4c387d254d3b6de83f4) )

	NEO_BIOS_AUDIO_128K( "238.m1", CRC(075b9518) SHA1(ac21b88a860b9572bf24432b4cadcc96d108055d) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "238.v1", 0x000000, 0x400000, CRC(260c0bef) SHA1(9c4f80ce4bb205afed11bb8b8926d20748eb5512) )
	ROM_LOAD( "238.v2", 0x400000, 0x200000, CRC(4ad7d59e) SHA1(bfdf2684f7f38af4e75ad0068ff9463dc2601598) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "238.c1", 0x0000000, 0x400000, CRC(90c6a181) SHA1(a381bc8449718814ff12b3a4f7fc4d1bb7ea1631) )
	ROM_LOAD16_BYTE( "238.c2", 0x0000001, 0x400000, CRC(888720f0) SHA1(cd4d65df8d3ef0dbcca2b7f3f803f45c457f5beb) )
	ROM_LOAD16_BYTE( "238.c3", 0x0800000, 0x400000, CRC(2c393aa3) SHA1(1cd7cebe5861a2d65f1d6615dd7752162e573a02) )
	ROM_LOAD16_BYTE( "238.c4", 0x0800001, 0x400000, CRC(b9e909eb) SHA1(33cc9b2d13e4ed2ab6040ff582a53dc9bca402e0) )
	ROM_LOAD16_BYTE( "238.c5", 0x1000000, 0x400000, CRC(c22c68eb) SHA1(a4b04118b1b1909d3b76be8d9ee5d97db6120600) )
	ROM_LOAD16_BYTE( "238.c6", 0x1000001, 0x400000, CRC(119323cd) SHA1(05a9d4b1fb4cc963b25452ff6f81e296e0c0b2a1) )
	ROM_LOAD16_BYTE( "238.c7", 0x1800000, 0x400000, CRC(a72ce7ed) SHA1(05b151554bd7af09ccf554a17bc3c75a0512faaf) )
	ROM_LOAD16_BYTE( "238.c8", 0x1800001, 0x400000, CRC(1c7c2efb) SHA1(b055ee43cbdaf9a3cb19e4e1f9dd2c40bde69d70) )
ROM_END

/****************************************
 ID-0239
 . NGM-2390
 NEO-MVS PROGBK1 / NEO-MVS CHA512Y
 . NGH-2390
 NEO-AEG PROGBK1Y / NEO-AEG CHA512Y
****************************************/

ROM_START( blazstar )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "239.p1",  0x000000, 0x100000, CRC(183682f8) SHA1(dcee1c2cf4a991ca1f9f2b40c4a738f21682807b) )
	ROM_LOAD16_WORD_SWAP( "239.p2", 0x100000, 0x200000, CRC(9a9f4154) SHA1(f8805453d0995c8fa16cd9accfb7a990071ca630) )

	NEO_SFIX_128K( "239.s1", CRC(d56cb498) SHA1(420ce56431dc7f3f7de84fcbc8c0a17b5eab205e) )

	NEO_BIOS_AUDIO_128K( "239.m1", CRC(d31a3aea) SHA1(e23abfeb23052f0358edcf2c83401025fe632511) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "239.v1", 0x000000, 0x400000, CRC(1b8d5bf7) SHA1(67fc1f7e36e92a89cd1d415eb31a2892f57b0d04) )
	ROM_LOAD( "239.v2", 0x400000, 0x400000, CRC(74cf0a70) SHA1(b00451a2a30de2517ae3eca35eb1fe985b950eb8) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "239.c1", 0x0000000, 0x400000, CRC(84f6d584) SHA1(ff36db8504611b0d8d942d1e24823ff71e4aeb37) )
	ROM_LOAD16_BYTE( "239.c2", 0x0000001, 0x400000, CRC(05a0cb22) SHA1(4abe03e7f3a86f277131d413a3151c7b9c3646c8) )
	ROM_LOAD16_BYTE( "239.c3", 0x0800000, 0x400000, CRC(5fb69c9e) SHA1(77b96518d8ad8ad120537e0f8ba65d69d1c33566) )
	ROM_LOAD16_BYTE( "239.c4", 0x0800001, 0x400000, CRC(0be028c4) SHA1(d3f8b37786ca7838c3525895a7f2b49afc8530d4) )
	ROM_LOAD16_BYTE( "239.c5", 0x1000000, 0x400000, CRC(74bae5f8) SHA1(812c9a31f0721c2971a316b084ce69337dbe3747) )
	ROM_LOAD16_BYTE( "239.c6", 0x1000001, 0x400000, CRC(4e0700d2) SHA1(cd059fb713c403208923c17e1e8ef02fcfd2fe8d) )
	ROM_LOAD16_BYTE( "239.c7", 0x1800000, 0x400000, CRC(010ff4fd) SHA1(2571d406442f007a7458d8ccb0939a9201c9c9bf) )
	ROM_LOAD16_BYTE( "239.c8", 0x1800001, 0x400000, CRC(db60460e) SHA1(a5cb27c0983c8b400d96fd0828ef0639a66d4dba) )
ROM_END

/****************************************
 ID-0240
 . NGM-2400
 NEO-MVS PROGBK1 / NEO-MVS CHA512Y
 . NGH-2400
 NEO-AEG PROGBK1Y / NEO-AEG CHA512Y
****************************************/

ROM_START( rbff2 ) /* MVS VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "240.p1",  0x000000, 0x100000, CRC(80e41205) SHA1(8f83eb8ff54be4ec40f8a0dd2cbe56c54908d00a) )
	ROM_LOAD16_WORD_SWAP( "240.p2", 0x100000, 0x400000, CRC(960aa88d) SHA1(3d9e785891871af90313f178dca2724633406674) )

	NEO_SFIX_128K( "240.s1", CRC(da3b40de) SHA1(e6bf74e057ac6fe1f249a7547f13ba7fbc694561) )

	NEO_BIOS_AUDIO_256K( "240.m1", CRC(ed482791) SHA1(1f54a45967cb7842c33aa24be322c9f33ff75ac3) )

	ROM_REGION( 0x0e00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "240.v1", 0x000000, 0x400000, CRC(f796265a) SHA1(736dff37eb91fc856b4d189249fb0de9b6c0813a) )
	ROM_LOAD( "240.v2", 0x400000, 0x400000, CRC(2cb3f3bb) SHA1(697e677890892f4b028c9a27c66809ca0a8a9b18) )
	ROM_LOAD( "240.v3", 0x800000, 0x400000, CRC(8fe1367a) SHA1(093d7a4ac2b54ad7ffb2dc316fe29415f7a99535) )
	ROM_LOAD( "240.v4", 0xc00000, 0x200000, CRC(996704d8) SHA1(0bf7a1d0660199dedf3c25be757eeab75cc6147e) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "240.c1", 0x0000000, 0x800000, CRC(effac504) SHA1(e36a96e7369b02c7e839b5abf3c6799453ba1927) )
	ROM_LOAD16_BYTE( "240.c2", 0x0000001, 0x800000, CRC(ed182d44) SHA1(a9fc0a3a786bf067c129ec7220df65953dff804f) )
	ROM_LOAD16_BYTE( "240.c3", 0x1000000, 0x800000, CRC(22e0330a) SHA1(0fe7f6a8aeba7f17dbb278e85003969ff10d3cd2) )
	ROM_LOAD16_BYTE( "240.c4", 0x1000001, 0x800000, CRC(c19a07eb) SHA1(139eac8b51cadf328dd42d8109f4e2463f57230c) )
	ROM_LOAD16_BYTE( "240.c5", 0x2000000, 0x800000, CRC(244dff5a) SHA1(156548156d3ceaa808d0053d0749af2526a3943e) )
	ROM_LOAD16_BYTE( "240.c6", 0x2000001, 0x800000, CRC(4609e507) SHA1(bb17f50a377dddb77c1eeda5944a7bcbf0cca5f7) )
ROM_END

ROM_START( rbff2h ) /* AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "240.p1", 0x000000, 0x100000, CRC(b6969780) SHA1(e3373d18e0f0724d69efb8024a27cca121f1b5b2) )
	ROM_LOAD16_WORD_SWAP( "240.p2", 0x100000, 0x400000, CRC(960aa88d) SHA1(3d9e785891871af90313f178dca2724633406674) )

	NEO_SFIX_128K( "240.s1", CRC(da3b40de) SHA1(e6bf74e057ac6fe1f249a7547f13ba7fbc694561) )

	NEO_BIOS_AUDIO_256K( "240.m1", CRC(ed482791) SHA1(1f54a45967cb7842c33aa24be322c9f33ff75ac3) )

	ROM_REGION( 0x0e00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "240.v1", 0x000000, 0x400000, CRC(f796265a) SHA1(736dff37eb91fc856b4d189249fb0de9b6c0813a) )
	ROM_LOAD( "240.v2", 0x400000, 0x400000, CRC(2cb3f3bb) SHA1(697e677890892f4b028c9a27c66809ca0a8a9b18) )
	ROM_LOAD( "240.v3", 0x800000, 0x400000, CRC(8fe1367a) SHA1(093d7a4ac2b54ad7ffb2dc316fe29415f7a99535) )
	ROM_LOAD( "240.v4", 0xc00000, 0x200000, CRC(996704d8) SHA1(0bf7a1d0660199dedf3c25be757eeab75cc6147e) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "240.c1", 0x0000000, 0x800000, CRC(effac504) SHA1(e36a96e7369b02c7e839b5abf3c6799453ba1927) )
	ROM_LOAD16_BYTE( "240.c2", 0x0000001, 0x800000, CRC(ed182d44) SHA1(a9fc0a3a786bf067c129ec7220df65953dff804f) )
	ROM_LOAD16_BYTE( "240.c3", 0x1000000, 0x800000, CRC(22e0330a) SHA1(0fe7f6a8aeba7f17dbb278e85003969ff10d3cd2) )
	ROM_LOAD16_BYTE( "240.c4", 0x1000001, 0x800000, CRC(c19a07eb) SHA1(139eac8b51cadf328dd42d8109f4e2463f57230c) )
	ROM_LOAD16_BYTE( "240.c5", 0x2000000, 0x800000, CRC(244dff5a) SHA1(156548156d3ceaa808d0053d0749af2526a3943e) )
	ROM_LOAD16_BYTE( "240.c6", 0x2000001, 0x800000, CRC(4609e507) SHA1(bb17f50a377dddb77c1eeda5944a7bcbf0cca5f7) )
ROM_END

ROM_START( rbff2k ) /* KOREAN VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "140k.p1", 0x000000, 0x100000, CRC(965edee1) SHA1(7f4b947b19ccfee32fc73e4fd89645eb313b5c77) )
	ROM_LOAD16_WORD_SWAP( "240.p2", 0x100000, 0x400000, CRC(960aa88d) SHA1(3d9e785891871af90313f178dca2724633406674) )

	NEO_SFIX_128K( "240.s1", CRC(da3b40de) SHA1(e6bf74e057ac6fe1f249a7547f13ba7fbc694561) )

	NEO_BIOS_AUDIO_256K( "240.m1", CRC(ed482791) SHA1(1f54a45967cb7842c33aa24be322c9f33ff75ac3) )

	ROM_REGION( 0x0e00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "240.v1", 0x000000, 0x400000, CRC(f796265a) SHA1(736dff37eb91fc856b4d189249fb0de9b6c0813a) )
	ROM_LOAD( "240.v2", 0x400000, 0x400000, CRC(2cb3f3bb) SHA1(697e677890892f4b028c9a27c66809ca0a8a9b18) )
	ROM_LOAD( "240.v3", 0x800000, 0x400000, CRC(8fe1367a) SHA1(093d7a4ac2b54ad7ffb2dc316fe29415f7a99535) )
	ROM_LOAD( "240.v4", 0xc00000, 0x200000, CRC(996704d8) SHA1(0bf7a1d0660199dedf3c25be757eeab75cc6147e) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "240.c1", 0x0000000, 0x800000, CRC(effac504) SHA1(e36a96e7369b02c7e839b5abf3c6799453ba1927) )
	ROM_LOAD16_BYTE( "240.c2", 0x0000001, 0x800000, CRC(ed182d44) SHA1(a9fc0a3a786bf067c129ec7220df65953dff804f) )
	ROM_LOAD16_BYTE( "240.c3", 0x1000000, 0x800000, CRC(22e0330a) SHA1(0fe7f6a8aeba7f17dbb278e85003969ff10d3cd2) )
	ROM_LOAD16_BYTE( "240.c4", 0x1000001, 0x800000, CRC(c19a07eb) SHA1(139eac8b51cadf328dd42d8109f4e2463f57230c) )
	ROM_LOAD16_BYTE( "240.c5", 0x2000000, 0x800000, CRC(244dff5a) SHA1(156548156d3ceaa808d0053d0749af2526a3943e) )
	ROM_LOAD16_BYTE( "240.c6", 0x2000001, 0x800000, CRC(4609e507) SHA1(bb17f50a377dddb77c1eeda5944a7bcbf0cca5f7) )
ROM_END

/****************************************
 ID-0241
 . NGM-2410
 NEO-MVS PROGBK1 / NEO-MVS CHA512Y
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 . NGH-2410
 NEO-AEG PROGBK1Y / NEO-AEG CHA512Y
****************************************/

ROM_START( mslug2 ) /* MVS AND AES VERSION */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "241.p1",  0x000000, 0x100000, CRC(2a53c5da) SHA1(5a6aba482cac588a6c2c51179c95b487c6e11899) )
	ROM_LOAD16_WORD_SWAP( "241.p2", 0x100000, 0x200000, CRC(38883f44) SHA1(fcf34b8c6e37774741542393b963635412484a27) )

	NEO_SFIX_128K( "241.s1", CRC(f3d32f0f) SHA1(2dc38b7dfd3ff14f64d5c0733c510b6bb8c692d0) )

	NEO_BIOS_AUDIO_128K( "241.m1", CRC(94520ebd) SHA1(f8a1551cebcb91e416f30f50581feed7f72899e9) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "241.v1", 0x000000, 0x400000, CRC(99ec20e8) SHA1(80597707f1fe115eed1941bb0701fc00790ad504) )
	ROM_LOAD( "241.v2", 0x400000, 0x400000, CRC(ecb16799) SHA1(b4b4ddc680836ed55942c66d7dfe756314e02211) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "241.c1", 0x0000000, 0x800000, CRC(394b5e0d) SHA1(4549926f5054ee6aa7689cf920be0327e3908a50) )
	ROM_LOAD16_BYTE( "241.c2", 0x0000001, 0x800000, CRC(e5806221) SHA1(1e5475cfab129c77acc610f09369ca42ba5aafa5) )
	ROM_LOAD16_BYTE( "241.c3", 0x1000000, 0x800000, CRC(9f6bfa6f) SHA1(a4319b48004e723f81a980887678e3e296049a53) )
	ROM_LOAD16_BYTE( "241.c4", 0x1000001, 0x800000, CRC(7d3e306f) SHA1(1499316fb381775218d897b81a6a0c3465d1a37c) )
ROM_END

/****************************************
 ID-0242
 . NGM-2420
 NEO-MVS PROGSF1 (1998.6.17) (protected board) / NEO-MVS CHA512Y
 NEO-MVS PROGSF1E (1998.6.18) (protected board) / NEO-MVS CHA512Y
 NEO-MVS PROGBK1 / NEO-MVS CHA512Y
 . NGH-2420
 NEO-AEG PROGBK1Y / NEO-AEG CHA512Y
****************************************/

ROM_START( kof98 ) /* encrypted code + protection */ /* MVS VERSION */
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "242.p1",  0x000000, 0x200000, CRC(8893df89) SHA1(0452828785110601c65f667209fc2d2926cd3751) )
	ROM_LOAD16_WORD_SWAP( "242.p2", 0x200000, 0x400000, CRC(980aba4c) SHA1(5e735929ec6c3ca5b2efae3c7de47bcbb8ade2c5) )

	NEO_SFIX_128K( "242.s1", CRC(7f7b4805) SHA1(80ee6e5d0ece9c34ebca54b043a7cb33f9ff6b92) )

	NEO_BIOS_AUDIO_256K( "242.m1", CRC(4ef7016b) SHA1(4182235e963bd70d398a79abeb54ab4d62887c48) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "242.v1", 0x000000, 0x400000, CRC(b9ea8051) SHA1(49606f64eb249263b3341b4f50cc1763c390b2af) )
	ROM_LOAD( "242.v2", 0x400000, 0x400000, CRC(cc11106e) SHA1(d3108bc05c9bf041d4236b2fa0c66b013aa8db1b) )
	ROM_LOAD( "242.v3", 0x800000, 0x400000, CRC(044ea4e1) SHA1(062a2f2e52098d73bc31c9ad66f5db8080395ce8) )
	ROM_LOAD( "242.v4", 0xc00000, 0x400000, CRC(7985ea30) SHA1(54ed5f0324de6164ea81943ebccb3e8d298368ec) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "242.c1", 0x0000000, 0x800000, CRC(e564ecd6) SHA1(78f22787a204f26bae9b2b1c945ddbc27143352f) )
	ROM_LOAD16_BYTE( "242.c2", 0x0000001, 0x800000, CRC(bd959b60) SHA1(2c97c59e77c9a3fe7d664e741d37944f3d56c10b) )
	ROM_LOAD16_BYTE( "242.c3", 0x1000000, 0x800000, CRC(22127b4f) SHA1(bd0d00f889d9da7c6ac48f287d9ed8c605ae22cf) )
	ROM_LOAD16_BYTE( "242.c4", 0x1000001, 0x800000, CRC(0b4fa044) SHA1(fa13c3764fae6b035a626601bc43629f1ebaaffd) )
	ROM_LOAD16_BYTE( "242.c5", 0x2000000, 0x800000, CRC(9d10bed3) SHA1(4d44addc7c808649bfb03ec45fb9529da413adff) )
	ROM_LOAD16_BYTE( "242.c6", 0x2000001, 0x800000, CRC(da07b6a2) SHA1(9c3f0da7cde1ffa8feca89efc88f07096e502acf) )
	ROM_LOAD16_BYTE( "242.c7", 0x3000000, 0x800000, CRC(f6d7a38a) SHA1(dd295d974dd4a7e5cb26a3ef3febcd03f28d522b) )
	ROM_LOAD16_BYTE( "242.c8", 0x3000001, 0x800000, CRC(c823e045) SHA1(886fbf64bcb58bc4eabb1fc9262f6ac9901a0f28) )
ROM_END

ROM_START( kof98a ) /* encrypted code + protection */ /* MVS VERSION */
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "242.p1",   0x000000, 0x200000, CRC(8893df89) SHA1(0452828785110601c65f667209fc2d2926cd3751) )
	ROM_LOAD16_WORD_SWAP( "242a.p2", 0x200000, 0x200000, CRC(3f74a000) SHA1(e887e0ac232683bd28703e08c4055fd0ea36402c) )
	ROM_LOAD16_WORD_SWAP( "242a.p3", 0x400000, 0x200000, CRC(6e474841) SHA1(0ce401277f9c53435ea00b930efe361c8d25a7d9) )

	NEO_SFIX_128K( "242.s1", CRC(7f7b4805) SHA1(80ee6e5d0ece9c34ebca54b043a7cb33f9ff6b92) )

	NEO_BIOS_AUDIO_256K( "242.m1", CRC(4ef7016b) SHA1(4182235e963bd70d398a79abeb54ab4d62887c48) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "242.v1", 0x000000, 0x400000, CRC(b9ea8051) SHA1(49606f64eb249263b3341b4f50cc1763c390b2af) )
	ROM_LOAD( "242.v2", 0x400000, 0x400000, CRC(cc11106e) SHA1(d3108bc05c9bf041d4236b2fa0c66b013aa8db1b) )
	ROM_LOAD( "242.v3", 0x800000, 0x400000, CRC(044ea4e1) SHA1(062a2f2e52098d73bc31c9ad66f5db8080395ce8) )
	ROM_LOAD( "242.v4", 0xc00000, 0x400000, CRC(7985ea30) SHA1(54ed5f0324de6164ea81943ebccb3e8d298368ec) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "242.c1", 0x0000000, 0x800000, CRC(e564ecd6) SHA1(78f22787a204f26bae9b2b1c945ddbc27143352f) )
	ROM_LOAD16_BYTE( "242.c2", 0x0000001, 0x800000, CRC(bd959b60) SHA1(2c97c59e77c9a3fe7d664e741d37944f3d56c10b) )
	ROM_LOAD16_BYTE( "242.c3", 0x1000000, 0x800000, CRC(22127b4f) SHA1(bd0d00f889d9da7c6ac48f287d9ed8c605ae22cf) )
	ROM_LOAD16_BYTE( "242.c4", 0x1000001, 0x800000, CRC(0b4fa044) SHA1(fa13c3764fae6b035a626601bc43629f1ebaaffd) )
	ROM_LOAD16_BYTE( "242.c5", 0x2000000, 0x800000, CRC(9d10bed3) SHA1(4d44addc7c808649bfb03ec45fb9529da413adff) )
	ROM_LOAD16_BYTE( "242.c6", 0x2000001, 0x800000, CRC(da07b6a2) SHA1(9c3f0da7cde1ffa8feca89efc88f07096e502acf) )
	ROM_LOAD16_BYTE( "242.c7", 0x3000000, 0x800000, CRC(f6d7a38a) SHA1(dd295d974dd4a7e5cb26a3ef3febcd03f28d522b) )
	ROM_LOAD16_BYTE( "242.c8", 0x3000001, 0x800000, CRC(c823e045) SHA1(886fbf64bcb58bc4eabb1fc9262f6ac9901a0f28) )
ROM_END

ROM_START( kof98k ) /* encrypted code + protection, only z80 rom is different to kof98 */ /* KOREAN VERSION */
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "242.p1",  0x000000, 0x200000, CRC(8893df89) SHA1(0452828785110601c65f667209fc2d2926cd3751) )
	ROM_LOAD16_WORD_SWAP( "242.p2", 0x200000, 0x400000, CRC(980aba4c) SHA1(5e735929ec6c3ca5b2efae3c7de47bcbb8ade2c5) )

	NEO_SFIX_128K( "242.s1", CRC(7f7b4805) SHA1(80ee6e5d0ece9c34ebca54b043a7cb33f9ff6b92) )

	/* Correct chip label */
	NEO_BIOS_AUDIO_256K( "242k.m1", CRC(ce12da0c) SHA1(e7c01dae2852d543d1a58d55735239f6a5aa05a5) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "242.v1", 0x000000, 0x400000, CRC(b9ea8051) SHA1(49606f64eb249263b3341b4f50cc1763c390b2af) )
	ROM_LOAD( "242.v2", 0x400000, 0x400000, CRC(cc11106e) SHA1(d3108bc05c9bf041d4236b2fa0c66b013aa8db1b) )
	ROM_LOAD( "242.v3", 0x800000, 0x400000, CRC(044ea4e1) SHA1(062a2f2e52098d73bc31c9ad66f5db8080395ce8) )
	ROM_LOAD( "242.v4", 0xc00000, 0x400000, CRC(7985ea30) SHA1(54ed5f0324de6164ea81943ebccb3e8d298368ec) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "242.c1", 0x0000000, 0x800000, CRC(e564ecd6) SHA1(78f22787a204f26bae9b2b1c945ddbc27143352f) )
	ROM_LOAD16_BYTE( "242.c2", 0x0000001, 0x800000, CRC(bd959b60) SHA1(2c97c59e77c9a3fe7d664e741d37944f3d56c10b) )
	ROM_LOAD16_BYTE( "242.c3", 0x1000000, 0x800000, CRC(22127b4f) SHA1(bd0d00f889d9da7c6ac48f287d9ed8c605ae22cf) )
	ROM_LOAD16_BYTE( "242.c4", 0x1000001, 0x800000, CRC(0b4fa044) SHA1(fa13c3764fae6b035a626601bc43629f1ebaaffd) )
	ROM_LOAD16_BYTE( "242.c5", 0x2000000, 0x800000, CRC(9d10bed3) SHA1(4d44addc7c808649bfb03ec45fb9529da413adff) )
	ROM_LOAD16_BYTE( "242.c6", 0x2000001, 0x800000, CRC(da07b6a2) SHA1(9c3f0da7cde1ffa8feca89efc88f07096e502acf) )
	ROM_LOAD16_BYTE( "242.c7", 0x3000000, 0x800000, CRC(f6d7a38a) SHA1(dd295d974dd4a7e5cb26a3ef3febcd03f28d522b) )
	ROM_LOAD16_BYTE( "242.c8", 0x3000001, 0x800000, CRC(c823e045) SHA1(886fbf64bcb58bc4eabb1fc9262f6ac9901a0f28) )
ROM_END

ROM_START( kof98ka ) /* encrypted code + protection, only z80 rom is different to kof98 */ /* KOREAN VERSION */
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "242.p1",  0x000000, 0x200000, CRC(8893df89) SHA1(0452828785110601c65f667209fc2d2926cd3751) )
	ROM_LOAD16_WORD_SWAP( "242.p2", 0x200000, 0x400000, CRC(980aba4c) SHA1(5e735929ec6c3ca5b2efae3c7de47bcbb8ade2c5) )

	NEO_SFIX_128K( "242.s1", CRC(7f7b4805) SHA1(80ee6e5d0ece9c34ebca54b043a7cb33f9ff6b92) )

	NEO_BIOS_AUDIO_256K( "242ka.m1", CRC(ce9fb07c) SHA1(631d995f1291dd803fb069f3b25e7b9ed30d8649) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "242.v1", 0x000000, 0x400000, CRC(b9ea8051) SHA1(49606f64eb249263b3341b4f50cc1763c390b2af) )
	ROM_LOAD( "242.v2", 0x400000, 0x400000, CRC(cc11106e) SHA1(d3108bc05c9bf041d4236b2fa0c66b013aa8db1b) )
	ROM_LOAD( "242.v3", 0x800000, 0x400000, CRC(044ea4e1) SHA1(062a2f2e52098d73bc31c9ad66f5db8080395ce8) )
	ROM_LOAD( "242.v4", 0xc00000, 0x400000, CRC(7985ea30) SHA1(54ed5f0324de6164ea81943ebccb3e8d298368ec) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "242.c1", 0x0000000, 0x800000, CRC(e564ecd6) SHA1(78f22787a204f26bae9b2b1c945ddbc27143352f) )
	ROM_LOAD16_BYTE( "242.c2", 0x0000001, 0x800000, CRC(bd959b60) SHA1(2c97c59e77c9a3fe7d664e741d37944f3d56c10b) )
	ROM_LOAD16_BYTE( "242.c3", 0x1000000, 0x800000, CRC(22127b4f) SHA1(bd0d00f889d9da7c6ac48f287d9ed8c605ae22cf) )
	ROM_LOAD16_BYTE( "242.c4", 0x1000001, 0x800000, CRC(0b4fa044) SHA1(fa13c3764fae6b035a626601bc43629f1ebaaffd) )
	ROM_LOAD16_BYTE( "242.c5", 0x2000000, 0x800000, CRC(9d10bed3) SHA1(4d44addc7c808649bfb03ec45fb9529da413adff) )
	ROM_LOAD16_BYTE( "242.c6", 0x2000001, 0x800000, CRC(da07b6a2) SHA1(9c3f0da7cde1ffa8feca89efc88f07096e502acf) )
	ROM_LOAD16_BYTE( "242.c7", 0x3000000, 0x800000, CRC(f6d7a38a) SHA1(dd295d974dd4a7e5cb26a3ef3febcd03f28d522b) )
	ROM_LOAD16_BYTE( "242.c8", 0x3000001, 0x800000, CRC(c823e045) SHA1(886fbf64bcb58bc4eabb1fc9262f6ac9901a0f28) )
ROM_END

ROM_START( kof98h ) /* MVS AND AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "242h.p1", 0x000000, 0x100000, CRC(61ac868a) SHA1(26577264aa72d6af272952a876fcd3775f53e3fa) )
	ROM_LOAD16_WORD_SWAP( "242.p2", 0x100000, 0x400000, CRC(980aba4c) SHA1(5e735929ec6c3ca5b2efae3c7de47bcbb8ade2c5) )

	NEO_SFIX_128K( "242.s1", CRC(7f7b4805) SHA1(80ee6e5d0ece9c34ebca54b043a7cb33f9ff6b92) )

	NEO_BIOS_AUDIO_256K( "242-mg1.m1", CRC(4e7a6b1b) SHA1(b54d08f88713ed0271aa06f9f7c9c572ef555b1a) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "242.v1", 0x000000, 0x400000, CRC(b9ea8051) SHA1(49606f64eb249263b3341b4f50cc1763c390b2af) )
	ROM_LOAD( "242.v2", 0x400000, 0x400000, CRC(cc11106e) SHA1(d3108bc05c9bf041d4236b2fa0c66b013aa8db1b) )
	ROM_LOAD( "242.v3", 0x800000, 0x400000, CRC(044ea4e1) SHA1(062a2f2e52098d73bc31c9ad66f5db8080395ce8) )
	ROM_LOAD( "242.v4", 0xc00000, 0x400000, CRC(7985ea30) SHA1(54ed5f0324de6164ea81943ebccb3e8d298368ec) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "242.c1", 0x0000000, 0x800000, CRC(e564ecd6) SHA1(78f22787a204f26bae9b2b1c945ddbc27143352f) )
	ROM_LOAD16_BYTE( "242.c2", 0x0000001, 0x800000, CRC(bd959b60) SHA1(2c97c59e77c9a3fe7d664e741d37944f3d56c10b) )
	ROM_LOAD16_BYTE( "242.c3", 0x1000000, 0x800000, CRC(22127b4f) SHA1(bd0d00f889d9da7c6ac48f287d9ed8c605ae22cf) )
	ROM_LOAD16_BYTE( "242.c4", 0x1000001, 0x800000, CRC(0b4fa044) SHA1(fa13c3764fae6b035a626601bc43629f1ebaaffd) )
	ROM_LOAD16_BYTE( "242.c5", 0x2000000, 0x800000, CRC(9d10bed3) SHA1(4d44addc7c808649bfb03ec45fb9529da413adff) )
	ROM_LOAD16_BYTE( "242.c6", 0x2000001, 0x800000, CRC(da07b6a2) SHA1(9c3f0da7cde1ffa8feca89efc88f07096e502acf) )
	ROM_LOAD16_BYTE( "242.c7", 0x3000000, 0x800000, CRC(f6d7a38a) SHA1(dd295d974dd4a7e5cb26a3ef3febcd03f28d522b) )
	ROM_LOAD16_BYTE( "242.c8", 0x3000001, 0x800000, CRC(c823e045) SHA1(886fbf64bcb58bc4eabb1fc9262f6ac9901a0f28) )
ROM_END

/****************************************
 ID-0243
 . NGM-2430
 NEO-MVS PROGBK1 / NEO-MVS CHA512Y
 . NGH-2430
 NEO-AEG PROGBK1Y / NEO-AEG CHA512Y
****************************************/

ROM_START( lastbld2 ) /* MVS AND AES VERSION */ /* later revision */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "243.p1",  0x000000, 0x100000, CRC(af1e6554) SHA1(bd8526f60c2472937728a5d933fbd19d899f2cba) )
	ROM_LOAD16_WORD_SWAP( "243.p2", 0x100000, 0x400000, CRC(add4a30b) SHA1(7db62564db49fe0218cbb35b119d62582a24d658) )

	NEO_SFIX_128K( "243.s1", CRC(c9cd2298) SHA1(a9a18b5347f9dbe29a2ccb63fd4c8fd19537bf8b) )

	NEO_BIOS_AUDIO_128K( "243.m1", CRC(acf12d10) SHA1(6e6b98cc1fa44f24a5168877559b0055e6957b60) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "243.v1", 0x000000, 0x400000, CRC(f7ee6fbb) SHA1(55137bcabeeb590e40a9b8a7c07dd106e4d12a90) )
	ROM_LOAD( "243.v2", 0x400000, 0x400000, CRC(aa9e4df6) SHA1(a0b91f63e2552a8ad9e0d1af00e2c38288637161) )
	ROM_LOAD( "243.v3", 0x800000, 0x400000, CRC(4ac750b2) SHA1(585a154acc67bd84ea5b944686b78ed082b768d9) )
	ROM_LOAD( "243.v4", 0xc00000, 0x400000, CRC(f5c64ba6) SHA1(2eac455def8c27090862cc042f65a3a8aad88283) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "243.c1", 0x0000000, 0x800000, CRC(5839444d) SHA1(0616921c4cce20422563578bd0e806d359508599) )
	ROM_LOAD16_BYTE( "243.c2", 0x0000001, 0x800000, CRC(dd087428) SHA1(ca27fdb60425664956a18c021ea465f452fb1527) )
	ROM_LOAD16_BYTE( "243.c3", 0x1000000, 0x800000, CRC(6054cbe0) SHA1(ec2f65e9c930250ee25fd064ee5ae76a7a9c61d9) )
	ROM_LOAD16_BYTE( "243.c4", 0x1000001, 0x800000, CRC(8bd2a9d2) SHA1(0935df65cd2b0891a708bcc0f1c188148058d4b5) )
	ROM_LOAD16_BYTE( "243.c5", 0x2000000, 0x800000, CRC(6a503dcf) SHA1(23241b16d7e20f923d41186b29487ab922c7f530) )
	ROM_LOAD16_BYTE( "243.c6", 0x2000001, 0x800000, CRC(ec9c36d0) SHA1(e145e9e359000dda6e1dfe95a996bc6d29cfca21) )
ROM_END

/****************************************
 ID-0244
 . ??M-2440
 NEO-MVS PROGBK1 / NEO-MVS CHA512Y
 . ??H-2440
****************************************/

ROM_START( neocup98 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "244.p1", 0x100000, 0x100000, CRC(f8fdb7a5) SHA1(f34ee5d1c24e70427d05ef488f46906dbd9f9950) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "244.s1", CRC(9bddb697) SHA1(2f479bcd5a433201168792a578de3057252d649f) )

	NEO_BIOS_AUDIO_128K( "244.m1", CRC(a701b276) SHA1(055550ebc650835bcf8ea4457b2c91bd73e21281) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "244.v1", 0x000000, 0x400000, CRC(79def46d) SHA1(63414235de2e177654508f1c840040424f8993e6) )
	ROM_LOAD( "244.v2", 0x400000, 0x200000, CRC(b231902f) SHA1(9209772e947a2c7ac31b49dd613bf2eab0cb3358) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "244.c1", 0x000000, 0x800000, CRC(c7a62b23) SHA1(4534ecc9ade69c543188c66229dcad89dbc48668) )
	ROM_LOAD16_BYTE( "244.c2", 0x000001, 0x800000, CRC(33aa0f35) SHA1(3443c7765c6aa177003d42bbfcac9f31d1e12575) )
ROM_END

/****************************************
 ID-0245
 . ??M-2450
 NEO-MVS PROGBK1 / NEO-MVS CHA512Y
****************************************/

ROM_START( breakrev ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "245.p1", 0x100000, 0x100000, CRC(c828876d) SHA1(1dcba850e5cf8219d0945612cfded6d20ca8682a) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "245.s1", CRC(e7660a5d) SHA1(1cd54964ba60b245ea57d9daf0e27b572b815d21) )

	NEO_BIOS_AUDIO_128K( "245.m1", CRC(00f31c66) SHA1(8488598415c9b74bce00e05b31d96e3d1625c20d) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "245.v1", 0x000000, 0x400000, CRC(e255446c) SHA1(b3933340d49d4ba581f3bf1af7ad69d786205790) )
	ROM_LOAD( "245.v2", 0x400000, 0x400000, CRC(9068198a) SHA1(71819b0475a5e173a2f9a6e4ff19a94655141c3c) )

	ROM_REGION( 0x1800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "245.c1", 0x0000000, 0x400000, CRC(68d4ae76) SHA1(2e820067f6963669f104bebf19e865fe4127b4dd) )
	ROM_LOAD16_BYTE( "245.c2", 0x0000001, 0x400000, CRC(fdee05cd) SHA1(efc4ffd790953ac7c25d5f045c64a9b49d24b096) )
	ROM_LOAD16_BYTE( "245.c3", 0x0800000, 0x400000, CRC(645077f3) SHA1(0ae74f3b4b3b88f128c6d8c0f35ffa53f5d67ef2) )
	ROM_LOAD16_BYTE( "245.c4", 0x0800001, 0x400000, CRC(63aeb74c) SHA1(9ff6930c0c3d79b46b86356e8565ce4fcd69ac38) )
	ROM_LOAD16_BYTE( "245.c5", 0x1000000, 0x400000, CRC(b5f40e7f) SHA1(b332bac64dbb9a9dd66c5315f47ea08634d36f45) )
	ROM_LOAD16_BYTE( "245.c6", 0x1000001, 0x400000, CRC(d0337328) SHA1(dff86b75dc283bd4512557a5c64f16e6be6c16e4) )
ROM_END

/****************************************
 ID-0246
 . NGM-2460
 NEO-MVS PROGBK1 / NEO-MVS CHA512Y
 . NGH-2460
****************************************/

ROM_START( shocktr2 )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "246.p1",  0x000000, 0x100000, CRC(6d4b7781) SHA1(3c9d53d5da9842bfd45037c919064dda3fb2e089) )
	ROM_LOAD16_WORD_SWAP( "246.p2", 0x100000, 0x400000, CRC(72ea04c3) SHA1(4fb1d22c30f5f3db4637dd92a4d2705c88de399d) )

	NEO_SFIX_128K( "246.s1", CRC(2a360637) SHA1(431b43da5377dd189e51bd93d88d8a24d1b5090a) )

	NEO_BIOS_AUDIO_128K( "246.m1", CRC(d0604ad1) SHA1(fae3cd52a177eadd5f5775ace957cc0f8301e65d) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "246.v1", 0x000000, 0x400000, CRC(16986fc6) SHA1(cff3103dadf2f4390460456a5bd3fb5f28e21f6a) )
	ROM_LOAD( "246.v2", 0x400000, 0x400000, CRC(ada41e83) SHA1(78e37ffaaa5679c8775a3a71f6df7a0d15082bdc) )
	ROM_LOAD( "246.v3", 0x800000, 0x200000, CRC(a05ba5db) SHA1(09d739cad323d918f4196f91b654627fcafd8f4d) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "246.c1", 0x0000000, 0x800000, CRC(47ac9ec5) SHA1(2d9eea11ba87baa23b18a1a3f607dc137846e807) )
	ROM_LOAD16_BYTE( "246.c2", 0x0000001, 0x800000, CRC(7bcab64f) SHA1(08d0edddd14b53d606e9a7a46aa4fb4e7398e0d0) )
	ROM_LOAD16_BYTE( "246.c3", 0x1000000, 0x800000, CRC(db2f73e8) SHA1(8d0c3473a8b2a4e28fed1b74beb2e025b7e61867) )
	ROM_LOAD16_BYTE( "246.c4", 0x1000001, 0x800000, CRC(5503854e) SHA1(a0f2e7c609cbb2aa43493a39d7dcaeca3d511d26) )
	ROM_LOAD16_BYTE( "246.c5", 0x2000000, 0x800000, CRC(055b3701) SHA1(97f5e92538d1f2e437dcb3f80e56e1230287e8d1) )
	ROM_LOAD16_BYTE( "246.c6", 0x2000001, 0x800000, CRC(7e2caae1) SHA1(d9de14e3e323664a8c5b7f1df1ba9ec7dd0e6a46) )
ROM_END

/****************************************
 ID-0247
 . ??M-2470
 NEO-MVS PROGBK1 / NEO-MVS CHA256
****************************************/

ROM_START( flipshot ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "247.p1", 0x000000, 0x100000, CRC(95779094) SHA1(a985e033bc6f137fa65855d3eed245d66d5b244a) )

	NEO_SFIX_128K( "247.s1", CRC(6300185c) SHA1(cb2f1de085fde214f96a962b1c2fa285eb387d44) )

	NEO_BIOS_AUDIO_128K( "247.m1", CRC(a9fe0144) SHA1(4cc076ecce9216a373f3dcd7ba28a03d6050e522) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "247.v1", 0x000000, 0x200000, CRC(42ec743d) SHA1(f45b5167ebcbd59300f4e5b05448cd421654102a) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "247.c1", 0x000000, 0x200000, CRC(c9eedcb2) SHA1(7627f2810322c146511525eb70b573a6a5ede926) )
	ROM_LOAD16_BYTE( "247.c2", 0x000001, 0x200000, CRC(7d6d6e87) SHA1(6475b58b9f91c20d1f465f3e892de0c68e12a92b) )
ROM_END

/****************************************
 ID-0248
 . ??M-2480
 NEO-MVS PROGBK1 / NEO-MVS CHA256
****************************************/

ROM_START( pbobbl2n ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "248.p1", 0x000000, 0x100000, CRC(9d6c0754) SHA1(95c70c2d51fc4de01e768e03cc800a850aaad5dc) )

	NEO_SFIX_128K( "248.s1", CRC(0a3fee41) SHA1(0ab2120e462086be942efcf6ffb37f58ea966ca3) )

	NEO_BIOS_AUDIO_128K( "248.m1", CRC(883097a9) SHA1(677bf9684c0c7977a9a3f0c1288e430040a53b49) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "248.v1", 0x000000, 0x400000, CRC(57fde1fa) SHA1(af39bc141fc35b78dcacfd42b3abb29d7e5c2c89) )
	ROM_LOAD( "248.v2", 0x400000, 0x400000, CRC(4b966ef3) SHA1(083c0e9fd7b8e506087648cdd8ec4206103984cd) )

	ROM_REGION( 0xa00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "248.c1", 0x000000, 0x400000, CRC(d9115327) SHA1(a49aa836a902326cfe785428e1699fefcf8566d4) )
	ROM_LOAD16_BYTE( "248.c2", 0x000001, 0x400000, CRC(77f9fdac) SHA1(4642d71d32b6a05dc8bfa0f95c936a77c7cef05e) )
	ROM_LOAD16_BYTE( "248.c3", 0x800000, 0x100000, CRC(8890bf7c) SHA1(a52f6bafd60e72003bfe38c80c1dde24b4983b2a) )
	ROM_LOAD16_BYTE( "248.c4", 0x800001, 0x100000, CRC(8efead3f) SHA1(f577d2f7c6f850b3d100c36947ad15e33dfa0bed) )
ROM_END

/****************************************
 ID-0249
 . ??M-2490
 NEO-MVS PROGBK1 / NEO-MVS CHA256
 NEO-MVS PROGBK1 / NEO-MVS CHA512Y
****************************************/

ROM_START( ctomaday ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "249.p1", 0x100000, 0x100000, CRC(c9386118) SHA1(5554662c7bc8605889cac4a67fee05bbb4eb786f) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "249.s1", CRC(dc9eb372) SHA1(b8aa142243ba303799554479bfc88eb49260f3b1) )

	NEO_BIOS_AUDIO_128K( "249.m1", CRC(80328a47) SHA1(34b6b1a81eab1cf38834b2eea55454ce1b6100e2) )

	ROM_REGION( 0x500000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "249.v1", 0x000000, 0x400000, CRC(de7c8f27) SHA1(3681a68a702ab5da8f509b8301d6cada75959332) )
	ROM_LOAD( "249.v2", 0x400000, 0x100000, CRC(c8e40119) SHA1(738f525c381ed68c0b8a89318a3e4d0089473c45) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "249.c1", 0x000000, 0x400000, CRC(041fb8ee) SHA1(dacc84d713d76818d89a26358374afaa22fa82a2) )
	ROM_LOAD16_BYTE( "249.c2", 0x000001, 0x400000, CRC(74f3cdf4) SHA1(55ddabaf77f4d575f4deb24fe63e4bdc2c6f31e1) )
ROM_END

/****************************************
 ID-0250
 . NGM-2500
 NEO-MVS PROGEOP (1999.2.2) / NEO-MVS CHA512Y
 . NGH-2500
 NEO-AEG PROGEOP (1999.4.2) / NEO-AEG CHA512Y
****************************************/

ROM_START( mslugx ) /* MVS AND AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "250.p1",  0x000000, 0x100000, CRC(81f1f60b) SHA1(4c19f2e9824e606178ac1c9d4b0516fbaa625035) )
	ROM_LOAD16_WORD_SWAP( "250.p2", 0x100000, 0x400000, CRC(1fda2e12) SHA1(18aaa7a3ba8da99f78c430e9be69ccde04bc04d9) )

	NEO_SFIX_128K( "250.s1", CRC(fb6f441d) SHA1(2cc392ecde5d5afb28ddbaa1030552b48571dcfb) )

	NEO_BIOS_AUDIO_128K( "250.m1", CRC(fd42a842) SHA1(55769bad4860f64ef53a333e0da9e073db483d6a) )

	ROM_REGION( 0xa00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "250.v1", 0x000000, 0x400000, CRC(c79ede73) SHA1(ebfcc67204ff9677cf7972fd5b6b7faabf07280c) )
	ROM_LOAD( "250.v2", 0x400000, 0x400000, CRC(ea9aabe1) SHA1(526c42ca9a388f7435569400e2f132e2724c71ff) )
	ROM_LOAD( "250.v3", 0x800000, 0x200000, CRC(2ca65102) SHA1(45979d1edb1fc774a415d9386f98d7cb252a2043) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "250.c1", 0x0000000, 0x800000, CRC(09a52c6f) SHA1(c3e8a8ccdac0f8bddc4c3413277626532405fae2) )
	ROM_LOAD16_BYTE( "250.c2", 0x0000001, 0x800000, CRC(31679821) SHA1(554f600a3aa09c16c13c625299b087a79d0d15c5) )
	ROM_LOAD16_BYTE( "250.c3", 0x1000000, 0x800000, CRC(fd602019) SHA1(c56646c62387bc1439d46610258c755beb8d7dd8) )
	ROM_LOAD16_BYTE( "250.c4", 0x1000001, 0x800000, CRC(31354513) SHA1(31be8ea2498001f68ce4b06b8b90acbf2dcab6af) )
	ROM_LOAD16_BYTE( "250.c5", 0x2000000, 0x800000, CRC(a4b56124) SHA1(d41069856df990a1a99d39fb263c8303389d5475) )
	ROM_LOAD16_BYTE( "250.c6", 0x2000001, 0x800000, CRC(83e3e69d) SHA1(39be66287696829d243fb71b3fb8b7dc2bc3298f) )
ROM_END

/****************************************
 ID-0251
 . NGM-2510
 SMA protected version found on:
 NEO-MVS PROGLBA (NEO-SMA) (1999.4.12) / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7042)
 Non SMA protected version found on:
 NEO-MVS PROGBK1 / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7042)
 . NGH-2510
 NEO-AEG PROGLBA (NEO-SMA) (1999.7.6) / NEO-AEG CHAFIO (1999.8.10) (NEO-CMC 7042)
****************************************/

ROM_START( kof99 ) /* Original Version - Encrypted Code & GFX */ /* MVS VERSION */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ka.neo-sma", 0x0c0000, 0x040000, CRC(7766d09e) SHA1(4e0a49d1ad669a62676cb30f527c6590cde80194) )
	ROM_LOAD16_WORD_SWAP( "251.p1",  0x100000, 0x400000, CRC(006e4532) SHA1(47791ab4044ad55988b1d3412d95b65b91a163c8) )
	ROM_LOAD16_WORD_SWAP( "251.p2",  0x500000, 0x400000, CRC(90175f15) SHA1(aa9e75810438a8b45808a8bf32cb04d91b5c0b3a) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_128K( "251.m1", CRC(5e74539c) SHA1(6f49a9343cbd026b2c6720ff3fa2e5b1f85e80da) )

	ROM_REGION( 0x0e00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "251.v1", 0x000000, 0x400000, CRC(ef2eecc8) SHA1(8ed13b9db92dba3124bc5ba66e3e275885ece24a) )
	ROM_LOAD( "251.v2", 0x400000, 0x400000, CRC(73e211ca) SHA1(0e60fa64cab6255d9721e2b4bc22e3de64c874c5) )
	ROM_LOAD( "251.v3", 0x800000, 0x400000, CRC(821901da) SHA1(c6d4975bfaa19a62ed59126cadf2578c0a5c257f) )
	ROM_LOAD( "251.v4", 0xc00000, 0x200000, CRC(b49e6178) SHA1(dde6f76e958841e8c99b693e13ced9aa9ef316dc) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "251.c1", 0x0000000, 0x800000, CRC(0f9e93fe) SHA1(c7d77f0833c6f526f632e4f2dce59e302f6b9a15) )
	ROM_LOAD16_BYTE( "251.c2", 0x0000001, 0x800000, CRC(e71e2ea3) SHA1(39c7a326fddbcca3b29c68cdc96aad4d62295c0f) )
	ROM_LOAD16_BYTE( "251.c3", 0x1000000, 0x800000, CRC(238755d2) SHA1(01125b5c7a28e350f091280b041954fd1ac7c98f) )
	ROM_LOAD16_BYTE( "251.c4", 0x1000001, 0x800000, CRC(438c8b22) SHA1(ffbc643f5b27dd00f2f95d4ef4c5f29ee814722b) )
	ROM_LOAD16_BYTE( "251.c5", 0x2000000, 0x800000, CRC(0b0abd0a) SHA1(d5ad324fe523bdc6f09209d236cc4932524a48f1) )
	ROM_LOAD16_BYTE( "251.c6", 0x2000001, 0x800000, CRC(65bbf281) SHA1(79ae174667a23dabcfe865b6cd6133c86098452e) )
	ROM_LOAD16_BYTE( "251.c7", 0x3000000, 0x800000, CRC(ff65f62e) SHA1(7cd335fede05b56e15db90ce407c1183a78da4e9) )
	ROM_LOAD16_BYTE( "251.c8", 0x3000001, 0x800000, CRC(8d921c68) SHA1(42acf1d27d52a8e3b6262eb7df50693c0b135565) )
ROM_END

ROM_START( kof99h ) /* Original Version - Encrypted Code & GFX */ /* AES VERSION */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kc.neo-sma",  0x0c0000, 0x040000, CRC(6c9d0647) SHA1(2a0ce62ca6c18007e8fbe1b60475c7874ab79389) )
	ROM_LOAD16_WORD_SWAP( "251.p1",   0x100000, 0x400000, CRC(006e4532) SHA1(47791ab4044ad55988b1d3412d95b65b91a163c8) )
	ROM_LOAD16_WORD_SWAP( "251h.p2",  0x500000, 0x400000, CRC(d9057f51) SHA1(8d365b4dd40351495df99d6c765df1434b0b0548) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_128K( "251.m1", CRC(5e74539c) SHA1(6f49a9343cbd026b2c6720ff3fa2e5b1f85e80da) )

	ROM_REGION( 0x0e00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "251.v1", 0x000000, 0x400000, CRC(ef2eecc8) SHA1(8ed13b9db92dba3124bc5ba66e3e275885ece24a) )
	ROM_LOAD( "251.v2", 0x400000, 0x400000, CRC(73e211ca) SHA1(0e60fa64cab6255d9721e2b4bc22e3de64c874c5) )
	ROM_LOAD( "251.v3", 0x800000, 0x400000, CRC(821901da) SHA1(c6d4975bfaa19a62ed59126cadf2578c0a5c257f) )
	ROM_LOAD( "251.v4", 0xc00000, 0x200000, CRC(b49e6178) SHA1(dde6f76e958841e8c99b693e13ced9aa9ef316dc) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "251.c1", 0x0000000, 0x800000, CRC(0f9e93fe) SHA1(c7d77f0833c6f526f632e4f2dce59e302f6b9a15) )
	ROM_LOAD16_BYTE( "251.c2", 0x0000001, 0x800000, CRC(e71e2ea3) SHA1(39c7a326fddbcca3b29c68cdc96aad4d62295c0f) )
	ROM_LOAD16_BYTE( "251.c3", 0x1000000, 0x800000, CRC(238755d2) SHA1(01125b5c7a28e350f091280b041954fd1ac7c98f) )
	ROM_LOAD16_BYTE( "251.c4", 0x1000001, 0x800000, CRC(438c8b22) SHA1(ffbc643f5b27dd00f2f95d4ef4c5f29ee814722b) )
	ROM_LOAD16_BYTE( "251.c5", 0x2000000, 0x800000, CRC(0b0abd0a) SHA1(d5ad324fe523bdc6f09209d236cc4932524a48f1) )
	ROM_LOAD16_BYTE( "251.c6", 0x2000001, 0x800000, CRC(65bbf281) SHA1(79ae174667a23dabcfe865b6cd6133c86098452e) )
	ROM_LOAD16_BYTE( "251.c7", 0x3000000, 0x800000, CRC(ff65f62e) SHA1(7cd335fede05b56e15db90ce407c1183a78da4e9) )
	ROM_LOAD16_BYTE( "251.c8", 0x3000001, 0x800000, CRC(8d921c68) SHA1(42acf1d27d52a8e3b6262eb7df50693c0b135565) )
ROM_END

ROM_START( kof99e ) /* Original Version - Encrypted Code & GFX */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ka.neo-sma", 0x0c0000, 0x040000, CRC(7766d09e) SHA1(4e0a49d1ad669a62676cb30f527c6590cde80194) )
	/* Is the SMA for this set correct? A set with this layout and a SMA.KB is known */
	ROM_LOAD16_WORD_SWAP( "251e.p1", 0x100000, 0x200000, CRC(1e8d692d) SHA1(eea1aa8c0a17f089ac14831889c36535e559072c) )
	ROM_LOAD16_WORD_SWAP( "251e.p2", 0x300000, 0x200000, CRC(d6206e5a) SHA1(0e1100d03c40c6d5cfa899d009e319ae73fce6b8) )
	ROM_LOAD16_WORD_SWAP( "251e.p3", 0x500000, 0x200000, CRC(d58c3ef8) SHA1(f927d90d55b49944f448d6286e0cb913cc70ade1) )
	ROM_LOAD16_WORD_SWAP( "251e.p4", 0x700000, 0x200000, CRC(52de02ae) SHA1(f16924ff8eef92da7716236a6a055e22e090a02b) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_128K( "251.m1", CRC(5e74539c) SHA1(6f49a9343cbd026b2c6720ff3fa2e5b1f85e80da) )

	ROM_REGION( 0x0e00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "251.v1", 0x000000, 0x400000, CRC(ef2eecc8) SHA1(8ed13b9db92dba3124bc5ba66e3e275885ece24a) )
	ROM_LOAD( "251.v2", 0x400000, 0x400000, CRC(73e211ca) SHA1(0e60fa64cab6255d9721e2b4bc22e3de64c874c5) )
	ROM_LOAD( "251.v3", 0x800000, 0x400000, CRC(821901da) SHA1(c6d4975bfaa19a62ed59126cadf2578c0a5c257f) )
	ROM_LOAD( "251.v4", 0xc00000, 0x200000, CRC(b49e6178) SHA1(dde6f76e958841e8c99b693e13ced9aa9ef316dc) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "251.c1", 0x0000000, 0x800000, CRC(0f9e93fe) SHA1(c7d77f0833c6f526f632e4f2dce59e302f6b9a15) )
	ROM_LOAD16_BYTE( "251.c2", 0x0000001, 0x800000, CRC(e71e2ea3) SHA1(39c7a326fddbcca3b29c68cdc96aad4d62295c0f) )
	ROM_LOAD16_BYTE( "251.c3", 0x1000000, 0x800000, CRC(238755d2) SHA1(01125b5c7a28e350f091280b041954fd1ac7c98f) )
	ROM_LOAD16_BYTE( "251.c4", 0x1000001, 0x800000, CRC(438c8b22) SHA1(ffbc643f5b27dd00f2f95d4ef4c5f29ee814722b) )
	ROM_LOAD16_BYTE( "251.c5", 0x2000000, 0x800000, CRC(0b0abd0a) SHA1(d5ad324fe523bdc6f09209d236cc4932524a48f1) )
	ROM_LOAD16_BYTE( "251.c6", 0x2000001, 0x800000, CRC(65bbf281) SHA1(79ae174667a23dabcfe865b6cd6133c86098452e) )
	ROM_LOAD16_BYTE( "251.c7", 0x3000000, 0x800000, CRC(ff65f62e) SHA1(7cd335fede05b56e15db90ce407c1183a78da4e9) )
	ROM_LOAD16_BYTE( "251.c8", 0x3000001, 0x800000, CRC(8d921c68) SHA1(42acf1d27d52a8e3b6262eb7df50693c0b135565) )
ROM_END

ROM_START( kof99ka ) /* Original Version - Encrypted GFX */ /* KOREAN VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "152.p1",  0x000000, 0x100000, CRC(f2c7ddfa) SHA1(d592eecc53d442c55c2f26a6a721fdf2924d2a5b) )
	ROM_LOAD16_WORD_SWAP( "152.p2", 0x100000, 0x400000, CRC(274ef47a) SHA1(98654b68cc85c19d4a90b46f3110f551fa2e5357) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_128K( "251.m1", CRC(5e74539c) SHA1(6f49a9343cbd026b2c6720ff3fa2e5b1f85e80da) )

	ROM_REGION( 0x0e00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "251.v1", 0x000000, 0x400000, CRC(ef2eecc8) SHA1(8ed13b9db92dba3124bc5ba66e3e275885ece24a) )
	ROM_LOAD( "251.v2", 0x400000, 0x400000, CRC(73e211ca) SHA1(0e60fa64cab6255d9721e2b4bc22e3de64c874c5) )
	ROM_LOAD( "251.v3", 0x800000, 0x400000, CRC(821901da) SHA1(c6d4975bfaa19a62ed59126cadf2578c0a5c257f) )
	ROM_LOAD( "251.v4", 0xc00000, 0x200000, CRC(b49e6178) SHA1(dde6f76e958841e8c99b693e13ced9aa9ef316dc) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "251.c1", 0x0000000, 0x800000, CRC(0f9e93fe) SHA1(c7d77f0833c6f526f632e4f2dce59e302f6b9a15) )
	ROM_LOAD16_BYTE( "251.c2", 0x0000001, 0x800000, CRC(e71e2ea3) SHA1(39c7a326fddbcca3b29c68cdc96aad4d62295c0f) )
	ROM_LOAD16_BYTE( "251.c3", 0x1000000, 0x800000, CRC(238755d2) SHA1(01125b5c7a28e350f091280b041954fd1ac7c98f) )
	ROM_LOAD16_BYTE( "251.c4", 0x1000001, 0x800000, CRC(438c8b22) SHA1(ffbc643f5b27dd00f2f95d4ef4c5f29ee814722b) )
	ROM_LOAD16_BYTE( "251.c5", 0x2000000, 0x800000, CRC(0b0abd0a) SHA1(d5ad324fe523bdc6f09209d236cc4932524a48f1) )
	ROM_LOAD16_BYTE( "251.c6", 0x2000001, 0x800000, CRC(65bbf281) SHA1(79ae174667a23dabcfe865b6cd6133c86098452e) )
	ROM_LOAD16_BYTE( "251.c7", 0x3000000, 0x800000, CRC(ff65f62e) SHA1(7cd335fede05b56e15db90ce407c1183a78da4e9) )
	ROM_LOAD16_BYTE( "251.c8", 0x3000001, 0x800000, CRC(8d921c68) SHA1(42acf1d27d52a8e3b6262eb7df50693c0b135565) )
ROM_END

ROM_START( kof99p ) /* Prototype Version - Possibly Hacked */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proto_251.p1", 0x000000, 0x100000, CRC(f37929c4) SHA1(226e7e3d629568399b88275e5bcd4e5b3839be95) )
	ROM_LOAD16_WORD_SWAP( "proto_251.p2", 0x100000, 0x400000, CRC(739742ad) SHA1(31acaf05a9bf186305888d3db7e4e8a83f7bb0a4) )

	NEO_SFIX_128K( "proto_251.s1", CRC(fb1498ed) SHA1(d40060b31b6f217a4abdf3b336439fcd7bd7aaef) )

	/* Did the Prototype really use the same sound program / voice roms, sound isn't great .. */
	NEO_BIOS_AUDIO_128K( "251.m1", CRC(5e74539c) SHA1(6f49a9343cbd026b2c6720ff3fa2e5b1f85e80da) )

	ROM_REGION( 0x0e00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "251.v1", 0x000000, 0x400000, CRC(ef2eecc8) SHA1(8ed13b9db92dba3124bc5ba66e3e275885ece24a) )
	ROM_LOAD( "251.v2", 0x400000, 0x400000, CRC(73e211ca) SHA1(0e60fa64cab6255d9721e2b4bc22e3de64c874c5) )
	ROM_LOAD( "251.v3", 0x800000, 0x400000, CRC(821901da) SHA1(c6d4975bfaa19a62ed59126cadf2578c0a5c257f) )
	ROM_LOAD( "251.v4", 0xc00000, 0x200000, CRC(b49e6178) SHA1(dde6f76e958841e8c99b693e13ced9aa9ef316dc) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "proto_251.c1", 0x0000000, 0x800000, CRC(e5d8ffa4) SHA1(65f15f9f02424a7a9dd35916166594f283e8d424) )
	ROM_LOAD16_BYTE( "proto_251.c2", 0x0000001, 0x800000, CRC(d822778f) SHA1(b590055e9bf1549bd6e1ecdabd65702202615712) )
	ROM_LOAD16_BYTE( "proto_251.c3", 0x1000000, 0x800000, CRC(f20959e8) SHA1(38293043fa77ac51c5e3191118874c58f1ae4d30) )
	ROM_LOAD16_BYTE( "proto_251.c4", 0x1000001, 0x800000, CRC(54ffbe9f) SHA1(8e62442923551f07a552621951b1accab2830e3b) )
	ROM_LOAD16_BYTE( "proto_251.c5", 0x2000000, 0x800000, CRC(d87a3bbc) SHA1(430f6812088712e0eb5714dcc664d8bba75e921a) )
	ROM_LOAD16_BYTE( "proto_251.c6", 0x2000001, 0x800000, CRC(4d40a691) SHA1(2b580d0678a5e6033ef16130671e860364d35e56) )
	ROM_LOAD16_BYTE( "proto_251.c7", 0x3000000, 0x800000, CRC(a4479a58) SHA1(d50e6cc9ccfe1ddbc6d90d46b8ca2cb0304edd8c) )
	ROM_LOAD16_BYTE( "proto_251.c8", 0x3000001, 0x800000, CRC(ead513ce) SHA1(e9b07a0b01fdeb3004755a479df059c81b4d0ed6) )
ROM_END

/****************************************
 ID-0252
 . ??M-2520
 NEO-MVS PROGBK1 / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7042)
****************************************/

ROM_START( ganryu ) /* Original Version - Encrypted GFX */ /* MVS ONLY RELEASE */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "252.p1", 0x100000, 0x100000, CRC(4b8ac4fb) SHA1(93d90271bff281862b03beba3809cf95a47a1e44) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_128K( "252.m1", CRC(30cc4099) SHA1(46453b7aac41855a92724a785372f8daf931d8d4) )

	ROM_REGION( 0x0400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "252.v1", 0x000000, 0x400000, CRC(e5946733) SHA1(d5904a50465af03d6ff33399a98f3259721ca0b2) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "252.c1", 0x0000000, 0x800000, CRC(50ee7882) SHA1(ace0f95407c246d0456341cf2ad8a7668b81df8a) )
	ROM_LOAD16_BYTE( "252.c2", 0x0000001, 0x800000, CRC(62585474) SHA1(b35461598087aa82886af0030c61b26cc064af5f) )
ROM_END

/****************************************
 ID-0253
 . NGM-2530
 NEO-MVS PROGLBA (1999.4.12) (NEO-SMA)(LBA-SUB) / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7042)
 . NGH-2530
 NEO-AEG PROGLBA (1999.7.6) (NEO-SMA) / NEO-AEG CHAFIO (1999.8.10) (NEO-CMC 7042)
****************************************/

ROM_START( garou ) /* Original Version - Encrypted GFX */ /* MVS VERSION - later revision */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kf.neo-sma", 0x0c0000, 0x040000, CRC(98bc93dc) SHA1(01fe3d18b50f770e131e8d8eeff4c630ba8c9551) )
	ROM_LOAD16_WORD_SWAP( "253.p1", 0x100000, 0x200000, CRC(ea3171a4) SHA1(bbda40f652baa0dc5fc6a006c001a1bdb0df43f6) )
	ROM_LOAD16_WORD_SWAP( "253.p2", 0x300000, 0x200000, CRC(382f704b) SHA1(0ace9c84a8b8a0524fd9a503e7d872de1bf1bd52) )
	ROM_LOAD16_WORD_SWAP( "253.p3", 0x500000, 0x200000, CRC(e395bfdd) SHA1(6b50f5ac15bf66b7e4e9bff57594fd3d7530c831) )
	ROM_LOAD16_WORD_SWAP( "253.p4", 0x700000, 0x200000, CRC(da92c08e) SHA1(5556f983ebcebc33160e90a6a6cf589d54c8cedc) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_256K( "253.m1", CRC(36a806be) SHA1(90fb44dc0c3fb57946a0f35716056abb84a0f191) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "253.v1", 0x000000, 0x400000, CRC(263e388c) SHA1(11f05feee170370c4bfc5053af79246a6e3de5dc) )
	ROM_LOAD( "253.v2", 0x400000, 0x400000, CRC(2c6bc7be) SHA1(c9c61054ce1a47bf1bf77a31117726b499df24a4) )
	ROM_LOAD( "253.v3", 0x800000, 0x400000, CRC(0425b27d) SHA1(986863c98fc3445487242dcf2ea75b075e7f33ee) )
	ROM_LOAD( "253.v4", 0xc00000, 0x400000, CRC(a54be8a9) SHA1(d7123e79b43e8adfaa5ecadbfcbeb6be890ec311) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "253.c1", 0x0000000, 0x800000, CRC(0603e046) SHA1(5ef4557ce90ba65d36129de97be1fdc049c4a3d0) )
	ROM_LOAD16_BYTE( "253.c2", 0x0000001, 0x800000, CRC(0917d2a4) SHA1(d4ed3a13ae22f880fb399671c1752f1a0283f316) )
	ROM_LOAD16_BYTE( "253.c3", 0x1000000, 0x800000, CRC(6737c92d) SHA1(678f0c9cc1267bd131546981b9989bfb7289d8ba) )
	ROM_LOAD16_BYTE( "253.c4", 0x1000001, 0x800000, CRC(5ba92ec6) SHA1(aae36b050a3a0321026a96eba06dd184c0e2acca) )
	ROM_LOAD16_BYTE( "253.c5", 0x2000000, 0x800000, CRC(3eab5557) SHA1(47c433015aa81a0b0a1d3ee51382c4948b80c023) )
	ROM_LOAD16_BYTE( "253.c6", 0x2000001, 0x800000, CRC(308d098b) SHA1(b052f1fa9fbc69606004c250e2505360eaa24949) )
	ROM_LOAD16_BYTE( "253.c7", 0x3000000, 0x800000, CRC(c0e995ae) SHA1(8675ca787d28246174c313167f82557f021366fc) )
	ROM_LOAD16_BYTE( "253.c8", 0x3000001, 0x800000, CRC(21a11303) SHA1(fd61221ad257c185ef5c1f9694bd6b840b591af3) )
ROM_END

ROM_START( garouh ) /* Original Version - Encrypted GFX */ /* MVS AND AES VERSION - earlier revision */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ke.neo-sma", 0x0c0000, 0x040000, CRC(96c72233) SHA1(29e19effd40fdf7e5144332396857f4ad0eff13e) )
	ROM_LOAD16_WORD_SWAP( "253h.p1",  0x100000, 0x400000, CRC(18ae5d7e) SHA1(bdb58ec9137d8653979b47132f2d10e1cc6aaa24) )
	ROM_LOAD16_WORD_SWAP( "253h.p2",  0x500000, 0x400000, CRC(afffa779) SHA1(ac017986f02277fbcd656b8c02492a3f4216a90e) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_256K( "253.m1", CRC(36a806be) SHA1(90fb44dc0c3fb57946a0f35716056abb84a0f191) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "253.v1", 0x000000, 0x400000, CRC(263e388c) SHA1(11f05feee170370c4bfc5053af79246a6e3de5dc) )
	ROM_LOAD( "253.v2", 0x400000, 0x400000, CRC(2c6bc7be) SHA1(c9c61054ce1a47bf1bf77a31117726b499df24a4) )
	ROM_LOAD( "253.v3", 0x800000, 0x400000, CRC(0425b27d) SHA1(986863c98fc3445487242dcf2ea75b075e7f33ee) )
	ROM_LOAD( "253.v4", 0xc00000, 0x400000, CRC(a54be8a9) SHA1(d7123e79b43e8adfaa5ecadbfcbeb6be890ec311) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "253.c1", 0x0000000, 0x800000, CRC(0603e046) SHA1(5ef4557ce90ba65d36129de97be1fdc049c4a3d0) )
	ROM_LOAD16_BYTE( "253.c2", 0x0000001, 0x800000, CRC(0917d2a4) SHA1(d4ed3a13ae22f880fb399671c1752f1a0283f316) )
	ROM_LOAD16_BYTE( "253.c3", 0x1000000, 0x800000, CRC(6737c92d) SHA1(678f0c9cc1267bd131546981b9989bfb7289d8ba) )
	ROM_LOAD16_BYTE( "253.c4", 0x1000001, 0x800000, CRC(5ba92ec6) SHA1(aae36b050a3a0321026a96eba06dd184c0e2acca) )
	ROM_LOAD16_BYTE( "253.c5", 0x2000000, 0x800000, CRC(3eab5557) SHA1(47c433015aa81a0b0a1d3ee51382c4948b80c023) )
	ROM_LOAD16_BYTE( "253.c6", 0x2000001, 0x800000, CRC(308d098b) SHA1(b052f1fa9fbc69606004c250e2505360eaa24949) )
	ROM_LOAD16_BYTE( "253.c7", 0x3000000, 0x800000, CRC(c0e995ae) SHA1(8675ca787d28246174c313167f82557f021366fc) )
	ROM_LOAD16_BYTE( "253.c8", 0x3000001, 0x800000, CRC(21a11303) SHA1(fd61221ad257c185ef5c1f9694bd6b840b591af3) )
ROM_END

ROM_START( garoup ) /* Prototype Version, seems genuine */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proto_253.p1", 0x000000, 0x100000, CRC(c72f0c16) SHA1(1ff6bb651682f93bef9ff02622c3cf63fe594986) )
	ROM_LOAD16_WORD_SWAP( "proto_253.p2", 0x100000, 0x400000, CRC(bf8de565) SHA1(0e24574168cd38138bed0aa4dca49849f6901ca2) )

	NEO_SFIX_128K( "proto_253.s1", CRC(779989de) SHA1(8bd550857b60f8a907f6d39a4225ceffdd330307) )

	NEO_BIOS_AUDIO_256K( "proto_253.m1", CRC(bbe464f7) SHA1(f5f8f3e48f5d453f45107085d6f4023bcd24c053) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "proto_253.v1", 0x000000, 0x400000, CRC(274f3923) SHA1(4c7a8ad1cd0e3afc1f78de3c2929120ed434f104) )
	ROM_LOAD( "proto_253.v2", 0x400000, 0x400000, CRC(8f86dabe) SHA1(b3d2d9f5c1d97a6e7aee2c674fb6627f41bbb240) )
	ROM_LOAD( "proto_253.v3", 0x800000, 0x400000, CRC(05fd06cd) SHA1(6cd699719614bb87547632ea3d61d92d81fdf563) )
	ROM_LOAD( "proto_253.v4", 0xc00000, 0x400000, CRC(14984063) SHA1(170d5638327ec0eb3590b80dc11590897367250c) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "proto_253.c1", 0x0000000, 0x800000, CRC(5bb5d137) SHA1(d648febd8e6a0bdd9bdbb6ce1f1f8b08567ec05a) )
	ROM_LOAD16_BYTE( "proto_253.c2", 0x0000001, 0x800000, CRC(5c8d2960) SHA1(f7503502be0332adf408ee0ea5ee5161c8939fd8) )
	ROM_LOAD16_BYTE( "proto_253.c3", 0x1000000, 0x800000, CRC(234d16fc) SHA1(7b9221f7ecc438150c8a10be72390329854ed21b) )
	ROM_LOAD16_BYTE( "proto_253.c4", 0x1000001, 0x800000, CRC(b9b5b993) SHA1(6059793eaf6e58c172235fe64aa9d25a40c38ed6) )
	ROM_LOAD16_BYTE( "proto_253.c5", 0x2000000, 0x800000, CRC(722615d2) SHA1(798832c535869f0e247c3db0d8253779b103e213) )
	ROM_LOAD16_BYTE( "proto_253.c6", 0x2000001, 0x800000, CRC(0a6fab38) SHA1(eaee6f2f18af91f7959d84d4b991b3fc182d07c4) )
	ROM_LOAD16_BYTE( "proto_253.c7", 0x3000000, 0x800000, CRC(d68e806f) SHA1(92bfd9839115bd590972ae4ecc45ad35dce22387) )
	ROM_LOAD16_BYTE( "proto_253.c8", 0x3000001, 0x800000, CRC(f778fe99) SHA1(c963f6ba90a36d02991728b44ffcf174ca18268a) )
ROM_END

/****************************************
 ID-0254
 . ??M-2540
 NEO-MVS PROGBK1 / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7042)
****************************************/

ROM_START( s1945p ) /* Original Version, Encrypted GFX Roms */ /* MVS ONLY RELEASE */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "254.p1",  0x000000, 0x100000, CRC(ff8efcff) SHA1(dcaeaca573385c172ecc43ee6bee355359091893) )
	ROM_LOAD16_WORD_SWAP( "254.p2", 0x100000, 0x400000, CRC(efdfd4dd) SHA1(254f3e1b546eed788f7ae919be9d1bf9702148ce) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_128K( "254.m1", CRC(994b4487) SHA1(a4e645a3ababa48a8325980ff022e04a8b51b017) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "254.v1", 0x000000, 0x400000, CRC(844f58fb) SHA1(e59544457be9f21481eac8b5a39b9cbb502f252d) )
	ROM_LOAD( "254.v2", 0x400000, 0x400000, CRC(d9a248f0) SHA1(dd3e0974b753e6f94d0943a002de45668a1b072b) )
	ROM_LOAD( "254.v3", 0x800000, 0x400000, CRC(0b0d2d33) SHA1(f8e76af42a997f36a40f66b39de00f68afe6a89c) )
	ROM_LOAD( "254.v4", 0xc00000, 0x400000, CRC(6d13dc91) SHA1(8433513c0b5aea61939068a25ab90efbe3e44116) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "254.c1", 0x0000000, 0x800000, CRC(ae6fc8ef) SHA1(544ccdaee8a4a45cdce9483e30852811d2d5f3cc) )
	ROM_LOAD16_BYTE( "254.c2", 0x0000001, 0x800000, CRC(436fa176) SHA1(d70141a91a360a1b1070753086f976608fec38af) )
	ROM_LOAD16_BYTE( "254.c3", 0x1000000, 0x800000, CRC(e53ff2dc) SHA1(31f6aaffe28146d574aa72f14f90a9d968f36bc6) )
	ROM_LOAD16_BYTE( "254.c4", 0x1000001, 0x800000, CRC(818672f0) SHA1(460c6738d0ee5ae440a23fc1434fab53bbb242b5) )
	ROM_LOAD16_BYTE( "254.c5", 0x2000000, 0x800000, CRC(4580eacd) SHA1(feb96eb5e80c9125ddd7836e0939212cd3011c34) )
	ROM_LOAD16_BYTE( "254.c6", 0x2000001, 0x800000, CRC(e34970fc) SHA1(6e43e15e27bc914357f977116ab1e2d98711bb21) )
	ROM_LOAD16_BYTE( "254.c7", 0x3000000, 0x800000, CRC(f2323239) SHA1(5b3e8dd77474203be010ec7363858d806344a320) )
	ROM_LOAD16_BYTE( "254.c8", 0x3000001, 0x800000, CRC(66848c7d) SHA1(24d4ed627940a4cf8129761c1da15556e52e199c) )
ROM_END

/****************************************
 ID-0255
 . ??M-2550
 NEO-MVS PROGBK1 / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7042)
****************************************/

ROM_START( preisle2 ) /* Original Version, Encrypted GFX */ /* MVS ONLY RELEASE */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "255.p1",  0x000000, 0x100000, CRC(dfa3c0f3) SHA1(793c6a46f3a794536dc0327a3f3fad20e25ab661) )
	ROM_LOAD16_WORD_SWAP( "255.p2", 0x100000, 0x400000, CRC(42050b80) SHA1(0981a8295d43b264c2b95e5d7568bdda4e64c976) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_128K( "255.m1", CRC(8efd4014) SHA1(5b73809b6e4e49264d281ef3e5004ac8a9de296d) )

	ROM_REGION( 0x0600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "255.v1", 0x000000, 0x400000, CRC(5a14543d) SHA1(7146ac748f846c7e2d5b0bdcf953892e39b648fe) )
	ROM_LOAD( "255.v2", 0x400000, 0x200000, CRC(6610d91a) SHA1(b2c6786920dc1712e88c3cc26d2c6c3ac2615bf4) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "255.c1", 0x0000000, 0x800000, CRC(ea06000b) SHA1(1539b12e461fa48301190eb8171bbffff9d984b7) )
	ROM_LOAD16_BYTE( "255.c2", 0x0000001, 0x800000, CRC(04e67d79) SHA1(aadb6ee750da2c14c6eededa2218db95e051a32c) )
	ROM_LOAD16_BYTE( "255.c3", 0x1000000, 0x800000, CRC(60e31e08) SHA1(bd5b81ad9d04cdc4e0df31ac40eca305f98277eb) )
	ROM_LOAD16_BYTE( "255.c4", 0x1000001, 0x800000, CRC(40371d69) SHA1(90011ccc5672ff1b90737cf50c963e71b6217ce3) )
	ROM_LOAD16_BYTE( "255.c5", 0x2000000, 0x800000, CRC(0b2e6adf) SHA1(15c7d9aa8b1ad9a071e6fd0ef0de8a057c23b02e) )
	ROM_LOAD16_BYTE( "255.c6", 0x2000001, 0x800000, CRC(b001bdd3) SHA1(394ba8004644844ee97a120cfda48aeac685af8a) )
ROM_END

/****************************************
 ID-0256
 . NGM-2560
 SMA protected version found on:
 NEO-MVS PROGLBA (1999.4.12) (NEO-SMA)(LBA-SUB) / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7042)
 Non SMA protected version found on:
 NEO-MVS PROGBK1 / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7042)
 . NGH-2560
 NEO-AEG PROGLBA (1999.7.6) (NEO-SMA)(LBA-SUB) / NEO-AEG CHAFIO (1999.8.10) (NEO-CMC 7042)
****************************************/

ROM_START( mslug3 ) /* Original Version - Encrypted Code & GFX */ /* revision 2000.4.1 */ /* MVS VERSION */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "neo-sma",    0x0c0000, 0x040000, CRC(9cd55736) SHA1(d6efb2b313127c2911d47d9324626b3f1e7c6ccb) )
	ROM_LOAD16_WORD_SWAP( "256.p1", 0x100000, 0x400000, CRC(b07edfd5) SHA1(dcbd9e500bfae98d754e55cdbbbbf9401013f8ee) )
	ROM_LOAD16_WORD_SWAP( "256.p2", 0x500000, 0x400000, CRC(6097c26b) SHA1(248ec29d21216f29dc6f5f3f0e1ad1601b3501b6) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_512K( "256.m1", CRC(eaeec116) SHA1(54419dbb21edc8c4b37eaac2e7ad9496d2de037a) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "256.v1", 0x000000, 0x400000, CRC(f2690241) SHA1(fd56babc1934d10e0d27c32f032f9edda7ca8ce9) )
	ROM_LOAD( "256.v2", 0x400000, 0x400000, CRC(7e2a10bd) SHA1(0d587fb9f64cba0315ce2d8a03e2b8fe34936dff) )
	ROM_LOAD( "256.v3", 0x800000, 0x400000, CRC(0eaec17c) SHA1(c3ed613cc6993edd6fc0d62a90bcd85de8e21915) )
	ROM_LOAD( "256.v4", 0xc00000, 0x400000, CRC(9b4b22d4) SHA1(9764fbf8453e52f80aa97a46fb9cf5937ef15a31) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "256.c1", 0x0000000, 0x800000, CRC(5a79c34e) SHA1(b8aa51fa50935cae62ab3d125b723ab888691e60) )
	ROM_LOAD16_BYTE( "256.c2", 0x0000001, 0x800000, CRC(944c362c) SHA1(3843ab300f956280475469caee70135658f67089) )
	ROM_LOAD16_BYTE( "256.c3", 0x1000000, 0x800000, CRC(6e69d36f) SHA1(94e8cf42e999114b4bd8b30e0aa2f365578c4c9a) )
	ROM_LOAD16_BYTE( "256.c4", 0x1000001, 0x800000, CRC(b755b4eb) SHA1(804700a0966a48f130c434ede3f970792ea74fa5) )
	ROM_LOAD16_BYTE( "256.c5", 0x2000000, 0x800000, CRC(7aacab47) SHA1(312c1c9846175fe1a3cad51d5ae230cf674fc93d) )
	ROM_LOAD16_BYTE( "256.c6", 0x2000001, 0x800000, CRC(c698fd5d) SHA1(16818883b06849ba2f8d61bdd5e21aaf99bd8408) )
	ROM_LOAD16_BYTE( "256.c7", 0x3000000, 0x800000, CRC(cfceddd2) SHA1(7def666adf8bd1703f40c61f182fc040b6362dc9) )
	ROM_LOAD16_BYTE( "256.c8", 0x3000001, 0x800000, CRC(4d9be34c) SHA1(a737bdfa2b815aea7067e7af2636e83a9409c414) )
ROM_END

ROM_START( mslug3a ) /* Original Version - Encrypted Code & GFX */ /* MVS VERSION */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "white.neo-sma",    0x0c0000, 0x040000, CRC(c60d29b2) SHA1(1647260ccbda833b35005608ef1fdc82fba02f04) ) /* stored in the custom SMA chip, the SMA has a white colour marking */
	ROM_LOAD16_WORD_SWAP( "256a.p1", 0x100000, 0x400000, CRC(a1177628) SHA1(4c4c379d9fc3a83265b7f32fbfce9d16b7d0f0fd) )
	ROM_LOAD16_WORD_SWAP( "256a.p2", 0x500000, 0x400000, CRC(9b659826) SHA1(d6bd03cf61879217922c18db4d3bd77095c0fe19) )

	ROM_Y_ZOOM

	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
	ROM_REGION( 0x80000, "fixed", 0 ) /* larger char set */
	ROM_FILL( 0x000000, 0x20000, 0x000000 )
	ROM_REGION( 0x20000, "fixedbios", 0 )
	ROM_LOAD( "sfix.sfix", 0x000000, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) )

	NEO_BIOS_AUDIO_512K( "256-m1.m1", CRC(eaeec116) SHA1(54419dbb21edc8c4b37eaac2e7ad9496d2de037a) ) /* mask rom TC534000 */

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "256.v1", 0x000000, 0x400000, CRC(f2690241) SHA1(fd56babc1934d10e0d27c32f032f9edda7ca8ce9) ) /* TC5332204 */
	ROM_LOAD( "256.v2", 0x400000, 0x400000, CRC(7e2a10bd) SHA1(0d587fb9f64cba0315ce2d8a03e2b8fe34936dff) ) /* TC5332204 */
	ROM_LOAD( "256.v3", 0x800000, 0x400000, CRC(0eaec17c) SHA1(c3ed613cc6993edd6fc0d62a90bcd85de8e21915) ) /* TC5332204 */
	ROM_LOAD( "256.v4", 0xc00000, 0x400000, CRC(9b4b22d4) SHA1(9764fbf8453e52f80aa97a46fb9cf5937ef15a31) ) /* TC5332204 */

	ROM_REGION( 0x4000000, "sprites", 0 )
	/* Encrypted */
	ROM_LOAD16_BYTE( "256.c1", 0x0000000, 0x800000, CRC(5a79c34e) SHA1(b8aa51fa50935cae62ab3d125b723ab888691e60) ) /* Plane 0,1 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "256.c2", 0x0000001, 0x800000, CRC(944c362c) SHA1(3843ab300f956280475469caee70135658f67089) ) /* Plane 2,3 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "256.c3", 0x1000000, 0x800000, CRC(6e69d36f) SHA1(94e8cf42e999114b4bd8b30e0aa2f365578c4c9a) ) /* Plane 0,1 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "256.c4", 0x1000001, 0x800000, CRC(b755b4eb) SHA1(804700a0966a48f130c434ede3f970792ea74fa5) ) /* Plane 2,3 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "256.c5", 0x2000000, 0x800000, CRC(7aacab47) SHA1(312c1c9846175fe1a3cad51d5ae230cf674fc93d) ) /* Plane 0,1 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "256.c6", 0x2000001, 0x800000, CRC(c698fd5d) SHA1(16818883b06849ba2f8d61bdd5e21aaf99bd8408) ) /* Plane 2,3 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "256.c7", 0x3000000, 0x800000, CRC(cfceddd2) SHA1(7def666adf8bd1703f40c61f182fc040b6362dc9) ) /* Plane 0,1 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "256.c8", 0x3000001, 0x800000, CRC(4d9be34c) SHA1(a737bdfa2b815aea7067e7af2636e83a9409c414) ) /* Plane 2,3 */ /* TC5364205 */
ROM_END

ROM_START( mslug3h ) /* Original Version - Encrypted GFX */ /* revision 2000.3.17 */ /* AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "256h.p1",  0x000000, 0x100000, CRC(9c42ca85) SHA1(7a8f77a89867b889295ae9b9dfd4ba28f02d234d) )
	ROM_LOAD16_WORD_SWAP( "256h.p2", 0x100000, 0x400000, CRC(1f3d8ce8) SHA1(08b05a8abfb86ec09a5e758d6273acf1489961f9) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_512K( "256.m1", CRC(eaeec116) SHA1(54419dbb21edc8c4b37eaac2e7ad9496d2de037a) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "256.v1", 0x000000, 0x400000, CRC(f2690241) SHA1(fd56babc1934d10e0d27c32f032f9edda7ca8ce9) )
	ROM_LOAD( "256.v2", 0x400000, 0x400000, CRC(7e2a10bd) SHA1(0d587fb9f64cba0315ce2d8a03e2b8fe34936dff) )
	ROM_LOAD( "256.v3", 0x800000, 0x400000, CRC(0eaec17c) SHA1(c3ed613cc6993edd6fc0d62a90bcd85de8e21915) )
	ROM_LOAD( "256.v4", 0xc00000, 0x400000, CRC(9b4b22d4) SHA1(9764fbf8453e52f80aa97a46fb9cf5937ef15a31) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "256.c1", 0x0000000, 0x800000, CRC(5a79c34e) SHA1(b8aa51fa50935cae62ab3d125b723ab888691e60) )
	ROM_LOAD16_BYTE( "256.c2", 0x0000001, 0x800000, CRC(944c362c) SHA1(3843ab300f956280475469caee70135658f67089) )
	ROM_LOAD16_BYTE( "256.c3", 0x1000000, 0x800000, CRC(6e69d36f) SHA1(94e8cf42e999114b4bd8b30e0aa2f365578c4c9a) )
	ROM_LOAD16_BYTE( "256.c4", 0x1000001, 0x800000, CRC(b755b4eb) SHA1(804700a0966a48f130c434ede3f970792ea74fa5) )
	ROM_LOAD16_BYTE( "256.c5", 0x2000000, 0x800000, CRC(7aacab47) SHA1(312c1c9846175fe1a3cad51d5ae230cf674fc93d) )
	ROM_LOAD16_BYTE( "256.c6", 0x2000001, 0x800000, CRC(c698fd5d) SHA1(16818883b06849ba2f8d61bdd5e21aaf99bd8408) )
	ROM_LOAD16_BYTE( "256.c7", 0x3000000, 0x800000, CRC(cfceddd2) SHA1(7def666adf8bd1703f40c61f182fc040b6362dc9) )
	ROM_LOAD16_BYTE( "256.c8", 0x3000001, 0x800000, CRC(4d9be34c) SHA1(a737bdfa2b815aea7067e7af2636e83a9409c414) )
ROM_END

/****************************************
 ID-0257
 . NGM-2570
 SMA protected version found on:
 NEO-MVS PROGLBA (1999.4.12) (NEO-SMA)(LBA-SUB) / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7050)
 Non SMA protected version found on:
 NEO-MVS PROGBK1 / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7050)
 . NGH-2570
 NEO-AEG PROGLBA (NEO-SMA) / NEO-AEG CHAFIO (1999.8.10) (NEO-CMC 7050)
****************************************/

ROM_START( kof2000 ) /* Original Version, Encrypted Code + Sound + GFX Roms */ /* MVS AND AES VERSION */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "neo-sma",   0x0c0000, 0x040000, CRC(71c6e6bb) SHA1(1bd29ded4c6b29780db8e8b772c452189699ca89) )
	ROM_LOAD16_WORD_SWAP( "257.p1", 0x100000, 0x400000, CRC(60947b4c) SHA1(5faa0a7ac7734d6c8e276589bd12dd574264647d) )
	ROM_LOAD16_WORD_SWAP( "257.p2", 0x500000, 0x400000, CRC(1b7ec415) SHA1(f19fa44e9ee5b5a6eb4a051349d6bc4acc3bbbdb) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_ENCRYPTED_256K( "257.m1", CRC(4b749113) SHA1(2af2361146edd0ce3966614d90165a5c1afb8de4) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "257.v1", 0x000000, 0x400000, CRC(17cde847) SHA1(4bcc0205b70dc6d9216b29025450c9c5b08cb65d) )
	ROM_LOAD( "257.v2", 0x400000, 0x400000, CRC(1afb20ff) SHA1(57dfd2de058139345ff2b744a225790baaecd5a2) )
	ROM_LOAD( "257.v3", 0x800000, 0x400000, CRC(4605036a) SHA1(51b228a0600d38a6ec37aec4822879ec3b0ee106) )
	ROM_LOAD( "257.v4", 0xc00000, 0x400000, CRC(764bbd6b) SHA1(df23c09ca6cf7d0ae5e11ff16e30c159725106b3) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "257.c1", 0x0000000, 0x800000, CRC(cef1cdfa) SHA1(6135080f3a6b4712b76cc217edcc58e72b55c2b9) )
	ROM_LOAD16_BYTE( "257.c2", 0x0000001, 0x800000, CRC(f7bf0003) SHA1(9f7b19a2100cf7d12867e742f440dd5277b4f895) )
	ROM_LOAD16_BYTE( "257.c3", 0x1000000, 0x800000, CRC(101e6560) SHA1(8073ae1139e215d1167f8d32c14079a46ce3ee1c) )
	ROM_LOAD16_BYTE( "257.c4", 0x1000001, 0x800000, CRC(bd2fc1b1) SHA1(da0006761923ad49b404a08d7a151193ee307a69) )
	ROM_LOAD16_BYTE( "257.c5", 0x2000000, 0x800000, CRC(89775412) SHA1(b221b30224bc4239f1b3c2d2fd1cd4fa84e3523c) )
	ROM_LOAD16_BYTE( "257.c6", 0x2000001, 0x800000, CRC(fa7200d5) SHA1(6f2b0d38af34e280d56a58955400e5c679906871) )
	ROM_LOAD16_BYTE( "257.c7", 0x3000000, 0x800000, CRC(7da11fe4) SHA1(065336cf166807acb6c8569d59d3bf37a19b0a42) )
	ROM_LOAD16_BYTE( "257.c8", 0x3000001, 0x800000, CRC(b1afa60b) SHA1(b916184f5cfe4121752270f4f65abf35d8eb0519) )
ROM_END

ROM_START( kof2000n ) /* Original Version, Encrypted Sound + GFX Roms */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "257n.p1",  0x000000, 0x100000, CRC(5f809dbe) SHA1(2bc233dcff5622de86d01e3b74b840c7caf12982) )
	ROM_LOAD16_WORD_SWAP( "257n.p2", 0x100000, 0x400000, CRC(693c2c5e) SHA1(dc9121b7369ef46596343cac055a00aec81704d4) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_ENCRYPTED_256K( "257.m1", CRC(4b749113) SHA1(2af2361146edd0ce3966614d90165a5c1afb8de4) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "257.v1", 0x000000, 0x400000, CRC(17cde847) SHA1(4bcc0205b70dc6d9216b29025450c9c5b08cb65d) )
	ROM_LOAD( "257.v2", 0x400000, 0x400000, CRC(1afb20ff) SHA1(57dfd2de058139345ff2b744a225790baaecd5a2) )
	ROM_LOAD( "257.v3", 0x800000, 0x400000, CRC(4605036a) SHA1(51b228a0600d38a6ec37aec4822879ec3b0ee106) )
	ROM_LOAD( "257.v4", 0xc00000, 0x400000, CRC(764bbd6b) SHA1(df23c09ca6cf7d0ae5e11ff16e30c159725106b3) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "257.c1", 0x0000000, 0x800000, CRC(cef1cdfa) SHA1(6135080f3a6b4712b76cc217edcc58e72b55c2b9) )
	ROM_LOAD16_BYTE( "257.c2", 0x0000001, 0x800000, CRC(f7bf0003) SHA1(9f7b19a2100cf7d12867e742f440dd5277b4f895) )
	ROM_LOAD16_BYTE( "257.c3", 0x1000000, 0x800000, CRC(101e6560) SHA1(8073ae1139e215d1167f8d32c14079a46ce3ee1c) )
	ROM_LOAD16_BYTE( "257.c4", 0x1000001, 0x800000, CRC(bd2fc1b1) SHA1(da0006761923ad49b404a08d7a151193ee307a69) )
	ROM_LOAD16_BYTE( "257.c5", 0x2000000, 0x800000, CRC(89775412) SHA1(b221b30224bc4239f1b3c2d2fd1cd4fa84e3523c) )
	ROM_LOAD16_BYTE( "257.c6", 0x2000001, 0x800000, CRC(fa7200d5) SHA1(6f2b0d38af34e280d56a58955400e5c679906871) )
	ROM_LOAD16_BYTE( "257.c7", 0x3000000, 0x800000, CRC(7da11fe4) SHA1(065336cf166807acb6c8569d59d3bf37a19b0a42) )
	ROM_LOAD16_BYTE( "257.c8", 0x3000001, 0x800000, CRC(b1afa60b) SHA1(b916184f5cfe4121752270f4f65abf35d8eb0519) )
ROM_END

/****************************************
 ID-0258
 SNK vs. Capcom?
****************************************/

/****************************************
 ID-0259
 . ??M-2590
 NEO-MVS PROGBK1 / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7042)
****************************************/

ROM_START( bangbead ) /* Original Version - Encrypted GFX */ /* MVS ONLY RELEASE */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "259.p1", 0x100000, 0x100000, CRC(88a37f8b) SHA1(566db84850fad5e8fe822e8bba910a33e083b550) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_128K( "259.m1", CRC(85668ee9) SHA1(7d3f51710cf90c097cd3faaeeef10ceb85cbb3e8) )

	ROM_REGION( 0x500000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "259.v1", 0x000000, 0x400000, CRC(088eb8ab) SHA1(608306e35501dd7d382d9f96b28e7550aa896a03) )
	ROM_LOAD( "259.v2", 0x400000, 0x100000, CRC(97528fe9) SHA1(8f5eddbb3a9a225492479d1a44801f3916c8e791) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "259.c1", 0x0000000, 0x800000, CRC(1f537f74) SHA1(b8ef691e92191c20a5ed4f20a75cca3c7383bca6) )
	ROM_LOAD16_BYTE( "259.c2", 0x0000001, 0x800000, CRC(0efd98ff) SHA1(d350315d3c7f26d638458e5ccf2126069a4c7a5b) )
ROM_END

/****************************************
 ID-0260
 . ??M-2600
 NEO-MVS PROGBK1 / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7042)
****************************************/

ROM_START( nitd ) /* Original Version - Encrypted GFX */ /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "260.p1", 0x000000, 0x080000, CRC(61361082) SHA1(441f3f41c1aa752c0e0a9a0b1d92711d9e636b85) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_512K( "260.m1", CRC(6407c5e5) SHA1(d273e154cc905b63205a17a1a6d419cac3485a92) )

	ROM_REGION( 0x0400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "260.v1", 0x000000, 0x400000, CRC(24b0480c) SHA1(d769e621be52a5cd2e2568891b5f95a48268e1e0) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "260.c1", 0x0000000, 0x800000, CRC(147b0c7f) SHA1(a647c3a2f6d146ff47521c1d39f58830601f5781) )
	ROM_LOAD16_BYTE( "260.c2", 0x0000001, 0x800000, CRC(d2b04b0d) SHA1(ce4322e6cfacb627fe997efe81018861e21d3c27) )
ROM_END

/****************************************
 ID-0261
 . NGM-2610
 NEO-MVS PROGBK1 / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7042)
 . NGH-2610
 NEO-AEG PROGBK1F / NEO-AEG CHAFIO (1999.8.10) (NEO-CMC 7042)
****************************************/

ROM_START( sengoku3 ) /* Original Version - Encrypted GFX */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "261.p1", 0x100000, 0x100000, CRC(e0d4bc0a) SHA1(8df366097f224771ca6d1aa5c1691cd46776cd12) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_512K( "261.m1", CRC(7d501c39) SHA1(8e6bcc428f5ac7532d9c9be7e07ad0821461a080) )

	ROM_REGION( 0x0e00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "261.v1", 0x000000, 0x400000, CRC(64c30081) SHA1(f9ebd20cf59b72e864b7274c1bdb6d99ecaf4595) )
	ROM_LOAD( "261.v2", 0x400000, 0x400000, CRC(392a9c47) SHA1(7ab90a54089236ca6c3ef1af8e566a8025d38159) )
	ROM_LOAD( "261.v3", 0x800000, 0x400000, CRC(c1a7ebe3) SHA1(1d7bb481451f5ee0457e954bb5210300182c3c9c) )
	ROM_LOAD( "261.v4", 0xc00000, 0x200000, CRC(9000d085) SHA1(11157b355ab4eb6627e9f322ed875332d3d77349) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "261.c1", 0x0000000, 0x800000, CRC(ded84d9c) SHA1(d960523b813d4fae06d716298d4e431a5c77a0c5) )
	ROM_LOAD16_BYTE( "261.c2", 0x0000001, 0x800000, CRC(b8eb4348) SHA1(619d24312549932959481fa58f43f11c048e1ca5) )
	ROM_LOAD16_BYTE( "261.c3", 0x1000000, 0x800000, CRC(84e2034a) SHA1(38ec4ae4b86933a25c9a03799b8cade4b1346401) )
	ROM_LOAD16_BYTE( "261.c4", 0x1000001, 0x800000, CRC(0b45ae53) SHA1(a19fb21408ab633aee8bbf38bf43b5e26766b355) )
ROM_END

/****************************************
 ID-0262
 . NGM-262?
 MVS PROGBK2 REV1.0 (NEO-PCM2 SNK)/ MVS CHAFIO REV1.0 (NEO-CMC 7050)
 . NGH-2621
 NEO-AEG PROGBK1F / NEO-AEG CHAFIO (1999.8.10) (NEO-CMC 7050)
  - Distribution by BrezzaSoft
****************************************/

ROM_START( kof2001 ) /* MVS VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "262.p1",  0x000000, 0x100000, CRC(9381750d) SHA1(dcfecd69e563ff52fe07d23c5372d0f748b07819) )
	ROM_LOAD16_WORD_SWAP( "262.p2", 0x100000, 0x400000, CRC(8e0d8329) SHA1(10dcc1baf0aaf1fc84c4d856bca6bcff85aed2bc) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_256K( "262.m1", CRC(a7f8119f) SHA1(71805b39b8b09c32425cf39f9de59b2f755976c2) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "262.v1", 0x000000, 0x400000, CRC(83d49ecf) SHA1(2f2c116e45397652e77fcf5d951fa5f71b639572) )
	ROM_LOAD( "262.v2", 0x400000, 0x400000, CRC(003f1843) SHA1(bdd58837ad542548bd4053c262f558af88e3b989) )
	ROM_LOAD( "262.v3", 0x800000, 0x400000, CRC(2ae38dbe) SHA1(4e82b7dd3b899d61907620517a5a27bdaba0725d) )
	ROM_LOAD( "262.v4", 0xc00000, 0x400000, CRC(26ec4dd9) SHA1(8bd68d95a2d913be41a51f51e48dbe3bff5924fb) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "262.c1", 0x0000000, 0x800000, CRC(99cc785a) SHA1(374f0674871d0196fa274aa6c5956d7b3848d5da) )
	ROM_LOAD16_BYTE( "262.c2", 0x0000001, 0x800000, CRC(50368cbf) SHA1(5d9e206e98e0b0c7735b72ea46b45058fdec2352) )
	ROM_LOAD16_BYTE( "262.c3", 0x1000000, 0x800000, CRC(fb14ff87) SHA1(445a8db2fc69eff54a252700f2d3a89244c58e75) )
	ROM_LOAD16_BYTE( "262.c4", 0x1000001, 0x800000, CRC(4397faf8) SHA1(6752b394f6647502a649a3e62bd3442f936b733e) )
	ROM_LOAD16_BYTE( "262.c5", 0x2000000, 0x800000, CRC(91f24be4) SHA1(88190c41f7d4a0f4b1982149fc9acfc640af498d) )
	ROM_LOAD16_BYTE( "262.c6", 0x2000001, 0x800000, CRC(a31e4403) SHA1(5cd1a14703aa58810e2377dfb7353c61e9dc9c1f) )
	ROM_LOAD16_BYTE( "262.c7", 0x3000000, 0x800000, CRC(54d9d1ec) SHA1(80c3a8ec39130dd5d3da561f287709da6b8abcf4) )
	ROM_LOAD16_BYTE( "262.c8", 0x3000001, 0x800000, CRC(59289a6b) SHA1(ddfce7c85b2a144975db5bb14b4b51aaf881880e) )
ROM_END

ROM_START( kof2001h ) /* AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "262h.p1",  0x000000, 0x100000, CRC(2af7e741) SHA1(e41282d73ed6d521da056f1a16573bb61bfa3826) )
	ROM_LOAD16_WORD_SWAP( "262h.p2", 0x100000, 0x400000, CRC(91eea062) SHA1(82bae42bbeedb9f3aa0c7c0b0a7a69be499cf98f) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_256K( "262.m1", CRC(a7f8119f) SHA1(71805b39b8b09c32425cf39f9de59b2f755976c2) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "262.v1", 0x000000, 0x400000, CRC(83d49ecf) SHA1(2f2c116e45397652e77fcf5d951fa5f71b639572) )
	ROM_LOAD( "262.v2", 0x400000, 0x400000, CRC(003f1843) SHA1(bdd58837ad542548bd4053c262f558af88e3b989) )
	ROM_LOAD( "262.v3", 0x800000, 0x400000, CRC(2ae38dbe) SHA1(4e82b7dd3b899d61907620517a5a27bdaba0725d) )
	ROM_LOAD( "262.v4", 0xc00000, 0x400000, CRC(26ec4dd9) SHA1(8bd68d95a2d913be41a51f51e48dbe3bff5924fb) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "262.c1", 0x0000000, 0x800000, CRC(99cc785a) SHA1(374f0674871d0196fa274aa6c5956d7b3848d5da) )
	ROM_LOAD16_BYTE( "262.c2", 0x0000001, 0x800000, CRC(50368cbf) SHA1(5d9e206e98e0b0c7735b72ea46b45058fdec2352) )
	ROM_LOAD16_BYTE( "262.c3", 0x1000000, 0x800000, CRC(fb14ff87) SHA1(445a8db2fc69eff54a252700f2d3a89244c58e75) )
	ROM_LOAD16_BYTE( "262.c4", 0x1000001, 0x800000, CRC(4397faf8) SHA1(6752b394f6647502a649a3e62bd3442f936b733e) )
	ROM_LOAD16_BYTE( "262.c5", 0x2000000, 0x800000, CRC(91f24be4) SHA1(88190c41f7d4a0f4b1982149fc9acfc640af498d) )
	ROM_LOAD16_BYTE( "262.c6", 0x2000001, 0x800000, CRC(a31e4403) SHA1(5cd1a14703aa58810e2377dfb7353c61e9dc9c1f) )
	ROM_LOAD16_BYTE( "262.c7", 0x3000000, 0x800000, CRC(54d9d1ec) SHA1(80c3a8ec39130dd5d3da561f287709da6b8abcf4) )
	ROM_LOAD16_BYTE( "262.c8", 0x3000001, 0x800000, CRC(59289a6b) SHA1(ddfce7c85b2a144975db5bb14b4b51aaf881880e) )
ROM_END

/****************************************
 ID-0263
 . NGM-2630
 NEO-MVS PROGBK2 (NEO-PCM2 SNK)/ NEO-MVS CHAFIO (NEO-CMC 7050)
 . NGH-2630
 NEO-AEG PROGBK2 (2002.4.1) (NEO-PCM2 SNK) / NEO-AEG CHAFIO (1999.8.10) (NEO-CMC 7050)
****************************************/

ROM_START( mslug4 ) /* Original Version - Encrypted GFX */ /* MVS VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263.p1",  0x000000, 0x100000, CRC(27e4def3) SHA1(a08785e8145981bb6b5332a3b2df7eb321253cca) )
	ROM_LOAD16_WORD_SWAP( "263.p2", 0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "263.m1", CRC(46ac8228) SHA1(5aeea221050c98e4bb0f16489ce772bf1c80f787) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "263.v1", 0x000000, 0x800000, CRC(01e9b9cd) SHA1(0b045c2999449f7dab5ae8a42e957d5b6650431e) )
	ROM_LOAD( "263.v2", 0x800000, 0x800000, CRC(4ab2bf81) SHA1(77ccfa48f7e3daddef5fe5229a0093eb2f803742) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "263.c1", 0x0000000, 0x800000, CRC(84865f8a) SHA1(34467ada896eb7c7ca58658bf2a932936d8b632c) )
	ROM_LOAD16_BYTE( "263.c2", 0x0000001, 0x800000, CRC(81df97f2) SHA1(2b74493b8ec8fd49216a627aeb3db493f76124e3) )
	ROM_LOAD16_BYTE( "263.c3", 0x1000000, 0x800000, CRC(1a343323) SHA1(bbbb5232bba538c277ce2ee02e2956ca2243b787) )
	ROM_LOAD16_BYTE( "263.c4", 0x1000001, 0x800000, CRC(942cfb44) SHA1(d9b46c71726383c4581fb042e63897e5a3c92d1b) )
	ROM_LOAD16_BYTE( "263.c5", 0x2000000, 0x800000, CRC(a748854f) SHA1(2611bbedf9b5d8e82c6b2c99b88f842c46434d41) )
	ROM_LOAD16_BYTE( "263.c6", 0x2000001, 0x800000, CRC(5c8ba116) SHA1(6034db09c8706d4ddbcefc053efbc47a0953eb92) )
ROM_END

ROM_START( mslug4h ) /* Original Version - Encrypted GFX */ /* AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "263h.p1",  0x000000, 0x100000, CRC(c67f5c8d) SHA1(12af74964843f103520d9f0825069ea2f67eeb2f) )
	ROM_LOAD16_WORD_SWAP( "263h.p2", 0x100000, 0x400000, CRC(bc3ec89e) SHA1(2cb0626bc4fa57e1d25f208e04532b570d87b3fb) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "263.m1", CRC(46ac8228) SHA1(5aeea221050c98e4bb0f16489ce772bf1c80f787) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "263.v1", 0x000000, 0x800000, CRC(01e9b9cd) SHA1(0b045c2999449f7dab5ae8a42e957d5b6650431e) )
	ROM_LOAD( "263.v2", 0x800000, 0x800000, CRC(4ab2bf81) SHA1(77ccfa48f7e3daddef5fe5229a0093eb2f803742) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "263.c1", 0x0000000, 0x800000, CRC(84865f8a) SHA1(34467ada896eb7c7ca58658bf2a932936d8b632c) )
	ROM_LOAD16_BYTE( "263.c2", 0x0000001, 0x800000, CRC(81df97f2) SHA1(2b74493b8ec8fd49216a627aeb3db493f76124e3) )
	ROM_LOAD16_BYTE( "263.c3", 0x1000000, 0x800000, CRC(1a343323) SHA1(bbbb5232bba538c277ce2ee02e2956ca2243b787) )
	ROM_LOAD16_BYTE( "263.c4", 0x1000001, 0x800000, CRC(942cfb44) SHA1(d9b46c71726383c4581fb042e63897e5a3c92d1b) )
	ROM_LOAD16_BYTE( "263.c5", 0x2000000, 0x800000, CRC(a748854f) SHA1(2611bbedf9b5d8e82c6b2c99b88f842c46434d41) )
	ROM_LOAD16_BYTE( "263.c6", 0x2000001, 0x800000, CRC(5c8ba116) SHA1(6034db09c8706d4ddbcefc053efbc47a0953eb92) )
ROM_END

/****************************************
 ID-0264
 . NGM-264?
 NEO-MVS PROGBK2 (2000.3.21) (NEO-PCM2 SNK) / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7050)
 . NGH-2641
 NEO-AEG PROGBK2 (2002.4.1) (NEO-PCM2 SNK) / NEO-AEG CHAFIO (1999.8.10) (NEO-CMC 7050)
  - Distribution by BrezzaSoft
****************************************/

ROM_START( rotd ) /* Encrypted Set */ /* MVS VERSION */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "264.p1", 0x000000, 0x800000, CRC(b8cc969d) SHA1(4f2205b4bdd32dd1522106ef4df10ac0eb1b852d) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "264.m1", CRC(4dbd7b43) SHA1(6b63756b0d2d30bbf13fbd219833c81fd060ef96) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "264.v1", 0x000000, 0x800000, CRC(fa005812) SHA1(73723126dab5a640ac11955ed6da1bf7a91394f5) )
	ROM_LOAD( "264.v2", 0x800000, 0x800000, CRC(c3dc8bf0) SHA1(a105e37262d9500a30fb8a5dac05aa4fab2562a3) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "264.c1", 0x0000000, 0x800000, CRC(4f148fee) SHA1(0821463765fad8fbd0dfbbabb7807337d0333719) )
	ROM_LOAD16_BYTE( "264.c2", 0x0000001, 0x800000, CRC(7cf5ff72) SHA1(ccb2f94bce943576d224cb326806942426d25584) )
	ROM_LOAD16_BYTE( "264.c3", 0x1000000, 0x800000, CRC(64d84c98) SHA1(8faf153f465ce6fb7770b27a7ce63caf11dd4086) )
	ROM_LOAD16_BYTE( "264.c4", 0x1000001, 0x800000, CRC(2f394a95) SHA1(82347e8f2b48b0522d7d91fd3f372d5768934ab2) )
	ROM_LOAD16_BYTE( "264.c5", 0x2000000, 0x800000, CRC(6b99b978) SHA1(8fd0a60029b41668f9e1e3056edd3c90f62efa83) )
	ROM_LOAD16_BYTE( "264.c6", 0x2000001, 0x800000, CRC(847d5c7d) SHA1(a2ce03f6302edf81f2645de9ec61df1a281ddd78) )
	ROM_LOAD16_BYTE( "264.c7", 0x3000000, 0x800000, CRC(231d681e) SHA1(87836e64dc816f8bf1c834641535ea96baacc024) )
	ROM_LOAD16_BYTE( "264.c8", 0x3000001, 0x800000, CRC(c5edb5c4) SHA1(253378c8739daa5da4edb15eff7050820b2b3755) )
ROM_END

/****************************************
 ID-0265
 . NGM-2650
 NEO-MVS PROGBK2 (2000.3.21) (NEO-PCM2 PLAYMORE) / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7050)
 . NGH-2650
 NEO-AEG PROGBK2 (NEO-PCM2 PLAYMORE) / NEO-AEG CHAFIO (1999.8.10) (NEO-CMC 7050)
****************************************/

ROM_START( kof2002 ) /* Encrypted Set */ /* MVS AND AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "265.p1",  0x000000, 0x100000, CRC(9ede7323) SHA1(ad9d45498777fda9fa58e75781f48e09aee705a6) )
	ROM_LOAD16_WORD_SWAP( "265.p2", 0x100000, 0x400000, CRC(327266b8) SHA1(98f445cc0a94f8744d74bca71cb420277622b034) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "265.m1", CRC(85aaa632) SHA1(744fba4ca3bc3a5873838af886efb97a8a316104) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "265.v1", 0x000000, 0x800000, CRC(15e8f3f5) SHA1(7c9e6426b9fa6db0158baa17a6485ffce057d889) )
	ROM_LOAD( "265.v2", 0x800000, 0x800000, CRC(da41d6f9) SHA1(a43021f1e58947dcbe3c8ca5283b20b649f0409d) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "265.c1", 0x0000000, 0x800000, CRC(2b65a656) SHA1(9c46d8cf5b1ef322db442ac6a9b9406ab49206c5) )
	ROM_LOAD16_BYTE( "265.c2", 0x0000001, 0x800000, CRC(adf18983) SHA1(150cd4a5e51e9df88688469d2ea7675c2cf3658a) )
	ROM_LOAD16_BYTE( "265.c3", 0x1000000, 0x800000, CRC(875e9fd7) SHA1(28f52d56192d48bbc5dc3c97abf456bd34a58cbd) )
	ROM_LOAD16_BYTE( "265.c4", 0x1000001, 0x800000, CRC(2da13947) SHA1(f8d79ec2c236aa3d3648a4f715676899602122c1) )
	ROM_LOAD16_BYTE( "265.c5", 0x2000000, 0x800000, CRC(61bd165d) SHA1(b3424db84bc683d858fb635bc42728f9cdd89caf) )
	ROM_LOAD16_BYTE( "265.c6", 0x2000001, 0x800000, CRC(03fdd1eb) SHA1(6155c7e802062f4eafa27e414c4e73ee59b868bf) )
	ROM_LOAD16_BYTE( "265.c7", 0x3000000, 0x800000, CRC(1a2749d8) SHA1(af7d9ec1d576209826fa568f676bbff92f6d6ddd) )
	ROM_LOAD16_BYTE( "265.c8", 0x3000001, 0x800000, CRC(ab0bb549) SHA1(d23afb60b7f831f7d4a98ad3c4a00ee19877a1ce) )
ROM_END

/****************************************
 ID-0266
 . NGM-2660
 NEO-MVS PROGBK2 (2000.3.21) (NEO-PCM2 PLAYMORE) / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7050)
 . NGH-2660
 NEO-AEG PROGBK2 (2002.4.1) (NEO-PCM2 PLAYMORE) / NEO-AEG CHAFIO (1999.8.10) (NEO-CMC 7050)
****************************************/

ROM_START( matrim ) /* Encrypted Set */ /* MVS AND AES VERSION */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "266.p1",  0x000000, 0x100000, CRC(5d4c2dc7) SHA1(8d723b0d28ec344eef26009b361a2b97d300dd51) )
	ROM_LOAD16_WORD_SWAP( "266.p2", 0x100000, 0x400000, CRC(a14b1906) SHA1(1daa14d73512f760ef569b06f9facb279437d1db) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "266.m1", CRC(456c3e6c) SHA1(5a07d0186198a18d2dda1331093cf29b0b9b2984) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "266.v1", 0x000000, 0x800000, CRC(a4f83690) SHA1(200d683d8c30ebc6d0ed331aa5bbba39b4e07160) )
	ROM_LOAD( "266.v2", 0x800000, 0x800000, CRC(d0f69eda) SHA1(9d7e98976ad433ed8a35d7afffa38130444ba7db) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "266.c1", 0x0000000, 0x800000, CRC(505f4e30) SHA1(f22b6f76fc0cad963555dc89d072967c8dc8b79a) )
	ROM_LOAD16_BYTE( "266.c2", 0x0000001, 0x800000, CRC(3cb57482) SHA1(dab15bc24391f9a5173de76af48b612fb9636ccf) )
	ROM_LOAD16_BYTE( "266.c3", 0x1000000, 0x800000, CRC(f1cc6ad0) SHA1(66c1cccc0332ffd2d3064f06330c41f95ca09ced) )
	ROM_LOAD16_BYTE( "266.c4", 0x1000001, 0x800000, CRC(45b806b7) SHA1(c2bb866fded53d62fad0fc88d89d5e7d4cb1894f) )
	ROM_LOAD16_BYTE( "266.c5", 0x2000000, 0x800000, CRC(9a15dd6b) SHA1(194a6973a7a9e3847efe1bdbaeaeb16e74aff2dd) )
	ROM_LOAD16_BYTE( "266.c6", 0x2000001, 0x800000, CRC(281cb939) SHA1(bdb7766cfde581ccfaee2be7fe48445f360a2301) )
	ROM_LOAD16_BYTE( "266.c7", 0x3000000, 0x800000, CRC(4b71f780) SHA1(d5611a6f6b730db58613b48f2b0174661ccfb7bb) )
	ROM_LOAD16_BYTE( "266.c8", 0x3000001, 0x800000, CRC(29873d33) SHA1(dc77f129ed49b8d40d0d4241feef3f6c2f19a987) )
ROM_END

/****************************************
 ID-0267
 . ??M-2670
 NEO-MVS PROGBK2 (2000.3.21) (NEO-PCM2 SNK) / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7050)
****************************************/

ROM_START( pnyaa ) /* Encrypted Set */ /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pn202.p1", 0x000000, 0x100000, CRC(bf34e71c) SHA1(cfa7a2c7c41601a758414faf34e59583d7537363) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "267.m1", CRC(c7853ccd) SHA1(1b7a4c5093cf0fe3861ce44fd1d3b30c71ad0abe) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "267.v1", 0x000000, 0x400000, CRC(e2e8e917) SHA1(7f412d55aebff3d38a225a88c632916295ab0584) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "267.c1", 0x0000000, 0x800000, CRC(5eebee65) SHA1(7eb3eefdeb24e19831d0f51d4ea07a0292c25ab6) )
	ROM_LOAD16_BYTE( "267.c2", 0x0000001, 0x800000, CRC(2b67187b) SHA1(149c3efd3c444fd0d35a97fa2268102bf76be3ed) )
ROM_END

/****************************************
 ID-0268
 . NGM-2680
 NEO-MVS PROGBK3S (2003.10.1) (NEO-PCM2 PLAYMORE) (NEO-PVC) / NEO-MVS CHAFIO (2003.7.24) (NEO-CMC 7050)
 . NGH-2680
 NEO-AEG PROGBK3S (2003.10.6) (NEO-PCM2 PLAYMORE) (NEO-PVC) / NEO-AEG CHAFIO (2003.7.24) (NEO-CMC 7050)
****************************************/

ROM_START( mslug5 ) /* Encrypted Set */ /* MVS VERSION */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "268.p1", 0x000000, 0x400000, CRC(d0466792) SHA1(880819933d997fab398f91061e9dbccb959ae8a1) )
	ROM_LOAD32_WORD_SWAP( "268.p2", 0x000002, 0x400000, CRC(fbf6b61e) SHA1(9ec743d5988b5e3183f37f8edf45c72a8c0c893e) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "268.m1", CRC(4a5a6e0e) SHA1(df0f660f2465e1db7be5adfcaf5e88ad61a74a42) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "268.v1", 0x000000, 0x800000, CRC(ae31d60c) SHA1(c42285cf4e52fea74247860813e826df5aa7600a) )
	ROM_LOAD( "268.v2", 0x800000, 0x800000, CRC(c40613ed) SHA1(af889570304e2867d7dfea1e94e388c06249fb67) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "268.c1", 0x0000000, 0x800000, CRC(ab7c389a) SHA1(025a188de589500bf7637fa8e7a37ab24bf4312e) )
	ROM_LOAD16_BYTE( "268.c2", 0x0000001, 0x800000, CRC(3560881b) SHA1(493d218c92290b4770024d6ee2917c4022753b07) )
	ROM_LOAD16_BYTE( "268.c3", 0x1000000, 0x800000, CRC(3af955ea) SHA1(cf36b6ae9b0d12744b17cb7a928399214de894be) )
	ROM_LOAD16_BYTE( "268.c4", 0x1000001, 0x800000, CRC(c329c373) SHA1(5073d4079958a0ef5426885af2c9e3178f37d5e0) )
	ROM_LOAD16_BYTE( "268.c5", 0x2000000, 0x800000, CRC(959c8177) SHA1(889bda7c65d71172e7d89194d1269561888fe789) )
	ROM_LOAD16_BYTE( "268.c6", 0x2000001, 0x800000, CRC(010a831b) SHA1(aec140661e3ae35d264df416478ba15188544d91) )
	ROM_LOAD16_BYTE( "268.c7", 0x3000000, 0x800000, CRC(6d72a969) SHA1(968dd9a4d1209b770b9b85ea6532fa24d262a262) )
	ROM_LOAD16_BYTE( "268.c8", 0x3000001, 0x800000, CRC(551d720e) SHA1(ebf69e334fcaba0fda6fd432fd0970283a365d12) )
ROM_END

ROM_START( mslug5h ) /* Encrypted Set */ /* AES release of the game but is also found in later MVS carts */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "268h.p1", 0x000000, 0x400000, CRC(3636690a) SHA1(e0da714b4bdc6efffe1250ded02ebddb3ab6d7b3) )
	ROM_LOAD32_WORD_SWAP( "268h.p2", 0x000002, 0x400000, CRC(8dfc47a2) SHA1(27d618cfbd0107a4d2a836797e967b39d2eb4851) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "268.m1", CRC(4a5a6e0e) SHA1(df0f660f2465e1db7be5adfcaf5e88ad61a74a42) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "268.v1", 0x000000, 0x800000, CRC(ae31d60c) SHA1(c42285cf4e52fea74247860813e826df5aa7600a) )
	ROM_LOAD( "268.v2", 0x800000, 0x800000, CRC(c40613ed) SHA1(af889570304e2867d7dfea1e94e388c06249fb67) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "268.c1", 0x0000000, 0x800000, CRC(ab7c389a) SHA1(025a188de589500bf7637fa8e7a37ab24bf4312e) )
	ROM_LOAD16_BYTE( "268.c2", 0x0000001, 0x800000, CRC(3560881b) SHA1(493d218c92290b4770024d6ee2917c4022753b07) )
	ROM_LOAD16_BYTE( "268.c3", 0x1000000, 0x800000, CRC(3af955ea) SHA1(cf36b6ae9b0d12744b17cb7a928399214de894be) )
	ROM_LOAD16_BYTE( "268.c4", 0x1000001, 0x800000, CRC(c329c373) SHA1(5073d4079958a0ef5426885af2c9e3178f37d5e0) )
	ROM_LOAD16_BYTE( "268.c5", 0x2000000, 0x800000, CRC(959c8177) SHA1(889bda7c65d71172e7d89194d1269561888fe789) )
	ROM_LOAD16_BYTE( "268.c6", 0x2000001, 0x800000, CRC(010a831b) SHA1(aec140661e3ae35d264df416478ba15188544d91) )
	ROM_LOAD16_BYTE( "268.c7", 0x3000000, 0x800000, CRC(6d72a969) SHA1(968dd9a4d1209b770b9b85ea6532fa24d262a262) )
	ROM_LOAD16_BYTE( "268.c8", 0x3000001, 0x800000, CRC(551d720e) SHA1(ebf69e334fcaba0fda6fd432fd0970283a365d12) )
ROM_END

/****************************************
 ID-0269
 . NGM-2690
 NEO-MVS PROGBK3R (2003.9.2) (NEO-PCM2 PLAYMORE) (NEO-PVC) / NEO-MVS CHAFIO (2003.7.24) (NEO-CMC 7050)
 . NGH-2690
 NEO-AEG PROGBK3R (2003.8.29) (NEO-PCM2 PLAYMORE) (NEO-PVC) / NEO-AEG CHAFIO (2003.7.24) (NEO-CMC 7050)
****************************************/

ROM_START( svc ) /* Encrypted Set */ /* MVS AND AES VERSION */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "269.p1", 0x000000, 0x400000, CRC(38e2005e) SHA1(1b902905916a30969282f1399a756e32ff069097) )
	ROM_LOAD32_WORD_SWAP( "269.p2", 0x000002, 0x400000, CRC(6d13797c) SHA1(3cb71a95cea6b006b44cac0f547df88aec0007b7) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "269.m1", CRC(f6819d00) SHA1(d3bbe09df502464f104e53501708ac6e2c1832c6) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "269.v1", 0x000000, 0x800000, CRC(c659b34c) SHA1(1931e8111ef43946f68699f8707334c96f753a1e) )
	ROM_LOAD( "269.v2", 0x800000, 0x800000, CRC(dd903835) SHA1(e58d38950a7a8697bb22a1cc7a371ae6664ae8f9) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "269.c1", 0x0000000, 0x800000, CRC(887b4068) SHA1(227cdcf7a10a415f1e3afe7ae97acc9afc2cc8e1) )
	ROM_LOAD16_BYTE( "269.c2", 0x0000001, 0x800000, CRC(4e8903e4) SHA1(31daaa4fd6c23e8f0a8428931c513d97d2eee1bd) )
	ROM_LOAD16_BYTE( "269.c3", 0x1000000, 0x800000, CRC(7d9c55b0) SHA1(1f94a948b3e3c31b3ff05518ef525031a3cb2c62) )
	ROM_LOAD16_BYTE( "269.c4", 0x1000001, 0x800000, CRC(8acb5bb6) SHA1(2c27d6e309646d7b84da85f78c06e4aaa74e844b) )
	ROM_LOAD16_BYTE( "269.c5", 0x2000000, 0x800000, CRC(097a4157) SHA1(54d839f55d27f68c704a94ea3c63c644ffc22ca4) )
	ROM_LOAD16_BYTE( "269.c6", 0x2000001, 0x800000, CRC(e19df344) SHA1(20448add53ab25dd3a8f0b681131ad3b9c68acc9) )
	ROM_LOAD16_BYTE( "269.c7", 0x3000000, 0x800000, CRC(d8f0340b) SHA1(43114af7557361a8903bb8cf8553f602946a9220) )
	ROM_LOAD16_BYTE( "269.c8", 0x3000001, 0x800000, CRC(2570b71b) SHA1(99266e1c2ffcf324793fb5c55325fbc7e6265ac0) )
ROM_END

/****************************************
 ID-0270
 . NGM-2700
 NEO-MVS PROGBK2R (2003.8.26) (NEO-PCM2 PLAYMORE) / NEO-MVS CHAFIO (2003.7.24) (NEO-CMC 7050)
 . NGH-2700
 NEO-AEG PROGBK2S (2003.10.16) (NEO-PCM2 PLAYMORE) / NEO-AEG CHAFIO (2003.7.24) (NEO-CMC 7050)
****************************************/

ROM_START( samsho5 ) /* Encrypted Set */ /* MVS VERSION */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "270.p1",  0x000000, 0x400000, CRC(4a2a09e6) SHA1(2644de02cdab8ccc605488a7c76b8c9cd1d5bcb9) )
	ROM_LOAD16_WORD_SWAP( "270.p2", 0x400000, 0x400000, CRC(e0c74c85) SHA1(df24a4ee76438e40c2f04a714175a7f85cacdfe0) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "270.m1", CRC(49c9901a) SHA1(2623e9765a0eba58fee2de72851e9dc502344a3d) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "270.v1", 0x000000, 0x800000, CRC(62e434eb) SHA1(1985f5e88f8e866f9683b6cea901aa28c04b80bf) )
	ROM_LOAD( "270.v2", 0x800000, 0x800000, CRC(180f3c9a) SHA1(6d7dc2605ead6e78704efa127e7e0dfe621e2c54) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "270.c1", 0x0000000, 0x800000, CRC(14ffffac) SHA1(2ccebfdd0c7907679ae95bf6eca85b8d322441e2) )
	ROM_LOAD16_BYTE( "270.c2", 0x0000001, 0x800000, CRC(401f7299) SHA1(94e48cdf1682b1250f53c59f3f71d995e928d17b) )
	ROM_LOAD16_BYTE( "270.c3", 0x1000000, 0x800000, CRC(838f0260) SHA1(d5c8d3c6e7221d04e0b20882a847752e5ba95635) )
	ROM_LOAD16_BYTE( "270.c4", 0x1000001, 0x800000, CRC(041560a5) SHA1(d165e533699f15b1e079c82f97db3542b3a7dd66) )
	ROM_LOAD16_BYTE( "270.c5", 0x2000000, 0x800000, CRC(bd30b52d) SHA1(9f8282e684415b4045218cf764ef7d75a70e3240) )
	ROM_LOAD16_BYTE( "270.c6", 0x2000001, 0x800000, CRC(86a69c70) SHA1(526732cdb408cf680af9da39057bce6a4dfb5e13) )
	ROM_LOAD16_BYTE( "270.c7", 0x3000000, 0x800000, CRC(d28fbc3c) SHA1(a82a6ba6760fad14d9309f9147cb7d80bd6f70fc) )
	ROM_LOAD16_BYTE( "270.c8", 0x3000001, 0x800000, CRC(02c530a6) SHA1(7a3fafa6075506c6ef78cc4ec2cb72118ec83cb9) )
ROM_END

ROM_START( samsho5h ) /* Encrypted Set, Alternate Set */ /* AES VERSION */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "270h.p1",  0x000000, 0x400000, CRC(bf956089) SHA1(c538289069bf338b9fa7ecc5c9143763dbb776a8) )
	ROM_LOAD16_WORD_SWAP( "270h.p2", 0x400000, 0x400000, CRC(943a6b1d) SHA1(12bd02fc197456da6ee86f066086094cef0f4bf9) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "270.m1", CRC(49c9901a) SHA1(2623e9765a0eba58fee2de72851e9dc502344a3d) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "270.v1", 0x000000, 0x800000, CRC(62e434eb) SHA1(1985f5e88f8e866f9683b6cea901aa28c04b80bf) )
	ROM_LOAD( "270.v2", 0x800000, 0x800000, CRC(180f3c9a) SHA1(6d7dc2605ead6e78704efa127e7e0dfe621e2c54) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "270.c1", 0x0000000, 0x800000, CRC(14ffffac) SHA1(2ccebfdd0c7907679ae95bf6eca85b8d322441e2) )
	ROM_LOAD16_BYTE( "270.c2", 0x0000001, 0x800000, CRC(401f7299) SHA1(94e48cdf1682b1250f53c59f3f71d995e928d17b) )
	ROM_LOAD16_BYTE( "270.c3", 0x1000000, 0x800000, CRC(838f0260) SHA1(d5c8d3c6e7221d04e0b20882a847752e5ba95635) )
	ROM_LOAD16_BYTE( "270.c4", 0x1000001, 0x800000, CRC(041560a5) SHA1(d165e533699f15b1e079c82f97db3542b3a7dd66) )
	ROM_LOAD16_BYTE( "270.c5", 0x2000000, 0x800000, CRC(bd30b52d) SHA1(9f8282e684415b4045218cf764ef7d75a70e3240) )
	ROM_LOAD16_BYTE( "270.c6", 0x2000001, 0x800000, CRC(86a69c70) SHA1(526732cdb408cf680af9da39057bce6a4dfb5e13) )
	ROM_LOAD16_BYTE( "270.c7", 0x3000000, 0x800000, CRC(d28fbc3c) SHA1(a82a6ba6760fad14d9309f9147cb7d80bd6f70fc) )
	ROM_LOAD16_BYTE( "270.c8", 0x3000001, 0x800000, CRC(02c530a6) SHA1(7a3fafa6075506c6ef78cc4ec2cb72118ec83cb9) )
ROM_END

/****************************************
 ID-0271
 . NGM-2710
 NEO-MVS PROGBK3S (2003.10.1) (NEO-PCM2 PLAYMORE) (NEO-PVC) / NEO-MVS CHAFIO (2003.7.24) (NEO-CMC 7050)
 . NGH-2710
 NEO-AEG PROGBK3S (2003.10.6) (NEO-PCM2 PLAYMORE) (NEO-PVC) / NEO-AEG CHAFIO (2003.7.24) (NEO-CMC 7050)
****************************************/

ROM_START( kof2003 ) /* Encrypted Code + Sound + GFX Roms */ /* MVS VERSION */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "271.p1", 0x000000, 0x400000, CRC(530ecc14) SHA1(812cf7e9902af3f5e9e330b7c05c2171b139ad2b) )
	ROM_LOAD32_WORD_SWAP( "271.p2", 0x000002, 0x400000, CRC(fd568da9) SHA1(46364906a1e81dc251117e91a1a7b43af1373ada) )
	ROM_LOAD16_WORD_SWAP( "271.p3", 0x800000, 0x100000, CRC(aec5b4a9) SHA1(74087f785590eda5898ce146029818f86ced42b6) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "271.m1", CRC(f5515629) SHA1(7516bf1b0207a3c8d41dc30c478f8d8b1f71304b) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "271.v1", 0x000000, 0x800000, CRC(ffa3f8c7) SHA1(7cf4a933973ca23b7f87c81151d8659e6ec4bd20) )
	ROM_LOAD( "271.v2", 0x800000, 0x800000, CRC(5382c7d1) SHA1(1bf999705eda80ba1e7b0d6bdd010d9bfb18bd76) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271.c1", 0x0000000, 0x800000, CRC(b1dc25d0) SHA1(50adc3c60d5b4b3abd10a49db2267306c6dbd772) )
	ROM_LOAD16_BYTE( "271.c2", 0x0000001, 0x800000, CRC(d5362437) SHA1(66db36522dc09106388c707252df9fe1c88b4856) )
	ROM_LOAD16_BYTE( "271.c3", 0x1000000, 0x800000, CRC(0a1fbeab) SHA1(9fe30d36ba98d00fda010832ff2f27783dd577c1) )
	ROM_LOAD16_BYTE( "271.c4", 0x1000001, 0x800000, CRC(87b19a0c) SHA1(b72a8e7d9124ce859b5149bb4381ba481c161ea5) )
	ROM_LOAD16_BYTE( "271.c5", 0x2000000, 0x800000, CRC(704ea371) SHA1(e75b80422f0d72eac826f8ffadf79efeccaab124) )
	ROM_LOAD16_BYTE( "271.c6", 0x2000001, 0x800000, CRC(20a1164c) SHA1(c9843b37612a16fc95f6851793b1cfb5d49d811d) )
	ROM_LOAD16_BYTE( "271.c7", 0x3000000, 0x800000, CRC(189aba7f) SHA1(7152195a57ad36b28290810fe87ed8c206262ba9) )
	ROM_LOAD16_BYTE( "271.c8", 0x3000001, 0x800000, CRC(20ec4fdc) SHA1(deb5f7ec5a090e419b9d1a6a74877bee081198e2) )
ROM_END

ROM_START( kof2003h ) /* Encrypted Code + Sound + GFX Roms */ /* AES VERSION */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "271h.p1", 0x000000, 0x400000, CRC(d0d0ae3e) SHA1(538d054ac50c91694fbbfefcce548b063713e14e) )
	ROM_LOAD32_WORD_SWAP( "271h.p2", 0x000002, 0x400000, CRC(fb3f79d9) SHA1(f253d10e732d6e23ae82d74ac9269d21f69ddb4d) )
	ROM_LOAD16_WORD_SWAP( "271h.p3", 0x800000, 0x100000, CRC(232702ad) SHA1(6045046027dac1cbd4cbd14b5c1ece522bc6197f) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "271h.m1", CRC(48d9affe) SHA1(68f01560b91bbada39001ce01bdeeed5c9bb29f2) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "271.v1", 0x000000, 0x800000, CRC(ffa3f8c7) SHA1(7cf4a933973ca23b7f87c81151d8659e6ec4bd20) )
	ROM_LOAD( "271.v2", 0x800000, 0x800000, CRC(5382c7d1) SHA1(1bf999705eda80ba1e7b0d6bdd010d9bfb18bd76) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271h.c1", 0x0000000, 0x800000, CRC(efb9dd24) SHA1(1c6fe10fdbfc3306c3b7321c731f28ffdbfb15b8) )
	ROM_LOAD16_BYTE( "271h.c2", 0x0000001, 0x800000, CRC(3fb90447) SHA1(04d196de7c54c77bc75eba56d3060d46efc2d406) )
	ROM_LOAD16_BYTE( "271h.c3", 0x1000000, 0x800000, CRC(27950f28) SHA1(924f4de61c86b9efde6f1104b986886f1117055d) )
	ROM_LOAD16_BYTE( "271h.c4", 0x1000001, 0x800000, CRC(735177f8) SHA1(c95da1bc256995a7f44c9cc3312879ab6cbc15d6) )
	ROM_LOAD16_BYTE( "271h.c5", 0x2000000, 0x800000, CRC(a51b7c0f) SHA1(53dcf692b35b8d32abe5962ac799b8d641f04710) )
	ROM_LOAD16_BYTE( "271h.c6", 0x2000001, 0x800000, CRC(d5cae4e0) SHA1(248cd9eaac7a04d6b5d80c7534de90b057d566d7) )
	ROM_LOAD16_BYTE( "271h.c7", 0x3000000, 0x800000, CRC(e65ae2d0) SHA1(39744e10697d7ac539ecfcfa597e75597f321955) )
	ROM_LOAD16_BYTE( "271h.c8", 0x3000001, 0x800000, CRC(312f528c) SHA1(b4ad75f54f730ada6cb00112b74022250f055725) )
ROM_END

/****************************************
 ID-0272
 . NGM-2720
 NEO-MVS PROGBK2S (2003.10.18) (NEO-PCM2 PLAYMORE) / NEO-MVS CHAFIO (2003.7.24) (NEO-CMC 7050)
 . NGH-2720
 NEO-AEG PROGBK2S (2003.10.16) (NEO-PCM2 PLAYMORE) / NEO-MVS CHAFIO (2003.7.24) (NEO-CMC 7050)
****************************************/

ROM_START( samsh5sp ) /* Encrypted Set */ /* MVS VERSION */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "272.p1",  0x000000, 0x400000, CRC(fb7a6bba) SHA1(f68c527208d8a55ca44b0caaa8ab66b3a0ffdfe5) )
	ROM_LOAD16_WORD_SWAP( "272.p2", 0x400000, 0x400000, CRC(63492ea6) SHA1(6ba946acb62c63ed61a42fe72b7fff3828883bcc) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "272.m1", CRC(adeebf40) SHA1(8cbd63dda3fff4de38060405bf70cd9308c9e66e) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "272.v1", 0x000000, 0x800000, CRC(76a94127) SHA1(c3affd7ff1eb02345cfb755962ec173a8ec34acd) )
	ROM_LOAD( "272.v2", 0x800000, 0x800000, CRC(4ba507f1) SHA1(728d139da3fe8a391fd8be4d24bb7fdd4bf9548a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "272.c1", 0x0000000, 0x800000, CRC(4f97661a) SHA1(87f1721bae5ef16bc23c06b05e64686c396413df) )
	ROM_LOAD16_BYTE( "272.c2", 0x0000001, 0x800000, CRC(a3afda4f) SHA1(86b475fce0bc0aa04d34e31324e8c7c7c847df19) )
	ROM_LOAD16_BYTE( "272.c3", 0x1000000, 0x800000, CRC(8c3c7502) SHA1(6639020a8860d2400308e110d7277cbaf6eccc2a) )
	ROM_LOAD16_BYTE( "272.c4", 0x1000001, 0x800000, CRC(32d5e2e2) SHA1(2b5612017152afd7433aaf99951a084ef5ad6bf0) )
	ROM_LOAD16_BYTE( "272.c5", 0x2000000, 0x800000, CRC(6ce085bc) SHA1(0432b04a2265c649bba1bbd934dfb425c5d80fb1) )
	ROM_LOAD16_BYTE( "272.c6", 0x2000001, 0x800000, CRC(05c8dc8e) SHA1(da45c222893f25495a66bdb302f9b0b1de3c8ae0) )
	ROM_LOAD16_BYTE( "272.c7", 0x3000000, 0x800000, CRC(1417b742) SHA1(dfe35eb4bcd022d2f2dc544ccbbb77078f08c0aa) )
	ROM_LOAD16_BYTE( "272.c8", 0x3000001, 0x800000, CRC(d49773cd) SHA1(cd8cf3b762d381c1f8f12919579c84a7ef7efb3f) )
ROM_END

ROM_START( samsh5sph ) /* Encrypted Set */ /* AES VERSION, 2nd bugfix release */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "272h.p1",  0x000000, 0x400000, CRC(c30a08dd) SHA1(66864954017c841d7ca8490112c3aa7a71a4da70) )
	ROM_LOAD16_WORD_SWAP( "272h.p2", 0x400000, 0x400000, CRC(bd64a518) SHA1(aa259a168930f106377d680db444535411b3bce0) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "272.m1", CRC(adeebf40) SHA1(8cbd63dda3fff4de38060405bf70cd9308c9e66e) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "272.v1", 0x000000, 0x800000, CRC(76a94127) SHA1(c3affd7ff1eb02345cfb755962ec173a8ec34acd) )
	ROM_LOAD( "272.v2", 0x800000, 0x800000, CRC(4ba507f1) SHA1(728d139da3fe8a391fd8be4d24bb7fdd4bf9548a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "272.c1", 0x0000000, 0x800000, CRC(4f97661a) SHA1(87f1721bae5ef16bc23c06b05e64686c396413df) )
	ROM_LOAD16_BYTE( "272.c2", 0x0000001, 0x800000, CRC(a3afda4f) SHA1(86b475fce0bc0aa04d34e31324e8c7c7c847df19) )
	ROM_LOAD16_BYTE( "272.c3", 0x1000000, 0x800000, CRC(8c3c7502) SHA1(6639020a8860d2400308e110d7277cbaf6eccc2a) )
	ROM_LOAD16_BYTE( "272.c4", 0x1000001, 0x800000, CRC(32d5e2e2) SHA1(2b5612017152afd7433aaf99951a084ef5ad6bf0) )
	ROM_LOAD16_BYTE( "272.c5", 0x2000000, 0x800000, CRC(6ce085bc) SHA1(0432b04a2265c649bba1bbd934dfb425c5d80fb1) )
	ROM_LOAD16_BYTE( "272.c6", 0x2000001, 0x800000, CRC(05c8dc8e) SHA1(da45c222893f25495a66bdb302f9b0b1de3c8ae0) )
	ROM_LOAD16_BYTE( "272.c7", 0x3000000, 0x800000, CRC(1417b742) SHA1(dfe35eb4bcd022d2f2dc544ccbbb77078f08c0aa) )
	ROM_LOAD16_BYTE( "272.c8", 0x3000001, 0x800000, CRC(d49773cd) SHA1(cd8cf3b762d381c1f8f12919579c84a7ef7efb3f) )
ROM_END

ROM_START( samsh5spho ) /* Encrypted Set */ /* AES VERSION, 1st release */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "272ho.p1",  0x000000, 0x400000, CRC(9291794d) SHA1(66588ff9b00ffad6508b03423548984e28a3209d) )
	ROM_LOAD16_WORD_SWAP( "272ho.p2", 0x400000, 0x400000, CRC(fa1a7dd8) SHA1(62443dad76d6c1e18f515d7d4ef8e1295a4b7f1d) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "272.m1", CRC(adeebf40) SHA1(8cbd63dda3fff4de38060405bf70cd9308c9e66e) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "272.v1", 0x000000, 0x800000, CRC(76a94127) SHA1(c3affd7ff1eb02345cfb755962ec173a8ec34acd) )
	ROM_LOAD( "272.v2", 0x800000, 0x800000, CRC(4ba507f1) SHA1(728d139da3fe8a391fd8be4d24bb7fdd4bf9548a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "272.c1", 0x0000000, 0x800000, CRC(4f97661a) SHA1(87f1721bae5ef16bc23c06b05e64686c396413df) )
	ROM_LOAD16_BYTE( "272.c2", 0x0000001, 0x800000, CRC(a3afda4f) SHA1(86b475fce0bc0aa04d34e31324e8c7c7c847df19) )
	ROM_LOAD16_BYTE( "272.c3", 0x1000000, 0x800000, CRC(8c3c7502) SHA1(6639020a8860d2400308e110d7277cbaf6eccc2a) )
	ROM_LOAD16_BYTE( "272.c4", 0x1000001, 0x800000, CRC(32d5e2e2) SHA1(2b5612017152afd7433aaf99951a084ef5ad6bf0) )
	ROM_LOAD16_BYTE( "272.c5", 0x2000000, 0x800000, CRC(6ce085bc) SHA1(0432b04a2265c649bba1bbd934dfb425c5d80fb1) )
	ROM_LOAD16_BYTE( "272.c6", 0x2000001, 0x800000, CRC(05c8dc8e) SHA1(da45c222893f25495a66bdb302f9b0b1de3c8ae0) )
	ROM_LOAD16_BYTE( "272.c7", 0x3000000, 0x800000, CRC(1417b742) SHA1(dfe35eb4bcd022d2f2dc544ccbbb77078f08c0aa) )
	ROM_LOAD16_BYTE( "272.c8", 0x3000001, 0x800000, CRC(d49773cd) SHA1(cd8cf3b762d381c1f8f12919579c84a7ef7efb3f) )
ROM_END


/*************************************
 *
 *  BrezzaSoft games, licensed?
 *
 *************************************/

/****************************************
 B-J-02
 . ???-????
 MVS PROGV (2000.11.17) / NEO-MVS CHAFIO (1999.6.14) (NEO-CMC 7050)
****************************************/

ROM_START( jockeygp ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "008.p1", 0x000000, 0x100000, CRC(2fb7f388) SHA1(e3c9b03944b4c10cf5081caaf9c8be1f08c06493) )
	ROM_FILL( 0x100000, 0x100000, 0xff )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "008.m1", CRC(d163c690) SHA1(1dfd04d20c5985037f07cd01000d0b04f3a8f4f4) )

	ROM_REGION( 0x0200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "008.v1", 0x000000, 0x200000, CRC(443eadba) SHA1(3def3c22f0e276bc4c2fc7ff70ce473c08b0d2df) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "008.c1", 0x0000000, 0x800000, CRC(a9acbf18) SHA1(d55122c70cbe78c2679598dc07863e1d1d1a31df) )
	ROM_LOAD16_BYTE( "008.c2", 0x0000001, 0x800000, CRC(6289eef9) SHA1(a2ede77bb2468a2e1486d74745a22a5451026039) )
ROM_END

ROM_START( jockeygpa ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "008a.p1", 0x000000, 0x100000, CRC(b8f35532) SHA1(b46c96677f1bfe324b678112e9c614a20c550d51) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "008.m1", CRC(d163c690) SHA1(1dfd04d20c5985037f07cd01000d0b04f3a8f4f4) )

	ROM_REGION( 0x0200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "008.v1", 0x000000, 0x200000, CRC(443eadba) SHA1(3def3c22f0e276bc4c2fc7ff70ce473c08b0d2df) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "008.c1", 0x0000000, 0x800000, CRC(a9acbf18) SHA1(d55122c70cbe78c2679598dc07863e1d1d1a31df) )
	ROM_LOAD16_BYTE( "008.c2", 0x0000001, 0x800000, CRC(6289eef9) SHA1(a2ede77bb2468a2e1486d74745a22a5451026039) )
ROM_END

/****************************************
 B-V-01
 . ???-????
 MVS PROGV (2000.11.17) / MVS CHAV (2000.10.26)
****************************************/

ROM_START( vliner ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "epr.p1", 0x000000, 0x080000, CRC(72a2c043) SHA1(b34bcc10ff33e4465126a6865fe8bf6b6a3d6cee) )

	NEO_SFIX_128K( "s-1.s1", CRC(972d8c31) SHA1(41f09ef28a3791668ea304c74b8b06c117a50e9a) )

	NEO_BIOS_AUDIO_64K( "m-1.m1", CRC(9b92b7d1) SHA1(2c9b777feb9a8e43fa1bd942aba5afe3b5427d94) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", ROMREGION_ERASE00 )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "c-1.c1", 0x000000, 0x80000, CRC(5118f7c0) SHA1(b6fb6e9cbb660580d98e00780ebf248c0995145a) )
	ROM_LOAD16_BYTE( "c-2.c2", 0x000001, 0x80000, CRC(efe9b33e) SHA1(910c651aadce9bf59e51c338ceef62287756d2e8) )
ROM_END

ROM_START( vlinero ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "epr_54.p1", 0x000000, 0x080000, CRC(172efc18) SHA1(8ca739f8780a9e6fa19ac2c3e931d75871603f58) )

	NEO_SFIX_128K( "s-1.s1", CRC(972d8c31) SHA1(41f09ef28a3791668ea304c74b8b06c117a50e9a) )

	NEO_BIOS_AUDIO_64K( "m-1.m1", CRC(9b92b7d1) SHA1(2c9b777feb9a8e43fa1bd942aba5afe3b5427d94) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", ROMREGION_ERASE00 )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "c-1.c1", 0x000000, 0x80000, CRC(5118f7c0) SHA1(b6fb6e9cbb660580d98e00780ebf248c0995145a) )
	ROM_LOAD16_BYTE( "c-2.c2", 0x000001, 0x80000, CRC(efe9b33e) SHA1(910c651aadce9bf59e51c338ceef62287756d2e8) )
ROM_END


/*************************************
 *
 *  Vektorlogic games, unlicensed
 *
 *************************************/

/****************************************
 NSBP V1.0U
 PROGRAM CART REVISION 2.0 COPYRIGHT VEKTORLOGIC (C) 2004 / GRAPHICS CART REVISION 1.2 COPYRIGHT VEKTORLOGIC (C) 2004
****************************************/

// this doesn't boot, protection like kof98?
// you can force it to boot with a simple debugger trick, but then it resets when starting a game
ROM_START( sbp ) /* Unlicensed, no official game ID # */ /* MVS ONLY VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "001-003-02a.u2", 0x000000, 0x080000, CRC(d054d264) SHA1(d1b4bc626d000e0679def0545940fa75035921ab) )

	NEO_SFIX_MT_128K
	ROM_LOAD( "001-003-02b.u2", 0x000000, 0x20000, CRC(2fd04b2a) SHA1(1acb446704ab56d0a33df7c48855aa8d00fd5a3c) )
	ROM_IGNORE(0x20000)
	ROM_IGNORE(0x20000)
	ROM_IGNORE(0x20000)

	NEO_BIOS_AUDIO_512K( "001-003-01b.u1", CRC(7b1f86f7) SHA1(15b6af7f9fbd0f1f6a1ecd912200ca8d0af2da2a) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "001-003-12a.u12", 0x000000, 0x400000, CRC(c96723b9) SHA1(52eec88550781d45f84efbf9b905d7e7912e96fa) )
	ROM_LOAD( "001-003-13a.u13", 0x400000, 0x400000, CRC(08c339a5) SHA1(badc9510ae243ef2a7877977eb36efa81b1489fe) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "001-003-03b.u3", 0x000000, 0x200000, CRC(44791317) SHA1(9e773eb9aae5ee767213bd17348ff8a312e9cb16) )
	ROM_LOAD16_BYTE( "001-003-04b.u4", 0x000001, 0x200000, CRC(a3a1c0df) SHA1(3b1e5be673f7cbb04199a805b0e0de93dad8cb8c) )
ROM_END


/*************************************
 *
 *  Jamma PCB sets
 *
 *************************************/

/****************************************
 ID-2680
 . MV-0 ????
 NEO-MVH MVOBR 2003.8.4
****************************************/

ROM_START( ms5pcb ) /* Encrypted Set, JAMMA PCB */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "268.p1", 0x000000, 0x400000, CRC(d0466792) SHA1(880819933d997fab398f91061e9dbccb959ae8a1) )
	ROM_LOAD32_WORD_SWAP( "268.p2", 0x000002, 0x400000, CRC(fbf6b61e) SHA1(9ec743d5988b5e3183f37f8edf45c72a8c0c893e) )

	NEO_SFIX_MT_128K

	ROM_REGION16_BE( 0x80000, "mainbios", 0 )
	/* this contains both an ASIA and JAPAN bios, HARDDIP3 on the PCB selects which to use */
	ROM_LOAD16_WORD_SWAP( "sp-4x.sp1", 0x00000, 0x80000, CRC(b4590283) SHA1(47047ed5b6062babc0a0bebcc30e4b3f021e115a) )

	ROM_REGION( 0x80000, "audiocrypt", 0 )
	ROM_LOAD( "268.m1", 0x00000, 0x80000, CRC(4a5a6e0e) SHA1(df0f660f2465e1db7be5adfcaf5e88ad61a74a42) )
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "268c.v1", 0x000000, 0x1000000, CRC(8458afe5) SHA1(62b4c6e7db763e9ff2697bbcdb43dc5a56b48c68) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD32_WORD( "268c.c1", 0x0000000, 0x1000000, BAD_DUMP CRC(802042e8) SHA1(ff028b65f60f0b51b255a380cc47ec19fdc0c0cf) )
	ROM_LOAD32_WORD( "268c.c2", 0x0000002, 0x1000000, BAD_DUMP CRC(3b89fb9f) SHA1(cbc0729aae961f683b105ec3e1cda58b3f985abc) )
	ROM_LOAD32_WORD( "268c.c3", 0x2000000, 0x1000000, BAD_DUMP CRC(0f3f59e3) SHA1(8cc751dc7d4e94864a9ce3346f23b8f011082fcc) )
	ROM_LOAD32_WORD( "268c.c4", 0x2000002, 0x1000000, BAD_DUMP CRC(3ad8435a) SHA1(b333c8993c9b4c4ea59450ad0a3560e0b28056bc) )
ROM_END

/****************************************
 ID-2690
 . MV-0 ????
 NEO-MVH MVO 2003.6.5
****************************************/

ROM_START( svcpcb ) /* Encrypted Set, JAMMA PCB */
	ROM_REGION( 0x2000000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "269c.p1", 0x000000, 0x2000000, CRC(432cfdfc) SHA1(19b40d32188a8bace6d2d570c6cf3d2f1e31e379) )

	NEO_SFIX_MT_512K

	ROM_REGION16_BE( 0x80000, "mainbios", 0 )
	/* this contains both an ASIA and JAPAN bios, HARDDIP3 on the PCB selects which to use */
	ROM_LOAD16_WORD_SWAP( "sp-4x.sp1", 0x00000, 0x80000, CRC(b4590283) SHA1(47047ed5b6062babc0a0bebcc30e4b3f021e115a) )

	ROM_REGION( 0x80000, "audiocrypt", 0 )
	ROM_LOAD( "269.m1", 0x00000, 0x80000, CRC(f6819d00) SHA1(d3bbe09df502464f104e53501708ac6e2c1832c6) )
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "269.v1", 0x000000, 0x800000, CRC(c659b34c) SHA1(1931e8111ef43946f68699f8707334c96f753a1e) )
	ROM_LOAD( "269.v2", 0x800000, 0x800000, CRC(dd903835) SHA1(e58d38950a7a8697bb22a1cc7a371ae6664ae8f9) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "269c.c1", 0x0000000, 0x2000000, CRC(1b608f9c) SHA1(4e70ad182da2ca18815bd3936efb04a06ebce01e) )
	ROM_LOAD( "269c.c2", 0x2000000, 0x2000000, CRC(5a95f294) SHA1(6123cc7b20b494076185d27c2ffea910e124b195) )
ROM_END

/****************************************
 ID-2690
 . MV-0 ????
 NEO-MVH MVOB 2003.7.9
****************************************/

ROM_START( svcpcba ) /* Encrypted Set, JAMMA PCB */
	/* alt PCB version, this one has the same program roms as the MVS set, and different GFX / Sound rom arrangements */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "269.p1", 0x000000, 0x400000, CRC(38e2005e) SHA1(1b902905916a30969282f1399a756e32ff069097)  )
	ROM_LOAD32_WORD_SWAP( "269.p2", 0x000002, 0x400000, CRC(6d13797c) SHA1(3cb71a95cea6b006b44cac0f547df88aec0007b7)  )

	NEO_SFIX_MT_512K

	ROM_REGION16_BE( 0x80000, "mainbios", 0 )
	/* this contains both an ASIA and JAPAN bios, HARDDIP3 on the PCB selects which to use */
	ROM_LOAD16_WORD_SWAP( "sp-4x.sp1", 0x00000, 0x80000, CRC(b4590283) SHA1(47047ed5b6062babc0a0bebcc30e4b3f021e115a) )

	ROM_REGION( 0x80000, "audiocrypt", 0 )
	ROM_LOAD( "269.m1", 0x00000, 0x80000, CRC(f6819d00) SHA1(d3bbe09df502464f104e53501708ac6e2c1832c6) )
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "269ca.v1", 0x000000, 0x1000000, CRC(a6af4753) SHA1(ec4f61a526b707a7faec4653b773beb3bf3a17ba) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD32_WORD( "269ca.c1", 0x0000000, 0x1000000, CRC(e64d2b0c) SHA1(0714198c400e5c273181e4c6f906b49e35fef75d) )
	ROM_LOAD32_WORD( "269ca.c2", 0x0000002, 0x1000000, CRC(249089c2) SHA1(1c0ca19e330efe1a74b2d35a1a9a8d61481e16a9) )
	ROM_LOAD32_WORD( "269ca.c3", 0x2000000, 0x1000000, CRC(d32f2fab) SHA1(273d58cb3c9075075b1ca39a3b247a2cd545fbe7) )
	ROM_LOAD32_WORD( "269ca.c4", 0x2000002, 0x1000000, CRC(bf77e878) SHA1(e6e76f8eed0d04ee9ad39bf38ce305930b10e2c1) )
ROM_END

/****************************************
 ID-2710
 . MV-0 ????
 NEO-MVH MVOC 2003.11.3
****************************************/

ROM_START( kf2k3pcb ) /* Encrypted Set, JAMMA PCB */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "271c.p1", 0x000000, 0x400000, CRC(b9da070c) SHA1(1a26325af142a4dd221c336061761468598c4634) )
	ROM_LOAD32_WORD_SWAP( "271c.p2", 0x000002, 0x400000, CRC(da3118c4) SHA1(582e4f44f03276adecb7b2848d3b96bf6da57f1e) )
	ROM_LOAD16_WORD_SWAP( "271c.p3", 0x800000, 0x100000, CRC(5cefd0d2) SHA1(cddc3164629fed4b6f715e12b109ad35d1009355) )

	NEO_SFIX_MT(0x100000)

	ROM_REGION16_BE( 0x80000, "mainbios", 0 )
	ROM_LOAD16_WORD_SWAP( "spj.sp1", 0x00000, 0x080000, CRC(148dd727) SHA1(2cf592a16c7157de02a989675d47965f2b3a44dd) ) // encrypted

	ROM_REGION( 0x80000, "audiocrypt", 0 )
	ROM_LOAD( "271c.m1", 0x00000, 0x80000, CRC(d6bcf2bc) SHA1(df78bc95990eb8e8f3638dde6e1876354df7fe84) )
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "271c.v1", 0x000000, 0x1000000, CRC(1d96154b) SHA1(1d4e262b0d30cee79a4edc83bb9706023c736668) )

	ROM_REGION( 0x6000000, "sprites", 0 )
	ROM_LOAD32_WORD( "271c.c1", 0x0000000, 0x1000000, CRC(f5ebb327) SHA1(e4f799a54b09adcca13b1b0cf95971a1f4291b61) )
	ROM_LOAD32_WORD( "271c.c2", 0x0000002, 0x1000000, CRC(2be21620) SHA1(872c658f53bbc558e90f18d5db9cbaa82e748a6a) )
	ROM_LOAD32_WORD( "271c.c3", 0x2000000, 0x1000000, CRC(ddded4ff) SHA1(ff7b356125bc9e6637b164f5e81b13eabeb8d804) )
	ROM_LOAD32_WORD( "271c.c4", 0x2000002, 0x1000000, CRC(d85521e6) SHA1(62278fa8690972ed32aca07a4f7f97e7203d9f3a) )
	ROM_LOAD32_WORD( "271c.c5", 0x4000000, 0x1000000, CRC(18aa3540) SHA1(15e0a8c4e0927b1f7eb9bee8f532acea6818d5eb) )
	ROM_LOAD32_WORD( "271c.c6", 0x4000002, 0x1000000, CRC(1c40de87) SHA1(8d6425aed43ff6a96c88194e203df6a783286373) )
ROM_END



/*************************************
 *
 *  Bootleg sets
 *
 *************************************/

/*
    About supported sets:

    For many bootleg sets, only P's (program rom), M1 (sound driver) and S1 (text layer) roms were dumped.
    For these sets it is assumed that the original V's (sound data) and C's (gfx data) are used.
    This requires verification.

*/


/* Zintrick bootleg */

/* This Zintrick set appears to be a bootleg made from the CD version, not a genuine
   prototype the code is based on that of the NeoCD version with some minor patches,
   for example the ADK SAMPLE TEST text that appears on the screen is actually a hacked
   PROG LOAD ERROR message. The set is supported in order to distinguish the hacks from
   a real prototype should one turn up. */

ROM_START( zintrckb )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "zin-p1.bin", 0x000000, 0x100000, CRC(06c8fca7) SHA1(b7bf38965c3d0db4d7a9684d14cac94a45b4a45b))

	NEO_SFIX_128K( "zin-s1.bin", CRC(a7ab0e81) SHA1(f0649819b96cea79b05411e0b15c8edc677d79ba) )

	NEO_BIOS_AUDIO_128K( "zin-m1.bin", CRC(fd9627ca) SHA1(b640c1f1ff466f734bb1cb5d7b589cb7e8a55346) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "zin-v1.bin", 0x000000, 0x200000, CRC(c09f74f1) SHA1(d0b56a780a6eba85ff092240b1f1cc6718f17c21) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "zin-c1.bin", 0x000000, 0x200000, CRC(76aee189) SHA1(ad6929804c5b9a59aa609e6baebc6aa37e858a47) )
	ROM_LOAD16_BYTE( "zin-c2.bin", 0x000001, 0x200000, CRC(844ed4b3) SHA1(fb7cd057bdc6cbe8b78097dd124118bae7402256) )
ROM_END

/* The King of Fighters '97 bootlegs */

ROM_START( kof97pls )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kf97-p1p.bin", 0x000000, 0x100000, CRC(c01fda46) SHA1(bc6402f5082efc80a8936364c657165f19b49415) )
	ROM_LOAD16_WORD_SWAP( "kf97-p2p.bin", 0x100000, 0x400000, CRC(5502b020) SHA1(37c48198d8b3798910a44075782cd1a20b687b4a) )

	NEO_SFIX_128K( "kf97-s1p.bin", CRC(73254270) SHA1(8d06305f9d8890da1327356272b88bdd0dc089f5) )

	NEO_BIOS_AUDIO_128K( "232.m1", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "232.v1", 0x000000, 0x400000, CRC(22a2b5b5) SHA1(ebdbc977332e6d93e266755000b43857e0082965) )
	ROM_LOAD( "232.v2", 0x400000, 0x400000, CRC(2304e744) SHA1(98d283e2bcc9291a53f52afd35ef76dfb0828432) )
	ROM_LOAD( "232.v3", 0x800000, 0x400000, CRC(759eb954) SHA1(54e77c4e9e6b89458e59824e478ddc33a9c72655) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "232.c1", 0x0000000, 0x800000, CRC(5f8bf0a1) SHA1(e8b63bbc814de171fd18c5864a7fc639970c1ecf) )
	ROM_LOAD16_BYTE( "232.c2", 0x0000001, 0x800000, CRC(e4d45c81) SHA1(fdb2b9326362e27b1c7a5beb977e0bc537488186) )
	ROM_LOAD16_BYTE( "232.c3", 0x1000000, 0x800000, CRC(581d6618) SHA1(14d3124a08ded59f86932c6b28e1a4e48c564ccd) )
	ROM_LOAD16_BYTE( "232.c4", 0x1000001, 0x800000, CRC(49bb1e68) SHA1(f769c1bd1b019521111ff3f0d22c63cb1f2640ef) )
	ROM_LOAD16_BYTE( "232.c5", 0x2000000, 0x400000, CRC(34fc4e51) SHA1(b39c65f27873f71a6f5a5d1d04e5435f874472ee) )
	ROM_LOAD16_BYTE( "232.c6", 0x2000001, 0x400000, CRC(4ff4d47b) SHA1(4d5689ede24a5fe4330bd85d4d3f4eb2795308bb) )
ROM_END

ROM_START( kof97oro )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "orochi-p1.bin",  0x0000000, 0x100000, CRC(6dcb2946) SHA1(3ccb3fdf3d32a75c7fcfefff5db1f3c75054731f) )
	ROM_LOAD16_WORD_SWAP( "orochi-p21.bin", 0x0200000, 0x100000, CRC(6e1c4d8c) SHA1(f514638a599a8a582c5f4df72f6a957bab776b7e) )
	ROM_CONTINUE( 0x100000, 0x100000 )
	ROM_LOAD16_WORD_SWAP( "orochi-p29.bin", 0x0400000, 0x100000, CRC(4c7c0221) SHA1(fdd05927743cb12210b74768155bb3f59bff01b5) )
	ROM_CONTINUE( 0x300000, 0x100000 )

	NEO_SFIX_128K( "orochi-s1.bin", CRC(4ee2149a) SHA1(180a1a90021031eac1a643b769d9cdeda56518f5) )

	NEO_BIOS_AUDIO_128K( "orochi-m1.bin", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "orochi-v1.bin", 0x000000, 0x0400000, CRC(22a2b5b5) SHA1(ebdbc977332e6d93e266755000b43857e0082965) )
	ROM_LOAD( "orochi-v2.bin", 0x400000, 0x0400000, CRC(2304e744) SHA1(98d283e2bcc9291a53f52afd35ef76dfb0828432) )
	ROM_LOAD( "orochi-v3.bin", 0x800000, 0x0400000, CRC(759eb954) SHA1(54e77c4e9e6b89458e59824e478ddc33a9c72655) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	// The C1 and C2 here are reconstructed but very likely to be correct.
	ROM_LOAD16_BYTE( "orochi-c1.bin",  0x0000000, 0x1000000, BAD_DUMP CRC(f13e841c) SHA1(e24b3fb5f7e1c1f4752cad382c264f5f93e737a0) )
	ROM_LOAD16_BYTE( "orochi-c2.bin",  0x0000001, 0x1000000, BAD_DUMP CRC(2db1f6d3) SHA1(13d957c04bd69f0db140e4633c39db4a9e44eab8) )
	ROM_LOAD16_BYTE( "orochi-c51.bin", 0x2000000, 0x0200000, CRC(a90340cb) SHA1(97eaa89f0e860e2c591ca3a995fd910d8116347d) )
	ROM_LOAD16_BYTE( "orochi-c61.bin", 0x2000001, 0x0200000, CRC(188e351a) SHA1(ab724250bc07ace0873fc825b798ace934260988) )
	ROM_LOAD16_BYTE( "orochi-c52.bin", 0x2400000, 0x0200000, CRC(d4eec50a) SHA1(0930cce5346fbbd5c1524f9148d0577cbe634420) )
	ROM_LOAD16_BYTE( "orochi-c62.bin", 0x2400001, 0x0200000, CRC(031b1ad5) SHA1(d47b3452953b553348be0a55473b863ce2872f6e) )
ROM_END

ROM_START( kog )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "5232-p1.bin", 0x000000, 0x200000, CRC(d2413ec6) SHA1(c0bf409d1e714cba5fdc6f79e4c2aec805316634) )
	ROM_LOAD16_WORD_SWAP( "232.p2",  0x200000, 0x400000, CRC(158b23f6) SHA1(9744620a70513490aaf9c5eda33e5ec31222be19) )

	NEO_SFIX_128K( "5232-s1.bin", CRC(0bef69da) SHA1(80918586e694dce35c4dba796eb18abf6a070ebb) )

	NEO_BIOS_AUDIO_128K( "232.m1", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "232.v1", 0x000000, 0x400000, CRC(22a2b5b5) SHA1(ebdbc977332e6d93e266755000b43857e0082965) )
	ROM_LOAD( "232.v2", 0x400000, 0x400000, CRC(2304e744) SHA1(98d283e2bcc9291a53f52afd35ef76dfb0828432) )
	ROM_LOAD( "232.v3", 0x800000, 0x400000, CRC(759eb954) SHA1(54e77c4e9e6b89458e59824e478ddc33a9c72655) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "5232-c1a.bin", 0x0000000, 0x800000, CRC(4eab9b0a) SHA1(a6f6b755215a3f41474e0a76b5463303a522c2d3) )
	ROM_LOAD16_BYTE( "5232-c2a.bin", 0x0000001, 0x800000, CRC(697f8fd0) SHA1(5784464c2357ccef8e6e79b6298843fc3d13b39c) )
	ROM_LOAD16_BYTE( "5232-c1b.bin", 0x1000000, 0x800000, CRC(1143fdf3) SHA1(9dc5fe9a3b7599380db62095880e2d6f237a41bd) )
	ROM_LOAD16_BYTE( "5232-c2b.bin", 0x1000001, 0x800000, CRC(ea82cf8f) SHA1(3d9ab64b69cecd6b3950839ac2c6d151ad66dcf8) )
	ROM_LOAD16_BYTE( "5232-c3.bin",  0x2000000, 0x400000, CRC(abd1be07) SHA1(857eb68bbee4538770bbfa77aaa540d61ab0abcd) )
	ROM_LOAD16_BYTE( "5232-c4.bin",  0x2000001, 0x400000, CRC(d2bd967b) SHA1(c494e0a98e127d37ca360a28accc167fa50fb626) )
ROM_END

/* Shock Troopers - 2nd Squad bootleg */

ROM_START( lans2004 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "lnsq-p1.bin",  0x000000, 0x200000, CRC(b40a879a) SHA1(379f3d44b0bae430b32157fd5f4018d77b243c58) )
	ROM_LOAD16_WORD_SWAP( "lnsq-p21.bin", 0x200000, 0x200000, CRC(ecdb2d42) SHA1(0d930cd369dfbcab7778b144355e5f70874aa324) )
	ROM_LOAD16_WORD_SWAP( "lnsq-p22.bin", 0x400000, 0x200000, CRC(fac5e2e7) SHA1(5cce7226c137da80c969df00e1cda41ef9c5082c) )

	NEO_SFIX_128K( "lnsq-s1.bin", CRC(39e82897) SHA1(24a8c94dd7e70ecde8f90ea17f75b6b5d065704f) )

	NEO_BIOS_AUDIO_128K( "246-m1.bin", CRC(d0604ad1) SHA1(fae3cd52a177eadd5f5775ace957cc0f8301e65d) )

	ROM_REGION( 0xA00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "lnsq-v1.bin", 0x000000, 0x400000, CRC(4408ebc3) SHA1(e3f4d8a7e243a8cf48e97d91bbfec7829c0d9404) )
	ROM_LOAD( "lnsq-v2.bin", 0x400000, 0x400000, CRC(3d953975) SHA1(6a4ab02ab3d4416a65343cf16815007cb273f19b) )
	ROM_LOAD( "lnsq-v3.bin", 0x800000, 0x200000, CRC(437d1d8e) SHA1(95e015c21707b53ed7223eaa19f6cdcfb4d94f0c) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "lnsq-c1.bin", 0x0000000, 0x800000, CRC(b83de59f) SHA1(8cc060f9a57ab7d4238543b0bce5f5cd1d271d4f) )
	ROM_LOAD16_BYTE( "lnsq-c2.bin", 0x0000001, 0x800000, CRC(e08969fd) SHA1(c192639d023cdad64a8f53dbcda02aa8cfb4168e) )
	ROM_LOAD16_BYTE( "lnsq-c3.bin", 0x1000000, 0x800000, CRC(013f2cda) SHA1(6261111ce69dc23fbf97241131e5a6a49355d18c) )
	ROM_LOAD16_BYTE( "lnsq-c4.bin", 0x1000001, 0x800000, CRC(d8c3a758) SHA1(d19ca3be06f9fb0cb1933b1eb3da318524c3145d) )
	ROM_LOAD16_BYTE( "lnsq-c5.bin", 0x2000000, 0x800000, CRC(75500b82) SHA1(06d2afe94ea3eb3c4e523f593b8e709dd7c284a3) )
	ROM_LOAD16_BYTE( "lnsq-c6.bin", 0x2000001, 0x800000, CRC(670ac13b) SHA1(f448a144caae51b69ea19e1f43940db135d1164a) )
ROM_END

/* Garou - Mark of the Wolves bootleg */

ROM_START( garoubl ) /* bootleg of garoup */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "garou-p1.bin", 0x000000, 0x100000, CRC(fd446d59) SHA1(e37484673a935b2af76c84cd26977c751c0f8cff) )
	ROM_LOAD16_WORD_SWAP( "garou-p2.bin", 0x100000, 0x400000, CRC(3fb10a84) SHA1(4e4a4f4cd7f0ad2520c938c64c8910e6f8805eaf) )

	NEO_SFIX_128K( "garou-s1.bin", CRC(df720e33) SHA1(58d05002d4851682bd626241fa7b70f78f6f3bc8) )

	NEO_BIOS_AUDIO_512K( "garou-m1.bin", CRC(7c51d002) SHA1(01ffba6cbc8da07804f7b21d8c71c39d64a1a4e2) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "garou-v1.bin", 0x000000, 0x400000, CRC(98d736e4) SHA1(3edda9a1d45b0e38a85156d24fc8ff2f0011239b) )
	ROM_LOAD( "garou-v2.bin", 0x400000, 0x400000, CRC(eb43c03f) SHA1(83c9c168b154e60a64f1033004b2d33e218bbb8b) )
	ROM_LOAD( "garou-v3.bin", 0x800000, 0x400000, CRC(10a0f814) SHA1(e86def80d6fb2a38ebc9f3338d22f28c15ce85da) )
	ROM_LOAD( "garou-v4.bin", 0xc00000, 0x400000, CRC(8918fdd3) SHA1(60ea2104a0f993341124728d8fde0e8e937c55ef) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "garou-c1.bin", 0x0000000, 0x1000000, CRC(e2ac83fa) SHA1(186f88a85d80efbb0371bd42cca152b6b59817fb) )
	ROM_LOAD16_BYTE( "garou-c2.bin", 0x0000001, 0x1000000, CRC(7c344b24) SHA1(f8af62a917e0ce2bf8ae4f17736fdd84d55d0788) )
	ROM_LOAD16_BYTE( "garou-c3.bin", 0x2000000, 0x1000000, CRC(d3aec5a6) SHA1(c1a584909a8a1519f676aa49351742b87c18276d) )
	ROM_LOAD16_BYTE( "garou-c4.bin", 0x2000001, 0x1000000, CRC(e02a242d) SHA1(8a73826d14880303a7bea2a903e842c733178aca) )
ROM_END

/* Metal Slug 3 bootleg */

ROM_START( mslug3b6 ) /* This "Metal Slug 6" is a hack/bootleg of Metal Slug 3, the real Metal Slug 6 is on Atomiswave Hardware */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "299-p1.bin", 0x000000, 0x200000, CRC(5f2fe228) SHA1(747775a2dfc0da87ad2ddd4f57ce5b2522f23fa5) )
	ROM_LOAD16_WORD_SWAP( "299-p2.bin", 0x100000, 0x400000, CRC(193fa835) SHA1(fb1f26db7998b0bb6b1c8b92500c1596ec5dfc71) )

	NEO_SFIX_128K( "299-s1.bin", CRC(6f8b9635) SHA1(86b0c8c0ccac913c6192ed6a96c35d4e1a5e8061) )

	NEO_BIOS_AUDIO_512K( "256.m1", CRC(eaeec116) SHA1(54419dbb21edc8c4b37eaac2e7ad9496d2de037a) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "256.v1", 0x000000, 0x400000, CRC(f2690241) SHA1(fd56babc1934d10e0d27c32f032f9edda7ca8ce9) )
	ROM_LOAD( "256.v2", 0x400000, 0x400000, CRC(7e2a10bd) SHA1(0d587fb9f64cba0315ce2d8a03e2b8fe34936dff) )
	ROM_LOAD( "256.v3", 0x800000, 0x400000, CRC(0eaec17c) SHA1(c3ed613cc6993edd6fc0d62a90bcd85de8e21915) )
	ROM_LOAD( "256.v4", 0xc00000, 0x400000, CRC(9b4b22d4) SHA1(9764fbf8453e52f80aa97a46fb9cf5937ef15a31) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "256.c1", 0x0000000, 0x800000, CRC(5a79c34e) SHA1(b8aa51fa50935cae62ab3d125b723ab888691e60) )
	ROM_LOAD16_BYTE( "256.c2", 0x0000001, 0x800000, CRC(944c362c) SHA1(3843ab300f956280475469caee70135658f67089) )
	ROM_LOAD16_BYTE( "256.c3", 0x1000000, 0x800000, CRC(6e69d36f) SHA1(94e8cf42e999114b4bd8b30e0aa2f365578c4c9a) )
	ROM_LOAD16_BYTE( "256.c4", 0x1000001, 0x800000, CRC(b755b4eb) SHA1(804700a0966a48f130c434ede3f970792ea74fa5) )
	ROM_LOAD16_BYTE( "256.c5", 0x2000000, 0x800000, CRC(7aacab47) SHA1(312c1c9846175fe1a3cad51d5ae230cf674fc93d) )
	ROM_LOAD16_BYTE( "256.c6", 0x2000001, 0x800000, CRC(c698fd5d) SHA1(16818883b06849ba2f8d61bdd5e21aaf99bd8408) )
	ROM_LOAD16_BYTE( "256.c7", 0x3000000, 0x800000, CRC(cfceddd2) SHA1(7def666adf8bd1703f40c61f182fc040b6362dc9) )
	ROM_LOAD16_BYTE( "256.c8", 0x3000001, 0x800000, CRC(4d9be34c) SHA1(a737bdfa2b815aea7067e7af2636e83a9409c414) )
ROM_END

/* Nightmare in the Dark bootleg */

ROM_START( nitdbl )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "nitd-p1.bin", 0x000000, 0x080000, CRC(1a05bd1b) SHA1(7bbddef842d50b0778711063af695b168a76ff61) )

	NEO_SFIX_128K( "nitd-s1.bin", CRC(dd3bf47c) SHA1(881271caee6508b8be51bf1b59c8f1e58e08e551) )

	/* Bootleg m1 is 128k, data is identical */
	NEO_BIOS_AUDIO_512K( "260.m1", CRC(6407c5e5) SHA1(d273e154cc905b63205a17a1a6d419cac3485a92) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "nitd-v1.bin", 0x000000, 0x200000, CRC(79008868) SHA1(90bd6aaefd37341297ab1f4ae7246e52facd87d0) )
	ROM_LOAD( "nitd-v2.bin", 0x200000, 0x200000, CRC(728558f9) SHA1(309aa7c933c199b2e540a601b363e7af8744fe00) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "nitd-c1.bin", 0x000000, 0x200000, CRC(b4353190) SHA1(90d5352e243a05f5c2be4fa7475667bb56e78016) )
	ROM_LOAD16_BYTE( "nitd-c2.bin", 0x000001, 0x200000, CRC(6e27511f) SHA1(1fc5cf7786ad0f0bc7b1623acabe605ad04af3c1) )
	ROM_LOAD16_BYTE( "nitd-c3.bin", 0x400000, 0x200000, CRC(472cf075) SHA1(7cdd25019e37a3d127e68a4179c051881df19afa) )
	ROM_LOAD16_BYTE( "nitd-c4.bin", 0x400001, 0x200000, CRC(4c3926e6) SHA1(7fc54a9886dbef911f7b226e3cd20081c535e989) )
ROM_END

/* The King of Fighters 2001 bootlegs */

ROM_START( cthd2003 ) /* Protected hack/bootleg of kof2001 Phenixsoft */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "5003-p1.bin", 0x000000, 0x100000, CRC(bb7602c1) SHA1(abf329a40f34c88f7325b255e3bc090db1edaca4) )
	ROM_LOAD16_WORD_SWAP( "5003-p2.bin", 0x100000, 0x400000, CRC(adc1c22b) SHA1(271e0629989257a0d21d280c05df53df259414b1) )

	NEO_SFIX_128K( "5003-s1.bin", CRC(5ba29aab) SHA1(e7ea67268a10243693bff722e6fd2276ca540acf) )

	NEO_BIOS_AUDIO_128K( "5003-m1.bin", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

	/* sound roms are identical to kof2001 */
	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "262.v1", 0x000000, 0x400000, CRC(83d49ecf) SHA1(2f2c116e45397652e77fcf5d951fa5f71b639572) )
	ROM_LOAD( "262.v2", 0x400000, 0x400000, CRC(003f1843) SHA1(bdd58837ad542548bd4053c262f558af88e3b989) )
	ROM_LOAD( "262.v3", 0x800000, 0x400000, CRC(2ae38dbe) SHA1(4e82b7dd3b899d61907620517a5a27bdaba0725d) )
	ROM_LOAD( "262.v4", 0xc00000, 0x400000, CRC(26ec4dd9) SHA1(8bd68d95a2d913be41a51f51e48dbe3bff5924fb) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "5003-c1.bin", 0x0000000, 0x800000, CRC(68f54b67) SHA1(e2869709b11ea2846799fe431211c83e928e103e) )
	ROM_LOAD16_BYTE( "5003-c2.bin", 0x0000001, 0x800000, CRC(2f8849d5) SHA1(7ef74981aa056f5acab4ddabffd3e98b4cb970be) )
	ROM_LOAD16_BYTE( "5003-c3.bin", 0x1000000, 0x800000, CRC(ac4aff71) SHA1(c983f642e68deaa40fee3e208f2dd55f3bacbdc1) )
	ROM_LOAD16_BYTE( "5003-c4.bin", 0x1000001, 0x800000, CRC(afef5d66) SHA1(39fe785563fbea54bba88de60dcc62e2458bd74a) )
	ROM_LOAD16_BYTE( "5003-c5.bin", 0x2000000, 0x800000, CRC(c7c1ae50) SHA1(f54f5be7513a5ce2f01ab107a2b26f6a9ee1f2a9) )
	ROM_LOAD16_BYTE( "5003-c6.bin", 0x2000001, 0x800000, CRC(613197f9) SHA1(6d1fefa1be81b79e251e55a1352544c0298e4674) )
	ROM_LOAD16_BYTE( "5003-c7.bin", 0x3000000, 0x800000, CRC(64ddfe0f) SHA1(361f3f4618009bf6419961266eb9ab5002bef53c) )
	ROM_LOAD16_BYTE( "5003-c8.bin", 0x3000001, 0x800000, CRC(917a1439) SHA1(6f28d1d7c6edee1283f25e632c69204dbebe40af) )
ROM_END

ROM_START( ct2k3sp ) /* Protected hack/bootleg of kof2001 Phenixsoft */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "5003-p1sp.bin", 0x000000, 0x100000, CRC(ab5c4de0) SHA1(ca9a6bfd4c32d791ecabb34ccbf2cbf0e84f97d5) )
	ROM_LOAD16_WORD_SWAP( "5003-p2.bin",   0x100000, 0x400000, CRC(adc1c22b) SHA1(271e0629989257a0d21d280c05df53df259414b1) )

	NEO_SFIX( 0x40000, "5003-s1sp.bin", CRC(6c355ab4) SHA1(71ac2bcd3dbda8402baecc56dabc2297b148a900) )

	NEO_BIOS_AUDIO_128K( "5003-m1.bin", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

	/* sound roms are identical to kof2001 */
	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "262.v1", 0x000000, 0x400000, CRC(83d49ecf) SHA1(2f2c116e45397652e77fcf5d951fa5f71b639572) )
	ROM_LOAD( "262.v2", 0x400000, 0x400000, CRC(003f1843) SHA1(bdd58837ad542548bd4053c262f558af88e3b989) )
	ROM_LOAD( "262.v3", 0x800000, 0x400000, CRC(2ae38dbe) SHA1(4e82b7dd3b899d61907620517a5a27bdaba0725d) )
	ROM_LOAD( "262.v4", 0xc00000, 0x400000, CRC(26ec4dd9) SHA1(8bd68d95a2d913be41a51f51e48dbe3bff5924fb) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "5003-c1.bin", 0x0000000, 0x800000, CRC(68f54b67) SHA1(e2869709b11ea2846799fe431211c83e928e103e) )
	ROM_LOAD16_BYTE( "5003-c2.bin", 0x0000001, 0x800000, CRC(2f8849d5) SHA1(7ef74981aa056f5acab4ddabffd3e98b4cb970be) )
	ROM_LOAD16_BYTE( "5003-c3.bin", 0x1000000, 0x800000, CRC(ac4aff71) SHA1(c983f642e68deaa40fee3e208f2dd55f3bacbdc1) )
	ROM_LOAD16_BYTE( "5003-c4.bin", 0x1000001, 0x800000, CRC(afef5d66) SHA1(39fe785563fbea54bba88de60dcc62e2458bd74a) )
	ROM_LOAD16_BYTE( "5003-c5.bin", 0x2000000, 0x800000, CRC(c7c1ae50) SHA1(f54f5be7513a5ce2f01ab107a2b26f6a9ee1f2a9) )
	ROM_LOAD16_BYTE( "5003-c6.bin", 0x2000001, 0x800000, CRC(613197f9) SHA1(6d1fefa1be81b79e251e55a1352544c0298e4674) )
	ROM_LOAD16_BYTE( "5003-c7.bin", 0x3000000, 0x800000, CRC(64ddfe0f) SHA1(361f3f4618009bf6419961266eb9ab5002bef53c) )
	ROM_LOAD16_BYTE( "5003-c8.bin", 0x3000001, 0x800000, CRC(917a1439) SHA1(6f28d1d7c6edee1283f25e632c69204dbebe40af) )
ROM_END

ROM_START( ct2k3sa ) /* Protected hack/bootleg of kof2001 Phenixsoft, alternate version */
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "5003-p1sa.bin", 0x000000, 0x100000, CRC(013a509d) SHA1(c61c9b777e6e062b5f4ad87cdb78e9ca05e9bfb9) )
	ROM_LOAD16_WORD_SWAP( "5003-p2.bin",   0x100000, 0x400000, CRC(adc1c22b) SHA1(271e0629989257a0d21d280c05df53df259414b1) )

	NEO_SFIX_128K( "5003-s1sa.bin", CRC(4e1f7eae) SHA1(3302ad290804272447ccd2e8edd3ce968f043db1) )
	/* S1 needs redump, correct? */

	NEO_BIOS_AUDIO_128K( "5003-m1.bin", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

	/* Original set has 2x64 mbit sound roms */
	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "262.v1", 0x000000, 0x400000, CRC(83d49ecf) SHA1(2f2c116e45397652e77fcf5d951fa5f71b639572) )
	ROM_LOAD( "262.v2", 0x400000, 0x400000, CRC(003f1843) SHA1(bdd58837ad542548bd4053c262f558af88e3b989) )
	ROM_LOAD( "262.v3", 0x800000, 0x400000, CRC(2ae38dbe) SHA1(4e82b7dd3b899d61907620517a5a27bdaba0725d) )
	ROM_LOAD( "262.v4", 0xc00000, 0x400000, CRC(26ec4dd9) SHA1(8bd68d95a2d913be41a51f51e48dbe3bff5924fb) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "5003-c1.bin", 0x0000000, 0x800000, CRC(68f54b67) SHA1(e2869709b11ea2846799fe431211c83e928e103e) )
	ROM_LOAD16_BYTE( "5003-c2.bin", 0x0000001, 0x800000, CRC(2f8849d5) SHA1(7ef74981aa056f5acab4ddabffd3e98b4cb970be) )
	ROM_LOAD16_BYTE( "5003-c3.bin", 0x1000000, 0x800000, CRC(ac4aff71) SHA1(c983f642e68deaa40fee3e208f2dd55f3bacbdc1) )
	ROM_LOAD16_BYTE( "5003-c4.bin", 0x1000001, 0x800000, CRC(afef5d66) SHA1(39fe785563fbea54bba88de60dcc62e2458bd74a) )
	ROM_LOAD16_BYTE( "5003-c5.bin", 0x2000000, 0x800000, CRC(c7c1ae50) SHA1(f54f5be7513a5ce2f01ab107a2b26f6a9ee1f2a9) )
	ROM_LOAD16_BYTE( "5003-c6.bin", 0x2000001, 0x800000, CRC(613197f9) SHA1(6d1fefa1be81b79e251e55a1352544c0298e4674) )
	ROM_LOAD16_BYTE( "5003-c7.bin", 0x3000000, 0x800000, CRC(64ddfe0f) SHA1(361f3f4618009bf6419961266eb9ab5002bef53c) )
	ROM_LOAD16_BYTE( "5003-c8.bin", 0x3000001, 0x800000, CRC(917a1439) SHA1(6f28d1d7c6edee1283f25e632c69204dbebe40af) )
ROM_END

/* Metal Slug 4 bootleg */

ROM_START( ms4plus )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ms4-p1p.bin", 0x000000, 0x100000, CRC(806a6e04) SHA1(df503772d607271ea51285154c9fd68e18b143ce) )
	ROM_LOAD16_WORD_SWAP( "263.p2",  0x100000, 0x400000, CRC(fdb7aed8) SHA1(dbeaec38f44e58ffedba99e70fa1439c2bf0dfa3) )

	NEO_SFIX_128K( "ms4-s1p.bin", CRC(07ff87ce) SHA1(96ddb439de2a26bf9869015d7fb19129d40f3fd9) )

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "263.m1", CRC(46ac8228) SHA1(5aeea221050c98e4bb0f16489ce772bf1c80f787) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "263.v1", 0x000000, 0x800000, CRC(01e9b9cd) SHA1(0b045c2999449f7dab5ae8a42e957d5b6650431e) )
	ROM_LOAD( "263.v2", 0x800000, 0x800000, CRC(4ab2bf81) SHA1(77ccfa48f7e3daddef5fe5229a0093eb2f803742) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "263.c1", 0x0000000, 0x800000, CRC(84865f8a) SHA1(34467ada896eb7c7ca58658bf2a932936d8b632c) )
	ROM_LOAD16_BYTE( "263.c2", 0x0000001, 0x800000, CRC(81df97f2) SHA1(2b74493b8ec8fd49216a627aeb3db493f76124e3) )
	ROM_LOAD16_BYTE( "263.c3", 0x1000000, 0x800000, CRC(1a343323) SHA1(bbbb5232bba538c277ce2ee02e2956ca2243b787) )
	ROM_LOAD16_BYTE( "263.c4", 0x1000001, 0x800000, CRC(942cfb44) SHA1(d9b46c71726383c4581fb042e63897e5a3c92d1b) )
	ROM_LOAD16_BYTE( "263.c5", 0x2000000, 0x800000, CRC(a748854f) SHA1(2611bbedf9b5d8e82c6b2c99b88f842c46434d41) )
	ROM_LOAD16_BYTE( "263.c6", 0x2000001, 0x800000, CRC(5c8ba116) SHA1(6034db09c8706d4ddbcefc053efbc47a0953eb92) )
ROM_END

/* The King of Fighters 2002 bootlegs */

ROM_START( kof2002b )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "265.p1",  0x000000, 0x100000, CRC(9ede7323) SHA1(ad9d45498777fda9fa58e75781f48e09aee705a6) )
	ROM_LOAD16_WORD_SWAP( "2k2-p2.bin", 0x100000, 0x400000, CRC(6dbee4df) SHA1(9a9646c81b233b44213c624b898c19f83e9a07f8) )

	NEO_SFIX_128K( "2k2-s1.bin", CRC(2255f5bf) SHA1(8a82b3e9717df30b580b9d0bac0b403f8102a002) )

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "265.m1", CRC(85aaa632) SHA1(744fba4ca3bc3a5873838af886efb97a8a316104) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "265.v1", 0x000000, 0x800000, CRC(15e8f3f5) SHA1(7c9e6426b9fa6db0158baa17a6485ffce057d889) )
	ROM_LOAD( "265.v2", 0x800000, 0x800000, CRC(da41d6f9) SHA1(a43021f1e58947dcbe3c8ca5283b20b649f0409d) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "2k2-c1.bin", 0x0000000, 0x800000, CRC(f25d3d66) SHA1(eb1da3e171c126d91e851ce141840709a2f62f8a) )
	ROM_LOAD16_BYTE( "2k2-c2.bin", 0x0000001, 0x800000, CRC(e3e66f1d) SHA1(af93e9e134816353d6187a53959c6e418b83ad8d) )
	ROM_LOAD16_BYTE( "2k2-c3.bin", 0x1000000, 0x800000, CRC(8732fa30) SHA1(81c482b375c04bcfbbc69e3e2a2e9ab567c9bb78) )
	ROM_LOAD16_BYTE( "2k2-c4.bin", 0x1000001, 0x800000, CRC(0989fd40) SHA1(355d6b2c528319e41ce89952c5cf5bcc47cd6de0) )
	ROM_LOAD16_BYTE( "2k2-c5.bin", 0x2000000, 0x800000, CRC(60635cd2) SHA1(0cf2c54e003edfcdbed64e0570e6b800e7ed3c1b) )
	ROM_LOAD16_BYTE( "2k2-c6.bin", 0x2000001, 0x800000, CRC(bd736824) SHA1(d897fc8248ace145fef57d8aa393eaebc4a1ccc4) )
	ROM_LOAD16_BYTE( "2k2-c7.bin", 0x3000000, 0x800000, CRC(2da8d8cf) SHA1(ab8aa88b8e1baba88e5fc01d0f3cb55503b6c81a) )
	ROM_LOAD16_BYTE( "2k2-c8.bin", 0x3000001, 0x800000, CRC(2048404a) SHA1(d6d0f049ffc196334825328e0472b04e04bf6695) )
ROM_END

ROM_START( kf2k2pls )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "2k2-p1p.bin", 0x000000, 0x100000, CRC(3ab03781) SHA1(86946c19f1c4d9ab5cde86688d698bf63118a39d) )
	ROM_LOAD16_WORD_SWAP( "265.p2",  0x100000, 0x400000, CRC(327266b8) SHA1(98f445cc0a94f8744d74bca71cb420277622b034) )

	NEO_SFIX_128K( "2k2-s1p.bin", CRC(595e0006) SHA1(ff086bdaa6f40e9ad963e1100a27f44618d684ed) )

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "265.m1", CRC(85aaa632) SHA1(744fba4ca3bc3a5873838af886efb97a8a316104) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "265.v1", 0x000000, 0x800000, CRC(15e8f3f5) SHA1(7c9e6426b9fa6db0158baa17a6485ffce057d889) )
	ROM_LOAD( "265.v2", 0x800000, 0x800000, CRC(da41d6f9) SHA1(a43021f1e58947dcbe3c8ca5283b20b649f0409d) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "265.c1", 0x0000000, 0x800000, CRC(2b65a656) SHA1(9c46d8cf5b1ef322db442ac6a9b9406ab49206c5) )
	ROM_LOAD16_BYTE( "265.c2", 0x0000001, 0x800000, CRC(adf18983) SHA1(150cd4a5e51e9df88688469d2ea7675c2cf3658a) )
	ROM_LOAD16_BYTE( "265.c3", 0x1000000, 0x800000, CRC(875e9fd7) SHA1(28f52d56192d48bbc5dc3c97abf456bd34a58cbd) )
	ROM_LOAD16_BYTE( "265.c4", 0x1000001, 0x800000, CRC(2da13947) SHA1(f8d79ec2c236aa3d3648a4f715676899602122c1) )
	ROM_LOAD16_BYTE( "265.c5", 0x2000000, 0x800000, CRC(61bd165d) SHA1(b3424db84bc683d858fb635bc42728f9cdd89caf) )
	ROM_LOAD16_BYTE( "265.c6", 0x2000001, 0x800000, CRC(03fdd1eb) SHA1(6155c7e802062f4eafa27e414c4e73ee59b868bf) )
	ROM_LOAD16_BYTE( "265.c7", 0x3000000, 0x800000, CRC(1a2749d8) SHA1(af7d9ec1d576209826fa568f676bbff92f6d6ddd) )
	ROM_LOAD16_BYTE( "265.c8", 0x3000001, 0x800000, CRC(ab0bb549) SHA1(d23afb60b7f831f7d4a98ad3c4a00ee19877a1ce) )
ROM_END

ROM_START( kf2k2pla )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "2k2-p1pa.bin", 0x000000, 0x100000, CRC(6a3a02f3) SHA1(c9973b64e9a87fa38dde233ee3e9a73ba085b013) )
	ROM_LOAD16_WORD_SWAP( "265.p2",   0x100000, 0x400000, CRC(327266b8) SHA1(98f445cc0a94f8744d74bca71cb420277622b034) )

	NEO_SFIX_128K( "2k2-s1pa.bin", CRC(1a3ed064) SHA1(9749bb55c750e6b65d651998c2649c5fb68db68e))

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "265.m1", CRC(85aaa632) SHA1(744fba4ca3bc3a5873838af886efb97a8a316104) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "265.v1", 0x000000, 0x800000, CRC(15e8f3f5) SHA1(7c9e6426b9fa6db0158baa17a6485ffce057d889) )
	ROM_LOAD( "265.v2", 0x800000, 0x800000, CRC(da41d6f9) SHA1(a43021f1e58947dcbe3c8ca5283b20b649f0409d) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "265.c1", 0x0000000, 0x800000, CRC(2b65a656) SHA1(9c46d8cf5b1ef322db442ac6a9b9406ab49206c5) )
	ROM_LOAD16_BYTE( "265.c2", 0x0000001, 0x800000, CRC(adf18983) SHA1(150cd4a5e51e9df88688469d2ea7675c2cf3658a) )
	ROM_LOAD16_BYTE( "265.c3", 0x1000000, 0x800000, CRC(875e9fd7) SHA1(28f52d56192d48bbc5dc3c97abf456bd34a58cbd) )
	ROM_LOAD16_BYTE( "265.c4", 0x1000001, 0x800000, CRC(2da13947) SHA1(f8d79ec2c236aa3d3648a4f715676899602122c1) )
	ROM_LOAD16_BYTE( "265.c5", 0x2000000, 0x800000, CRC(61bd165d) SHA1(b3424db84bc683d858fb635bc42728f9cdd89caf) )
	ROM_LOAD16_BYTE( "265.c6", 0x2000001, 0x800000, CRC(03fdd1eb) SHA1(6155c7e802062f4eafa27e414c4e73ee59b868bf) )
	ROM_LOAD16_BYTE( "265.c7", 0x3000000, 0x800000, CRC(1a2749d8) SHA1(af7d9ec1d576209826fa568f676bbff92f6d6ddd) )
	ROM_LOAD16_BYTE( "265.c8", 0x3000001, 0x800000, CRC(ab0bb549) SHA1(d23afb60b7f831f7d4a98ad3c4a00ee19877a1ce) )
ROM_END

ROM_START( kf2k2mp )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kf02m-p1.bin", 0x000000, 0x400000, CRC(ff7c6ec0) SHA1(704c14d671dcb4cfed44d9f978a289cb7dd9d065) )
	ROM_LOAD16_WORD_SWAP( "kf02m-p2.bin", 0x400000, 0x400000, CRC(91584716) SHA1(90da863037cf775957fa154cd42536e221df5740) )

	NEO_SFIX_128K( "kf02m-s1.bin", CRC(348d6f2c) SHA1(586da8a936ebbb71af324339a4b60ec91dfa0990) )

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "265.m1", CRC(85aaa632) SHA1(744fba4ca3bc3a5873838af886efb97a8a316104) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "265.v1", 0x000000, 0x800000, CRC(15e8f3f5) SHA1(7c9e6426b9fa6db0158baa17a6485ffce057d889) )
	ROM_LOAD( "265.v2", 0x800000, 0x800000, CRC(da41d6f9) SHA1(a43021f1e58947dcbe3c8ca5283b20b649f0409d) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "265.c1", 0x0000000, 0x800000, CRC(2b65a656) SHA1(9c46d8cf5b1ef322db442ac6a9b9406ab49206c5) )
	ROM_LOAD16_BYTE( "265.c2", 0x0000001, 0x800000, CRC(adf18983) SHA1(150cd4a5e51e9df88688469d2ea7675c2cf3658a) )
	ROM_LOAD16_BYTE( "265.c3", 0x1000000, 0x800000, CRC(875e9fd7) SHA1(28f52d56192d48bbc5dc3c97abf456bd34a58cbd) )
	ROM_LOAD16_BYTE( "265.c4", 0x1000001, 0x800000, CRC(2da13947) SHA1(f8d79ec2c236aa3d3648a4f715676899602122c1) )
	ROM_LOAD16_BYTE( "265.c5", 0x2000000, 0x800000, CRC(61bd165d) SHA1(b3424db84bc683d858fb635bc42728f9cdd89caf) )
	ROM_LOAD16_BYTE( "265.c6", 0x2000001, 0x800000, CRC(03fdd1eb) SHA1(6155c7e802062f4eafa27e414c4e73ee59b868bf) )
	ROM_LOAD16_BYTE( "265.c7", 0x3000000, 0x800000, CRC(1a2749d8) SHA1(af7d9ec1d576209826fa568f676bbff92f6d6ddd) )
	ROM_LOAD16_BYTE( "265.c8", 0x3000001, 0x800000, CRC(ab0bb549) SHA1(d23afb60b7f831f7d4a98ad3c4a00ee19877a1ce) )
ROM_END

ROM_START( kf2k2mp2 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "k2k2m2p1.bin", 0x000000, 0x200000, CRC(1016806c) SHA1(a583b45e9c0d6f67b95c52e44444aabe88f68d97) )
	ROM_LOAD16_WORD_SWAP( "k2k2m2p2.bin", 0x200000, 0x400000, CRC(432fdf53) SHA1(d7e542cd84d948162c60768e40ee4ed33d8e7913) )

	NEO_SFIX_128K( "k2k2m2s1.bin", CRC(446e74c5) SHA1(efc2afb26578bad9eb21659c70eb0f827d6d1ef6) )

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "265.m1", CRC(85aaa632) SHA1(744fba4ca3bc3a5873838af886efb97a8a316104) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "265.v1", 0x000000, 0x800000, CRC(15e8f3f5) SHA1(7c9e6426b9fa6db0158baa17a6485ffce057d889) )
	ROM_LOAD( "265.v2", 0x800000, 0x800000, CRC(da41d6f9) SHA1(a43021f1e58947dcbe3c8ca5283b20b649f0409d) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "265.c1", 0x0000000, 0x800000, CRC(2b65a656) SHA1(9c46d8cf5b1ef322db442ac6a9b9406ab49206c5) )
	ROM_LOAD16_BYTE( "265.c2", 0x0000001, 0x800000, CRC(adf18983) SHA1(150cd4a5e51e9df88688469d2ea7675c2cf3658a) )
	ROM_LOAD16_BYTE( "265.c3", 0x1000000, 0x800000, CRC(875e9fd7) SHA1(28f52d56192d48bbc5dc3c97abf456bd34a58cbd) )
	ROM_LOAD16_BYTE( "265.c4", 0x1000001, 0x800000, CRC(2da13947) SHA1(f8d79ec2c236aa3d3648a4f715676899602122c1) )
	ROM_LOAD16_BYTE( "265.c5", 0x2000000, 0x800000, CRC(61bd165d) SHA1(b3424db84bc683d858fb635bc42728f9cdd89caf) )
	ROM_LOAD16_BYTE( "265.c6", 0x2000001, 0x800000, CRC(03fdd1eb) SHA1(6155c7e802062f4eafa27e414c4e73ee59b868bf) )
	ROM_LOAD16_BYTE( "265.c7", 0x3000000, 0x800000, CRC(1a2749d8) SHA1(af7d9ec1d576209826fa568f676bbff92f6d6ddd) )
	ROM_LOAD16_BYTE( "265.c8", 0x3000001, 0x800000, CRC(ab0bb549) SHA1(d23afb60b7f831f7d4a98ad3c4a00ee19877a1ce) )
ROM_END

ROM_START( kof10th )
	ROM_REGION( 0x900000, "maincpu", 0 ) // Modified
	ROM_LOAD16_WORD_SWAP( "kf10-p1.bin", 0x000000, 0x800000, CRC(b1fd0c43) SHA1(5f842a8a27be2d957fd4140d6431ae47154997bb) )

	NEO_SFIX_MT(0x40000)

	NEO_BIOS_AUDIO_128K( "kf10-m1.bin", CRC(f6fab859) SHA1(0184aa1394b9f9946d610278b53b846020dd88dc) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "kf10-v1.bin", 0x000000, 0x800000, CRC(0fc9a58d) SHA1(9d79ef00e2c2abd9f29af5521c2fbe5798bf336f) )
	ROM_LOAD( "kf10-v2.bin", 0x800000, 0x800000, CRC(b8c475a4) SHA1(10caf9c69927a223445d2c4b147864c02ce520a8) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "kf10-c1a.bin", 0x0000000, 0x400000, CRC(3bbc0364) SHA1(e8aa7ff82f151ce1db56f259377b64cceef85af0) )
	ROM_LOAD16_BYTE( "kf10-c2a.bin", 0x0000001, 0x400000, CRC(91230075) SHA1(d9098e05a7ba6008661147b6bf8bc2f494b8b72b) )
	ROM_LOAD16_BYTE( "kf10-c1b.bin", 0x0800000, 0x400000, CRC(b5abfc28) SHA1(eabf60992bb3485c95330065294071ec155bfe7c) )
	ROM_LOAD16_BYTE( "kf10-c2b.bin", 0x0800001, 0x400000, CRC(6cc4c6e1) SHA1(be824a944e745ee18efdc45c81fd496a4d624b9c) )
	ROM_LOAD16_BYTE( "kf10-c3a.bin", 0x1000000, 0x400000, CRC(5b3d4a16) SHA1(93ac1cd7739100f8c32732644f81f2a19837b131) )
	ROM_LOAD16_BYTE( "kf10-c4a.bin", 0x1000001, 0x400000, CRC(c6f3419b) SHA1(340c17a73aeb7bf8a6209f8459e6f00000075b50) )
	ROM_LOAD16_BYTE( "kf10-c3b.bin", 0x1800000, 0x400000, CRC(9d2bba19) SHA1(5ebbd0af3f83a60e33c8ccb743e3d5f5a96f1273) )
	ROM_LOAD16_BYTE( "kf10-c4b.bin", 0x1800001, 0x400000, CRC(5a4050cb) SHA1(8fd2291f349efa1ed5cd37ad4e273b60fe831a77) )
	ROM_LOAD16_BYTE( "kf10-c5a.bin", 0x2000000, 0x400000, CRC(a289d1e1) SHA1(50c7d7ebde6e118a01036cc3e40827fcd9f0d3fd) )
	ROM_LOAD16_BYTE( "kf10-c6a.bin", 0x2000001, 0x400000, CRC(e6494b5d) SHA1(18e064b9867ae0b0794065f8dbefd486620419db) )
	ROM_LOAD16_BYTE( "kf10-c5b.bin", 0x2800000, 0x400000, CRC(404fff02) SHA1(56d1b32c87ea4885e49264e8b21846e465a20e1f) )
	ROM_LOAD16_BYTE( "kf10-c6b.bin", 0x2800001, 0x400000, CRC(f2ccfc9e) SHA1(69db7fac7023785ab94ea711a72dbc2826cfe1a3) )
	ROM_LOAD16_BYTE( "kf10-c7a.bin", 0x3000000, 0x400000, CRC(be79c5a8) SHA1(ded3c5eb3571647f50533eb682c2675372ace3fb) )
	ROM_LOAD16_BYTE( "kf10-c8a.bin", 0x3000001, 0x400000, CRC(a5952ca4) SHA1(76dbb3cb45ce5a4beffa1ed29491204fc6617e42) )
	ROM_LOAD16_BYTE( "kf10-c7b.bin", 0x3800000, 0x400000, CRC(3fdb3542) SHA1(7d2050752a2064cd6729f483a0da93808e2c6033) )
	ROM_LOAD16_BYTE( "kf10-c8b.bin", 0x3800001, 0x400000, CRC(661b7a52) SHA1(0ae2ad2389134892f156337332b77adade3ddad1) )
ROM_END

ROM_START( kf10thep ) /* this is a hack of kof2002 much like the various korean hacks / bootlegs of games */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "5008-p1.bin", 0x000000, 0x200000, CRC(bf5469ba) SHA1(f05236d8fffab5836c0d27becdeeb80def32ee49) )
	ROM_LOAD16_WORD_SWAP( "5008-p2.bin", 0x200000, 0x400000, CRC(a649ec38) SHA1(5c63ed5e5c848940f587c966da4908d04cf1293c) )
	ROM_LOAD16_WORD_SWAP( "5008-p3.bin", 0x600000, 0x200000, CRC(e629e13c) SHA1(6ebe080ce01c51064cb2f4d89315ba98a45ae727) )

	NEO_SFIX_128K( "5008-s1.bin", CRC(92410064) SHA1(1fb800b46341858207d3b6961a760289fbec7faa) )

	NEO_BIOS_AUDIO_128K( "5008-m1.bin", CRC(5a47d9ad) SHA1(0197737934653acc6c97221660d789e9914f3578) )
	//NEO_BIOS_AUDIO_128K( "5004-m1.bin", CRC(f6fab859) SHA1(0184aa1394b9f9946d610278b53b846020dd88dc) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "kf10-v1.bin", 0x000000, 0x800000, CRC(0fc9a58d) SHA1(9d79ef00e2c2abd9f29af5521c2fbe5798bf336f) )
	ROM_LOAD( "kf10-v2.bin", 0x800000, 0x800000, CRC(b8c475a4) SHA1(10caf9c69927a223445d2c4b147864c02ce520a8) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "kf10-c1a.bin", 0x0000000, 0x400000, CRC(3bbc0364) SHA1(e8aa7ff82f151ce1db56f259377b64cceef85af0) )
	ROM_LOAD16_BYTE( "kf10-c2a.bin", 0x0000001, 0x400000, CRC(91230075) SHA1(d9098e05a7ba6008661147b6bf8bc2f494b8b72b) )
	ROM_LOAD16_BYTE( "kf10-c1b.bin", 0x0800000, 0x400000, CRC(b5abfc28) SHA1(eabf60992bb3485c95330065294071ec155bfe7c) )
	ROM_LOAD16_BYTE( "kf10-c2b.bin", 0x0800001, 0x400000, CRC(6cc4c6e1) SHA1(be824a944e745ee18efdc45c81fd496a4d624b9c) )
	ROM_LOAD16_BYTE( "kf10-c3a.bin", 0x1000000, 0x400000, CRC(5b3d4a16) SHA1(93ac1cd7739100f8c32732644f81f2a19837b131) )
	ROM_LOAD16_BYTE( "kf10-c4a.bin", 0x1000001, 0x400000, CRC(c6f3419b) SHA1(340c17a73aeb7bf8a6209f8459e6f00000075b50) )
	ROM_LOAD16_BYTE( "kf10-c3b.bin", 0x1800000, 0x400000, CRC(9d2bba19) SHA1(5ebbd0af3f83a60e33c8ccb743e3d5f5a96f1273) )
	ROM_LOAD16_BYTE( "kf10-c4b.bin", 0x1800001, 0x400000, CRC(5a4050cb) SHA1(8fd2291f349efa1ed5cd37ad4e273b60fe831a77) )
	ROM_LOAD16_BYTE( "kf10-c5a.bin", 0x2000000, 0x400000, CRC(a289d1e1) SHA1(50c7d7ebde6e118a01036cc3e40827fcd9f0d3fd) )
	ROM_LOAD16_BYTE( "kf10-c6a.bin", 0x2000001, 0x400000, CRC(e6494b5d) SHA1(18e064b9867ae0b0794065f8dbefd486620419db) )
	ROM_LOAD16_BYTE( "kf10-c5b.bin", 0x2800000, 0x400000, CRC(404fff02) SHA1(56d1b32c87ea4885e49264e8b21846e465a20e1f) )
	ROM_LOAD16_BYTE( "kf10-c6b.bin", 0x2800001, 0x400000, CRC(f2ccfc9e) SHA1(69db7fac7023785ab94ea711a72dbc2826cfe1a3) )
	ROM_LOAD16_BYTE( "kf10-c7a.bin", 0x3000000, 0x400000, CRC(be79c5a8) SHA1(ded3c5eb3571647f50533eb682c2675372ace3fb) )
	ROM_LOAD16_BYTE( "kf10-c8a.bin", 0x3000001, 0x400000, CRC(a5952ca4) SHA1(76dbb3cb45ce5a4beffa1ed29491204fc6617e42) )
	ROM_LOAD16_BYTE( "5008-c7b.bin", 0x3800000, 0x400000, CRC(33604ef0) SHA1(57deec23c81d5d673ce5992cef1f2567f1a2148e) )
	ROM_LOAD16_BYTE( "5008-c8b.bin", 0x3800001, 0x400000, CRC(51f6a8f8) SHA1(9ef1cdbdd125a2b430346c22b59f36902312905f) )
ROM_END

ROM_START( kf2k5uni )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "5006-p2a.bin", 0x000000, 0x400000, CRC(ced883a2) SHA1(f93db4d74ce0a73a3e9631966fee37be22470c89) )
	ROM_LOAD16_WORD_SWAP( "5006-p1.bin",  0x400000, 0x400000, CRC(72c39c46) SHA1(4ba0657de20319c0bc30c7c3bba7d7331d0ce9a7) )

	NEO_SFIX_128K( "5006-s1.bin", CRC(91f8c544) SHA1(9d16cafb9ca4bc54f31f7fd82b1be06ec8b11c79) )

	NEO_BIOS_AUDIO_128K( "5006-m1.bin", CRC(9050bfe7) SHA1(765bf3d954f775231b7ef2504bb844cd0b29e3f7) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "kf10-v1.bin", 0x000000, 0x800000, CRC(0fc9a58d) SHA1(9d79ef00e2c2abd9f29af5521c2fbe5798bf336f) )
	ROM_LOAD( "kf10-v2.bin", 0x800000, 0x800000, CRC(b8c475a4) SHA1(10caf9c69927a223445d2c4b147864c02ce520a8) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "kf10-c1a.bin", 0x0000000, 0x400000, CRC(3bbc0364) SHA1(e8aa7ff82f151ce1db56f259377b64cceef85af0) )
	ROM_LOAD16_BYTE( "kf10-c2a.bin", 0x0000001, 0x400000, CRC(91230075) SHA1(d9098e05a7ba6008661147b6bf8bc2f494b8b72b) )
	ROM_LOAD16_BYTE( "kf10-c1b.bin", 0x0800000, 0x400000, CRC(b5abfc28) SHA1(eabf60992bb3485c95330065294071ec155bfe7c) )
	ROM_LOAD16_BYTE( "kf10-c2b.bin", 0x0800001, 0x400000, CRC(6cc4c6e1) SHA1(be824a944e745ee18efdc45c81fd496a4d624b9c) )
	ROM_LOAD16_BYTE( "kf10-c3a.bin", 0x1000000, 0x400000, CRC(5b3d4a16) SHA1(93ac1cd7739100f8c32732644f81f2a19837b131) )
	ROM_LOAD16_BYTE( "kf10-c4a.bin", 0x1000001, 0x400000, CRC(c6f3419b) SHA1(340c17a73aeb7bf8a6209f8459e6f00000075b50) )
	ROM_LOAD16_BYTE( "kf10-c3b.bin", 0x1800000, 0x400000, CRC(9d2bba19) SHA1(5ebbd0af3f83a60e33c8ccb743e3d5f5a96f1273) )
	ROM_LOAD16_BYTE( "kf10-c4b.bin", 0x1800001, 0x400000, CRC(5a4050cb) SHA1(8fd2291f349efa1ed5cd37ad4e273b60fe831a77) )
	ROM_LOAD16_BYTE( "kf10-c5a.bin", 0x2000000, 0x400000, CRC(a289d1e1) SHA1(50c7d7ebde6e118a01036cc3e40827fcd9f0d3fd) )
	ROM_LOAD16_BYTE( "kf10-c6a.bin", 0x2000001, 0x400000, CRC(e6494b5d) SHA1(18e064b9867ae0b0794065f8dbefd486620419db) )
	ROM_LOAD16_BYTE( "kf10-c5b.bin", 0x2800000, 0x400000, CRC(404fff02) SHA1(56d1b32c87ea4885e49264e8b21846e465a20e1f) )
	ROM_LOAD16_BYTE( "kf10-c6b.bin", 0x2800001, 0x400000, CRC(f2ccfc9e) SHA1(69db7fac7023785ab94ea711a72dbc2826cfe1a3) )
	ROM_LOAD16_BYTE( "kf10-c7a.bin", 0x3000000, 0x400000, CRC(be79c5a8) SHA1(ded3c5eb3571647f50533eb682c2675372ace3fb) )
	ROM_LOAD16_BYTE( "kf10-c8a.bin", 0x3000001, 0x400000, CRC(a5952ca4) SHA1(76dbb3cb45ce5a4beffa1ed29491204fc6617e42) )
	ROM_LOAD16_BYTE( "kf10-c7b.bin", 0x3800000, 0x400000, CRC(3fdb3542) SHA1(7d2050752a2064cd6729f483a0da93808e2c6033) )
	ROM_LOAD16_BYTE( "kf10-c8b.bin", 0x3800001, 0x400000, CRC(661b7a52) SHA1(0ae2ad2389134892f156337332b77adade3ddad1) )
ROM_END

ROM_START( kof2k4se )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "365.p1", 0x000000, 0x080000, CRC(21a84084) SHA1(973e8a0bffa0e1f055803f663f81a8e03701802d) )
	ROM_LOAD16_WORD_SWAP( "365.p2", 0x080000, 0x080000, CRC(febb484e) SHA1(4b1838795b84f22d578ad043641df0a7bf7d9774) )
	ROM_LOAD16_WORD_SWAP( "365.p3", 0x100000, 0x400000, CRC(e6c50566) SHA1(cc6a3489a3bfeb4dcc65b6ddae0030f7e66fbabe) )

	NEO_SFIX_128K( "365.s1", CRC(a3c9b2d8) SHA1(1472d2cbd7bb73e84824ecf773924007e6117e77) )

	NEO_BIOS_AUDIO_128K( "365.m1", CRC(5a47d9ad) SHA1(0197737934653acc6c97221660d789e9914f3578) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "365.v1", 0x000000, 0x800000, CRC(e4ddfb3f) SHA1(eb8220ab01c16cf9244b7f3f9912bec0db561b85) )
	ROM_LOAD( "365.v2", 0x800000, 0x800000, CRC(b887d287) SHA1(f593a5722df6f6fac023d189a739a117e976bb2f) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "365.c1", 0x0000000, 0x800000, CRC(7a050288) SHA1(55a20c5b01e11a859f096af3f8e09986025d288f) )
	ROM_LOAD16_BYTE( "365.c2", 0x0000001, 0x800000, CRC(e924afcf) SHA1(651e974f7339d2cdcfa58c5398013197a0525b77) )
	ROM_LOAD16_BYTE( "265d.c3", 0x1000000, 0x800000, CRC(959fad0b) SHA1(63ab83ddc5f688dc8165a7ff8d262df3fcd942a2) )
	ROM_LOAD16_BYTE( "265d.c4", 0x1000001, 0x800000, CRC(efe6a468) SHA1(2a414285e48aa948b5b0d4a9333bab083b5fb853) )
	ROM_LOAD16_BYTE( "265d.c5", 0x2000000, 0x800000, CRC(74bba7c6) SHA1(e01adc7a4633bc0951b9b4f09abc07d728e9a2d9) )
	ROM_LOAD16_BYTE( "265d.c6", 0x2000001, 0x800000, CRC(e20d2216) SHA1(5d28eea7b581e780b78f391a8179f1678ee0d9a5) )
	ROM_LOAD16_BYTE( "365.c7", 0x3000000, 0x800000, CRC(fa705b2b) SHA1(f314c66876589601806352484dd8e45bc41be692) )
	ROM_LOAD16_BYTE( "365.c8", 0x3000001, 0x800000, CRC(2c912ff9) SHA1(b624a625ea3e221808b7ea43fb0b1a51d8c1853e) )
ROM_END

/* Matrimelee bootleg */

ROM_START( matrimbl )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "266.p1",  0x000000, 0x100000, CRC(5d4c2dc7) SHA1(8d723b0d28ec344eef26009b361a2b97d300dd51) )
	ROM_LOAD16_WORD_SWAP( "266.p2", 0x100000, 0x400000, CRC(a14b1906) SHA1(1daa14d73512f760ef569b06f9facb279437d1db) )

	NEO_SFIX_MT_512K

	NEO_BIOS_AUDIO_128K( "mart-m1.bin", CRC(3ea96ab1) SHA1(e5053c4312f658faed2a34e38325a22ef792d384) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "mart-v1.bin", 0x000000, 0x400000, CRC(352b0a07) SHA1(19f7cc12f3f6d0fda9c7449816c4c32367447897) )
	ROM_LOAD16_WORD_SWAP( "mart-v2.bin", 0x400000, 0x400000, CRC(1e9bd59e) SHA1(0f754e780d0ebb815a92a45ad55f85f6d0181b70) )
	ROM_LOAD( "mart-v3.bin", 0x800000, 0x400000, CRC(e8362fcc) SHA1(42d558fd80cabe22a1c09a1fa75741afbcf46b7c) )
	ROM_LOAD16_WORD_SWAP( "mart-v4.bin", 0xc00000, 0x400000, CRC(c8c79b19) SHA1(9c7a5e694d68f37a27209e1400b60b6241a04cc7) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "mart-c1.bin", 0x0000000, 0x800000, CRC(a5595656) SHA1(d86281607f22e4f2001047eaeeda99cd673c508c) )
	ROM_LOAD16_BYTE( "mart-c2.bin", 0x0000001, 0x800000, CRC(c5f7c300) SHA1(9ff5ffb750bd2e925667d84389192f92183e8677) )
	ROM_LOAD16_BYTE( "mart-c3.bin", 0x1000000, 0x800000, CRC(574efd7d) SHA1(6cac303db705fe2800701ee51de9e9fca04e6e66) )
	ROM_LOAD16_BYTE( "mart-c4.bin", 0x1000001, 0x800000, CRC(109d54d9) SHA1(22cb748b3b14317b90d9d9951297ada2bfc3a3f1) )
	ROM_LOAD16_BYTE( "mart-c5.bin", 0x2000000, 0x800000, CRC(15c9e882) SHA1(1c9f1ccaed4fdd9d8f5cc9b6fcaca3c4e328e59e) )
	ROM_LOAD16_BYTE( "mart-c6.bin", 0x2000001, 0x800000, CRC(77497b97) SHA1(c6481bea5a36f8210971fdcb4bfbe7ed93c769de) )
	ROM_LOAD16_BYTE( "mart-c7.bin", 0x3000000, 0x800000, CRC(ab481bb6) SHA1(6b2d97c5505eeb28e300b075f37f0d69ef44463a) )
	ROM_LOAD16_BYTE( "mart-c8.bin", 0x3000001, 0x800000, CRC(906cf267) SHA1(b0f2cf8887794d715f208751ddd1ed26b2c3ffdf) )
ROM_END

/* Metal Slug 5 bootleg */

ROM_START( ms5plus )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ms5-p1p.bin", 0x000000, 0x100000, CRC(106b276f) SHA1(0e840df95f3813145e5043573483c7610d2d3e68) )
	ROM_LOAD16_WORD_SWAP( "ms5-p2p.bin", 0x100000, 0x200000, CRC(d6a458e8) SHA1(c0a8bdae06d62859fb6734766ccc190eb2a809a4) )
	ROM_LOAD16_WORD_SWAP( "ms5-p3p.bin", 0x300000, 0x200000, CRC(439ec031) SHA1(f0ad8f9be7d26bc504593c1321bd23c286a221f0) )

	NEO_SFIX_128K("ms5-s1p.bin", CRC(21e04432) SHA1(10057a2aa487087f7143d1d69fdad978a6bef0f7) )

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "268.m1", CRC(4a5a6e0e) SHA1(df0f660f2465e1db7be5adfcaf5e88ad61a74a42) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "268-v1c.v1", 0x000000, 0x800000, CRC(ae31d60c) SHA1(c42285cf4e52fea74247860813e826df5aa7600a) )
	ROM_LOAD( "268-v2c.v2", 0x800000, 0x800000, CRC(c40613ed) SHA1(af889570304e2867d7dfea1e94e388c06249fb67) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "268-c1c.c1", 0x0000000, 0x800000, CRC(ab7c389a) SHA1(025a188de589500bf7637fa8e7a37ab24bf4312e) )
	ROM_LOAD16_BYTE( "268-c2c.c2", 0x0000001, 0x800000, CRC(3560881b) SHA1(493d218c92290b4770024d6ee2917c4022753b07) )
	ROM_LOAD16_BYTE( "268-c3c.c3", 0x1000000, 0x800000, CRC(3af955ea) SHA1(cf36b6ae9b0d12744b17cb7a928399214de894be) )
	ROM_LOAD16_BYTE( "268-c4c.c4", 0x1000001, 0x800000, CRC(c329c373) SHA1(5073d4079958a0ef5426885af2c9e3178f37d5e0) )
	ROM_LOAD16_BYTE( "268-c5c.c5", 0x2000000, 0x800000, CRC(959c8177) SHA1(889bda7c65d71172e7d89194d1269561888fe789) )
	ROM_LOAD16_BYTE( "268-c6c.c6", 0x2000001, 0x800000, CRC(010a831b) SHA1(aec140661e3ae35d264df416478ba15188544d91) )
	ROM_LOAD16_BYTE( "268-c7c.c7", 0x3000000, 0x800000, CRC(6d72a969) SHA1(968dd9a4d1209b770b9b85ea6532fa24d262a262) )
	ROM_LOAD16_BYTE( "268-c8c.c8", 0x3000001, 0x800000, CRC(551d720e) SHA1(ebf69e334fcaba0fda6fd432fd0970283a365d12) )
ROM_END

/* clear cart, orange pcbs
   prog board: no v encryption, uses a plcc epm7096lc84-15 for pcm, 16-bit v roms decoded by 2x 74hc245
   cha board: no c/m encryption, uses a soic palce16v8 for zmc, 5x 74hc273a for neo-273, 6x so44 m59pw064 64Mbit + 2x dip lh28f160 16MBit flash roms for gfx
   all roms are erasable flash chips, mixture of 5v and 3.3v
   produced sometime after early 2004 (going by youngest ic date code) */
ROM_START( mslug5b )
	ROM_REGION( 0x500000, "maincpu", ROMREGION_BE|ROMREGION_16BIT )
	ROM_LOAD16_WORD_SWAP( "ms5b-p1.bin", 0x000000, 0x100000, CRC(1376f43c) SHA1(7ca4a8b11c7effda2603d04e793cf664e7aa39bf) ) /* MX29F1615PC-10     16Mbit  2nd half empty */
	ROM_LOAD16_WORD_SWAP( "ms5b-p2.bin", 0x100000, 0x400000, CRC(4becfba0) SHA1(fd3708f6c8fa26133b29b4b033148dff54dc1e7d) ) /* LH28F320BJD-TTL80  32Mbit  3.3v */

	/* Scrambled */
	NEO_SFIX_128K( "ms5b-s1.bin", CRC(3a427c9f) SHA1(6c6050640adb7148d42d35e3017cc171e53ae957) ) /* W29C011A-15  1Mbit */

	/* Not encrypted */
	NEO_BIOS_AUDIO_128K( "ms5b-m1.bin", CRC(bf1601bc) SHA1(5e285c98c65acefd77e893247482af0d09f3e1e4) ) /* W29EE011-15  1Mbit */

	/* Not encrypted, odd bytes scrambled */
	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "ms5b-v1.bin", 0x000000, 0x400000, CRC(e3f9fd75) SHA1(8772d0936c45623763b92c55816d0e56dd8d2ef2) ) /* LH28F320BJD-TTL80  32Mbit  3.3v  2 bytes diff vs decrypted */
	ROM_LOAD( "ms5b-v2.bin", 0x400000, 0x400000, CRC(a53618f6) SHA1(002e37f3d45aa6153593c7939902e1a022de14c7) ) /* LH28F320BJD-TTL80  32Mbit  3.3v */
	ROM_LOAD( "ms5b-v3.bin", 0x800000, 0x400000, CRC(14f000ee) SHA1(b30df60964cc8480b78a4bc2d323cad59e44a0ae) ) /* LH28F320BJD-TTL80  32Mbit  3.3v */
	ROM_LOAD( "ms5b-v4.bin", 0xc00000, 0x400000, CRC(0ccee813) SHA1(4bc034f7f37da956b4116a2dea8a856b96e43c18) ) /* LH28F320BJD-TTL80  32Mbit  3.3v */

	/* Not encrypted, a18/a19 lines swapped */
	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "ms5b-c1.bin", 0x0000000, 0x800000, CRC(4b0e5998) SHA1(458486d579db118ec4ba4f9fce9d62fedfef949b) ) /* M59PW064  64Mbit  3.3v */
	ROM_LOAD16_BYTE( "ms5b-c2.bin", 0x0000001, 0x800000, CRC(022fc30b) SHA1(7178900acbb377c3de95338c8fae56e308327cab) ) /* M59PW064  64Mbit  3.3v */
	ROM_LOAD16_BYTE( "ms5b-c3.bin", 0x1000000, 0x800000, CRC(ead86d28) SHA1(e1db4f839972748f49dddfe3bd4b0cf2e0ddf074) ) /* M59PW064  64Mbit  3.3v */
	ROM_LOAD16_BYTE( "ms5b-c4.bin", 0x1000001, 0x800000, CRC(0be6be35) SHA1(34e20e55423cefd2b98c15061f86198b64727173) ) /* M59PW064  64Mbit  3.3v */
	ROM_LOAD16_BYTE( "ms5b-c5.bin", 0x2000000, 0x200000, CRC(2a23e569) SHA1(576370a24a8ef5ca0f8e7afa4ccdb0cb3ad9bdaa) ) /* LH28F160BJD-TTL80  16Mbit  3.3v */
	ROM_LOAD16_BYTE( "ms5b-c6.bin", 0x2000001, 0x200000, CRC(6eb6bc9e) SHA1(4e54d904b0ce34cca429b3c86ab8bf972c66336e) ) /* LH28F160BJD-TTL80  16Mbit  3.3v */
	ROM_LOAD16_BYTE( "ms5b-c7.bin", 0x3000000, 0x800000, CRC(57f4e53f) SHA1(813d98175288045c0750d45afe03c74973d70cee) ) /* M59PW064  64Mbit  3.3v */
	ROM_LOAD16_BYTE( "ms5b-c8.bin", 0x3000001, 0x800000, CRC(9d59ff7c) SHA1(ff90dc79598de0880df17624c76df81c92f267ce) ) /* M59PW064  64Mbit  3.3v */
ROM_END

/* Puzzle Bobble / Bust-A-Move (Neo-Geo) bootleg */

ROM_START( pbobblenb )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "u7", 0x000000, 0x080000, CRC(ac1e9ef3) SHA1(a2b125ee70869667431ab125bc29e768500802ad) )

	NEO_SFIX_128K( "us1", CRC(9caae538) SHA1 (cf2d90a7c1a42107c0bb8b9a61397634286dbe0a) )

	NEO_BIOS_AUDIO_128K( "um1", CRC(f424368a) SHA1 (5e5bbcaeb82bed2ee17df08f005ca20ad1030723) )

	ROM_REGION( 0x380000, "ymsnd:adpcma", 0 )
	/* 0x000000-0x1fffff empty */
	ROM_LOAD( "u8", 0x200000, 0x100000, CRC(0840cbc4) SHA1 (1adbd7aef44fa80832f63dfb8efdf69fd7256a57) )
	ROM_LOAD( "u9", 0x300000, 0x080000, CRC(0a548948) SHA1 (e1e4afd17811cb60401c14fbcf0465035165f4fb) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD16_BYTE( "uc5", 0x000000, 0x80000, CRC(e89ad494) SHA1 (69c9ea415773af94ac44c48af05d55ada222b138) )
	ROM_LOAD16_BYTE( "uc6", 0x000001, 0x80000, CRC(4b42d7eb) SHA1 (042ae50a528cea21cf07771d3915c57aa16fd5af) )
ROM_END

/* SNK vs. CAPCOM SVC CHAOS bootlegs */

ROM_START( svcboot )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "svc-p1.bin", 0x000000, 0x800000, CRC(0348f162) SHA1(c313351d68effd92aeb80ed320e4f8c26a3bb53e) )

	NEO_SFIX_MT_128K
	ROM_LOAD( "svc-s1.bin", 0x10000, 0x10000, CRC(70b44df1) SHA1(52ae3f264d7b33e94e770e6b2d0cf35a64e7dda4) )
	ROM_CONTINUE( 0x00000, 0x10000 )

	NEOGEO_BIOS

	ROM_REGION( 0x20000, "audiobios", 0 )
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) )

	ROM_REGION( 0x50000, "audiocpu", 0 )
	ROM_LOAD( "svc-m1.bin", 0x20000, 0x10000, CRC(804328c3) SHA1(f931636c563b0789d4812033a77b47bf663db43f) )
	ROM_CONTINUE( 0x00000, 0x10000 )
	ROM_COPY( "audiocpu", 0x000000, 0x10000, 0x10000 )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD16_WORD_SWAP( "svc-v2.bin", 0x000000, 0x400000, CRC(b5097287) SHA1(3ba3a9b5624879616382ed40337a3d9c50a0f314) )
	ROM_LOAD16_WORD_SWAP( "svc-v1.bin", 0x400000, 0x400000, CRC(bd3a391f) SHA1(972bf09b75e99a683ee965bec93b0da8f15d72d9) )
	ROM_LOAD16_WORD_SWAP( "svc-v4.bin", 0x800000, 0x400000, CRC(33fc0b37) SHA1(d61017d829f44c7df8795ba10c55c727d9972662) )
	ROM_LOAD16_WORD_SWAP( "svc-v3.bin", 0xc00000, 0x400000, CRC(aa9849a0) SHA1(9539b3356a070a066a89f27c287f316e7367ce2a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "svc-c1.bin", 0x0000000, 0x800000, CRC(a7826b89) SHA1(3bbe348ce54b80b56ef032ea532a18ef3cafeb11) )
	ROM_LOAD16_BYTE( "svc-c2.bin", 0x0000001, 0x800000, CRC(ed3c2089) SHA1(b5d17692f15f5a678c273589fab2e3918711135e) )
	ROM_LOAD16_BYTE( "svc-c3.bin", 0x1000000, 0x800000, CRC(71ed8063) SHA1(ea1df9e2e382a8560a06d447421844cc588f43dd) )
	ROM_LOAD16_BYTE( "svc-c4.bin", 0x1000001, 0x800000, CRC(250bde2d) SHA1(8c72dcfceef6d022ab4b73ab37cf3ac0c3940c17) )
	ROM_LOAD16_BYTE( "svc-c5.bin", 0x2000000, 0x800000, CRC(9817c082) SHA1(1bea9c7220c2b1524896c86841d6d8fd55f5d366) )
	ROM_LOAD16_BYTE( "svc-c6.bin", 0x2000001, 0x800000, CRC(2bc0307f) SHA1(8090fa82c46eb503832359093c8cc3cee3141c90) )
	ROM_LOAD16_BYTE( "svc-c7.bin", 0x3000000, 0x800000, CRC(4358d7b9) SHA1(9270b58c2abc072a046bedda72f1395df26d0714) )
	ROM_LOAD16_BYTE( "svc-c8.bin", 0x3000001, 0x800000, CRC(366deee5) SHA1(d477ad7a5987fd6c7ef2c1680fbb7c884654590e) )
ROM_END

ROM_START( svcplus )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "svc-p1p.bin", 0x000000, 0x200000, CRC(a194d842) SHA1(72b7bfa34a97632b1aa003488e074d766a6c2f08) )
	ROM_LOAD16_WORD_SWAP( "svc-p2p.bin", 0x200000, 0x200000, CRC(50c0e2b7) SHA1(97b396415ab0e692e43ddf371091e5a456712f0a) )
	ROM_LOAD16_WORD_SWAP( "svc-p3p.bin", 0x400000, 0x200000, CRC(58cdc293) SHA1(3c4f2418ec513bcc13ed33a727de11dfb98f7525) )

	NEO_SFIX_128K( "svc-s1p.bin", CRC(73344711) SHA1(04d84c4fe241b9135cd210f8ed8c725f595d11d2) )

	NEOGEO_BIOS

	ROM_REGION( 0x20000, "audiobios", 0 )
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) )

	ROM_REGION( 0x50000, "audiocpu", 0 )
	ROM_LOAD( "svc-m1.bin", 0x20000, 0x10000, CRC(804328c3) SHA1(f931636c563b0789d4812033a77b47bf663db43f) )
	ROM_CONTINUE( 0x00000, 0x10000 )
	ROM_COPY( "audiocpu", 0x000000, 0x10000, 0x10000 )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD16_WORD_SWAP( "svc-v2.bin", 0x000000, 0x400000, CRC(b5097287) SHA1(3ba3a9b5624879616382ed40337a3d9c50a0f314) )
	ROM_LOAD16_WORD_SWAP( "svc-v1.bin", 0x400000, 0x400000, CRC(bd3a391f) SHA1(972bf09b75e99a683ee965bec93b0da8f15d72d9) )
	ROM_LOAD16_WORD_SWAP( "svc-v4.bin", 0x800000, 0x400000, CRC(33fc0b37) SHA1(d61017d829f44c7df8795ba10c55c727d9972662) )
	ROM_LOAD16_WORD_SWAP( "svc-v3.bin", 0xc00000, 0x400000, CRC(aa9849a0) SHA1(9539b3356a070a066a89f27c287f316e7367ce2a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "svc-c1.bin", 0x0000000, 0x800000, CRC(a7826b89) SHA1(3bbe348ce54b80b56ef032ea532a18ef3cafeb11) )
	ROM_LOAD16_BYTE( "svc-c2.bin", 0x0000001, 0x800000, CRC(ed3c2089) SHA1(b5d17692f15f5a678c273589fab2e3918711135e) )
	ROM_LOAD16_BYTE( "svc-c3.bin", 0x1000000, 0x800000, CRC(71ed8063) SHA1(ea1df9e2e382a8560a06d447421844cc588f43dd) )
	ROM_LOAD16_BYTE( "svc-c4.bin", 0x1000001, 0x800000, CRC(250bde2d) SHA1(8c72dcfceef6d022ab4b73ab37cf3ac0c3940c17) )
	ROM_LOAD16_BYTE( "svc-c5.bin", 0x2000000, 0x800000, CRC(9817c082) SHA1(1bea9c7220c2b1524896c86841d6d8fd55f5d366) )
	ROM_LOAD16_BYTE( "svc-c6.bin", 0x2000001, 0x800000, CRC(2bc0307f) SHA1(8090fa82c46eb503832359093c8cc3cee3141c90) )
	ROM_LOAD16_BYTE( "svc-c7.bin", 0x3000000, 0x800000, CRC(4358d7b9) SHA1(9270b58c2abc072a046bedda72f1395df26d0714) )
	ROM_LOAD16_BYTE( "svc-c8.bin", 0x3000001, 0x800000, CRC(366deee5) SHA1(d477ad7a5987fd6c7ef2c1680fbb7c884654590e) )
ROM_END

ROM_START( svcplusa )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "svc-p1pl.bin", 0x000000, 0x200000, CRC(16b44144) SHA1(5eab530274b1b6f480a39a86c199da524cddfccc) )
	ROM_LOAD16_WORD_SWAP( "svc-p2pl.bin", 0x200000, 0x400000, CRC(7231ace2) SHA1(d2f13ddd5d3ee29b4b9824e8663f7ee0241f30cf) )

	NEO_SFIX_MT_128K
	ROM_LOAD( "svc-s1pl.bin", 0x10000, 0x10000, CRC(ca3c735e) SHA1(aebd15253c90432a2e0a4c40f37110c1e2176ee4) )
	ROM_CONTINUE( 0x00000, 0x10000 )

	NEOGEO_BIOS

	ROM_REGION( 0x20000, "audiobios", 0 )
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) )

	ROM_REGION( 0x50000, "audiocpu", 0 )
	ROM_LOAD( "svc-m1.bin", 0x20000, 0x10000, CRC(804328c3) SHA1(f931636c563b0789d4812033a77b47bf663db43f) )
	ROM_CONTINUE( 0x00000, 0x10000 )
	ROM_COPY( "audiocpu", 0x000000, 0x10000, 0x10000 )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD16_WORD_SWAP( "svc-v2.bin", 0x000000, 0x400000, CRC(b5097287) SHA1(3ba3a9b5624879616382ed40337a3d9c50a0f314) )
	ROM_LOAD16_WORD_SWAP( "svc-v1.bin", 0x400000, 0x400000, CRC(bd3a391f) SHA1(972bf09b75e99a683ee965bec93b0da8f15d72d9) )
	ROM_LOAD16_WORD_SWAP( "svc-v4.bin", 0x800000, 0x400000, CRC(33fc0b37) SHA1(d61017d829f44c7df8795ba10c55c727d9972662) )
	ROM_LOAD16_WORD_SWAP( "svc-v3.bin", 0xc00000, 0x400000, CRC(aa9849a0) SHA1(9539b3356a070a066a89f27c287f316e7367ce2a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "svc-c1.bin", 0x0000000, 0x800000, CRC(a7826b89) SHA1(3bbe348ce54b80b56ef032ea532a18ef3cafeb11) )
	ROM_LOAD16_BYTE( "svc-c2.bin", 0x0000001, 0x800000, CRC(ed3c2089) SHA1(b5d17692f15f5a678c273589fab2e3918711135e) )
	ROM_LOAD16_BYTE( "svc-c3.bin", 0x1000000, 0x800000, CRC(71ed8063) SHA1(ea1df9e2e382a8560a06d447421844cc588f43dd) )
	ROM_LOAD16_BYTE( "svc-c4.bin", 0x1000001, 0x800000, CRC(250bde2d) SHA1(8c72dcfceef6d022ab4b73ab37cf3ac0c3940c17) )
	ROM_LOAD16_BYTE( "svc-c5.bin", 0x2000000, 0x800000, CRC(9817c082) SHA1(1bea9c7220c2b1524896c86841d6d8fd55f5d366) )
	ROM_LOAD16_BYTE( "svc-c6.bin", 0x2000001, 0x800000, CRC(2bc0307f) SHA1(8090fa82c46eb503832359093c8cc3cee3141c90) )
	ROM_LOAD16_BYTE( "svc-c7.bin", 0x3000000, 0x800000, CRC(4358d7b9) SHA1(9270b58c2abc072a046bedda72f1395df26d0714) )
	ROM_LOAD16_BYTE( "svc-c8.bin", 0x3000001, 0x800000, CRC(366deee5) SHA1(d477ad7a5987fd6c7ef2c1680fbb7c884654590e) )
ROM_END

ROM_START( svcsplus )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "svc-p1sp.bin", 0x000000, 0x400000, CRC(2601902f) SHA1(202348a13c6480f7de37a3ee983823838822fc98) )
	ROM_LOAD16_WORD_SWAP( "svc-p2sp.bin", 0x400000, 0x400000, CRC(0ca13305) SHA1(ac8fbca71b754acbcdd11802161a62ae1cf32d88) )

	NEO_SFIX_128K( "svc-s1sp.bin", CRC(233d6439) SHA1(369024c7a2405c3144c14ac016c07c3dc0f44187) )

	NEOGEO_BIOS

	ROM_REGION( 0x20000, "audiobios", 0 )
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) )

	ROM_REGION( 0x50000, "audiocpu", 0 )
	ROM_LOAD( "svc-m1.bin", 0x20000, 0x10000, CRC(804328c3) SHA1(f931636c563b0789d4812033a77b47bf663db43f) )
	ROM_CONTINUE( 0x00000, 0x10000 )
	ROM_COPY( "audiocpu", 0x000000, 0x10000, 0x10000 )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD16_WORD_SWAP( "svc-v2.bin", 0x000000, 0x400000, CRC(b5097287) SHA1(3ba3a9b5624879616382ed40337a3d9c50a0f314) )
	ROM_LOAD16_WORD_SWAP( "svc-v1.bin", 0x400000, 0x400000, CRC(bd3a391f) SHA1(972bf09b75e99a683ee965bec93b0da8f15d72d9) )
	ROM_LOAD16_WORD_SWAP( "svc-v4.bin", 0x800000, 0x400000, CRC(33fc0b37) SHA1(d61017d829f44c7df8795ba10c55c727d9972662) )
	ROM_LOAD16_WORD_SWAP( "svc-v3.bin", 0xc00000, 0x400000, CRC(aa9849a0) SHA1(9539b3356a070a066a89f27c287f316e7367ce2a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "svc-c1.bin", 0x0000000, 0x800000, CRC(a7826b89) SHA1(3bbe348ce54b80b56ef032ea532a18ef3cafeb11) )
	ROM_LOAD16_BYTE( "svc-c2.bin", 0x0000001, 0x800000, CRC(ed3c2089) SHA1(b5d17692f15f5a678c273589fab2e3918711135e) )
	ROM_LOAD16_BYTE( "svc-c3.bin", 0x1000000, 0x800000, CRC(71ed8063) SHA1(ea1df9e2e382a8560a06d447421844cc588f43dd) )
	ROM_LOAD16_BYTE( "svc-c4.bin", 0x1000001, 0x800000, CRC(250bde2d) SHA1(8c72dcfceef6d022ab4b73ab37cf3ac0c3940c17) )
	ROM_LOAD16_BYTE( "svc-c5.bin", 0x2000000, 0x800000, CRC(9817c082) SHA1(1bea9c7220c2b1524896c86841d6d8fd55f5d366) )
	ROM_LOAD16_BYTE( "svc-c6.bin", 0x2000001, 0x800000, CRC(2bc0307f) SHA1(8090fa82c46eb503832359093c8cc3cee3141c90) )
	ROM_LOAD16_BYTE( "svc-c7.bin", 0x3000000, 0x800000, CRC(4358d7b9) SHA1(9270b58c2abc072a046bedda72f1395df26d0714) )
	ROM_LOAD16_BYTE( "svc-c8.bin", 0x3000001, 0x800000, CRC(366deee5) SHA1(d477ad7a5987fd6c7ef2c1680fbb7c884654590e) )
ROM_END

/* Samurai Shodown 5 bootleg */

ROM_START( samsho5b )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ssv.p2", 0x000000, 0x400000, CRC(5023067f) SHA1(b1d682fa7d158f19664356a919da6572e8cfeee0) )
	ROM_LOAD16_WORD_SWAP( "ssv.p1", 0x400000, 0x400000, CRC(b6cbe386) SHA1(99c2407361116c2b2c5fe72df53e05c5f99163c1) )

	NEO_SFIX_128K( "ssv.s1", CRC(70f667d0) SHA1(6d7ce62bb77eb215cc22d6c3c677accfd740aa83) )

	NEO_BIOS_AUDIO_128K( "ssv.m1", CRC(18114fb1) SHA1(016dc2f328340f3637a9bff373a20973df29f6b8) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "ssv.v1", 0x000000, 0x400000, CRC(a3609761) SHA1(6dce1dbfd228c739b3716ae1cf08fd7f925d8650) )
	ROM_LOAD( "ssv.v2", 0x400000, 0x400000, CRC(cbd6ebd5) SHA1(00211be3fa32035b0947ac65920ea8acae7bfae2) )
	ROM_LOAD( "ssv.v3", 0x800000, 0x400000, CRC(6f1c2703) SHA1(8015df3d788cb7926ebbcda64a96964fe102ba27) )
	ROM_LOAD( "ssv.v4", 0xc00000, 0x400000, CRC(5020c055) SHA1(bd1e68d1b0a47b0e2b365159e210048f8b22823a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "ssv.c1", 0x0000000, 0x1000000, CRC(9c564a01) SHA1(99dc8900fd8f56ae04fff72b34ddcaa8abe4c1be) )
	ROM_LOAD16_BYTE( "ssv.c2", 0x0000001, 0x1000000, CRC(4b73b8da) SHA1(a8b626de74cf57bbd8c222e8e24c953c9e8680f4) )
	ROM_LOAD16_BYTE( "ssv.c3", 0x2000000, 0x1000000, CRC(029f9bb5) SHA1(6296c879aa0bbd22383ceeeac0326805cbc8b4ec) )
	ROM_LOAD16_BYTE( "ssv.c4", 0x2000001, 0x1000000, CRC(75722430) SHA1(30594c30a167e75463670249df7744755e39e75b) )
ROM_END

/* The King of Fighters 2003 bootlegs */

ROM_START( kf2k3bl )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "2k3-p1.bin", 0x100000, 0x400000, CRC(92ed6ee3) SHA1(5e7e21eb40dfcc453ba73808760d5ddedd49c58a) )
	ROM_LOAD16_WORD_SWAP( "2k3-p2.bin", 0x500000, 0x200000, CRC(5d3d8bb3) SHA1(7f2341f14ca12ff5721eb038b3496228a1f34b60) )
	ROM_CONTINUE( 0x000000, 0x100000 )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "2k3-s1.bin", CRC(482c48a5) SHA1(27e2f5295a9a838e112be28dafc111893a388a16) )

	NEO_BIOS_AUDIO_128K( "2k3-m1.bin", CRC(3a4969ff) SHA1(2fc107a023a82053a8df63025829bcf12cee9610) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "271-v1c.v1", 0x000000, 0x800000, CRC(ffa3f8c7) SHA1(7cf4a933973ca23b7f87c81151d8659e6ec4bd20) )
	ROM_LOAD( "271-v2c.v2", 0x800000, 0x800000, CRC(5382c7d1) SHA1(1bf999705eda80ba1e7b0d6bdd010d9bfb18bd76) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271-c1c.c1", 0x0000000, 0x800000, CRC(b1dc25d0) SHA1(50adc3c60d5b4b3abd10a49db2267306c6dbd772) )
	ROM_LOAD16_BYTE( "271-c2c.c2", 0x0000001, 0x800000, CRC(d5362437) SHA1(66db36522dc09106388c707252df9fe1c88b4856) )
	ROM_LOAD16_BYTE( "271-c3c.c3", 0x1000000, 0x800000, CRC(0a1fbeab) SHA1(9fe30d36ba98d00fda010832ff2f27783dd577c1) )
	ROM_LOAD16_BYTE( "271-c4c.c4", 0x1000001, 0x800000, CRC(87b19a0c) SHA1(b72a8e7d9124ce859b5149bb4381ba481c161ea5) )
	ROM_LOAD16_BYTE( "271-c5c.c5", 0x2000000, 0x800000, CRC(704ea371) SHA1(e75b80422f0d72eac826f8ffadf79efeccaab124) )
	ROM_LOAD16_BYTE( "271-c6c.c6", 0x2000001, 0x800000, CRC(20a1164c) SHA1(c9843b37612a16fc95f6851793b1cfb5d49d811d) )
	ROM_LOAD16_BYTE( "271-c7c.c7", 0x3000000, 0x800000, CRC(189aba7f) SHA1(7152195a57ad36b28290810fe87ed8c206262ba9) )
	ROM_LOAD16_BYTE( "271-c8c.c8", 0x3000001, 0x800000, CRC(20ec4fdc) SHA1(deb5f7ec5a090e419b9d1a6a74877bee081198e2) )
ROM_END

ROM_START( kf2k3bla )
	ROM_REGION( 0x700000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "2k3-p1bl.bin", 0x000000, 0x100000, CRC(4ea414dd) SHA1(c242c9709c20a8cde3ad562adbe640a5dd5abcf1) )
	ROM_LOAD16_WORD_SWAP( "2k3-p3bl.bin", 0x100000, 0x400000, CRC(370acbff) SHA1(e72544de1c5e2e4f7478fc003caba9e33a306c19) )
	ROM_LOAD16_WORD_SWAP( "2k3-p2bl.bin", 0x500000, 0x200000, CRC(9c04fc52) SHA1(f41b53c79e4209373ec68276fa5941c91424bb15) )

	NEO_SFIX_128K( "2k3-s1.bin", CRC(482c48a5) SHA1(27e2f5295a9a838e112be28dafc111893a388a16) )

	NEO_BIOS_AUDIO_128K( "2k3-m1.bin", CRC(3a4969ff) SHA1(2fc107a023a82053a8df63025829bcf12cee9610) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "271-v1c.v1", 0x000000, 0x800000, CRC(ffa3f8c7) SHA1(7cf4a933973ca23b7f87c81151d8659e6ec4bd20) )
	ROM_LOAD( "271-v2c.v2", 0x800000, 0x800000, CRC(5382c7d1) SHA1(1bf999705eda80ba1e7b0d6bdd010d9bfb18bd76) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271-c1c.c1", 0x0000000, 0x800000, CRC(b1dc25d0) SHA1(50adc3c60d5b4b3abd10a49db2267306c6dbd772) )
	ROM_LOAD16_BYTE( "271-c2c.c2", 0x0000001, 0x800000, CRC(d5362437) SHA1(66db36522dc09106388c707252df9fe1c88b4856) )
	ROM_LOAD16_BYTE( "271-c3c.c3", 0x1000000, 0x800000, CRC(0a1fbeab) SHA1(9fe30d36ba98d00fda010832ff2f27783dd577c1) )
	ROM_LOAD16_BYTE( "271-c4c.c4", 0x1000001, 0x800000, CRC(87b19a0c) SHA1(b72a8e7d9124ce859b5149bb4381ba481c161ea5) )
	ROM_LOAD16_BYTE( "271-c5c.c5", 0x2000000, 0x800000, CRC(704ea371) SHA1(e75b80422f0d72eac826f8ffadf79efeccaab124) )
	ROM_LOAD16_BYTE( "271-c6c.c6", 0x2000001, 0x800000, CRC(20a1164c) SHA1(c9843b37612a16fc95f6851793b1cfb5d49d811d) )
	ROM_LOAD16_BYTE( "271-c7c.c7", 0x3000000, 0x800000, CRC(189aba7f) SHA1(7152195a57ad36b28290810fe87ed8c206262ba9) )
	ROM_LOAD16_BYTE( "271-c8c.c8", 0x3000001, 0x800000, CRC(20ec4fdc) SHA1(deb5f7ec5a090e419b9d1a6a74877bee081198e2) )
ROM_END

ROM_START( kf2k3pl )
	ROM_REGION( 0x700000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "2k3-p1pl.bin", 0x000000, 0x100000, CRC(07b84112) SHA1(0b085a928a39ff9c0745a58bfa4ce6106b5f474a) )
	ROM_LOAD16_WORD_SWAP( "2k3-p3bl.bin", 0x100000, 0x400000, CRC(370acbff) SHA1(e72544de1c5e2e4f7478fc003caba9e33a306c19) )
	ROM_LOAD16_WORD_SWAP( "2k3-p2bl.bin", 0x500000, 0x200000, CRC(9c04fc52) SHA1(f41b53c79e4209373ec68276fa5941c91424bb15) )

	NEO_SFIX_128K( "2k3-s1pl.bin", CRC(ad548a36) SHA1(7483dbe2d74a1bd1b4dc501e99e48a683416d08e) )

	NEO_BIOS_AUDIO_128K( "2k3-m1.bin", CRC(3a4969ff) SHA1(2fc107a023a82053a8df63025829bcf12cee9610) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "271-v1c.v1", 0x000000, 0x800000, CRC(ffa3f8c7) SHA1(7cf4a933973ca23b7f87c81151d8659e6ec4bd20) )
	ROM_LOAD( "271-v2c.v2", 0x800000, 0x800000, CRC(5382c7d1) SHA1(1bf999705eda80ba1e7b0d6bdd010d9bfb18bd76) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271-c1c.c1", 0x0000000, 0x800000, CRC(b1dc25d0) SHA1(50adc3c60d5b4b3abd10a49db2267306c6dbd772) )
	ROM_LOAD16_BYTE( "271-c2c.c2", 0x0000001, 0x800000, CRC(d5362437) SHA1(66db36522dc09106388c707252df9fe1c88b4856) )
	ROM_LOAD16_BYTE( "271-c3c.c3", 0x1000000, 0x800000, CRC(0a1fbeab) SHA1(9fe30d36ba98d00fda010832ff2f27783dd577c1) )
	ROM_LOAD16_BYTE( "271-c4c.c4", 0x1000001, 0x800000, CRC(87b19a0c) SHA1(b72a8e7d9124ce859b5149bb4381ba481c161ea5) )
	ROM_LOAD16_BYTE( "271-c5c.c5", 0x2000000, 0x800000, CRC(704ea371) SHA1(e75b80422f0d72eac826f8ffadf79efeccaab124) )
	ROM_LOAD16_BYTE( "271-c6c.c6", 0x2000001, 0x800000, CRC(20a1164c) SHA1(c9843b37612a16fc95f6851793b1cfb5d49d811d) )
	ROM_LOAD16_BYTE( "271-c7c.c7", 0x3000000, 0x800000, CRC(189aba7f) SHA1(7152195a57ad36b28290810fe87ed8c206262ba9) )
	ROM_LOAD16_BYTE( "271-c8c.c8", 0x3000001, 0x800000, CRC(20ec4fdc) SHA1(deb5f7ec5a090e419b9d1a6a74877bee081198e2) )
ROM_END

ROM_START( kf2k3upl )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "2k3-p1up.bin", 0x000000, 0x800000, CRC(87294c01) SHA1(21420415a6b2ba1b43ecc1934270dc085d6bd7d9) )

	NEO_SFIX_128K( "2k3-s1up.bin", CRC(e5708c0c) SHA1(5649446d3b0b1bd138b5a8b40b96a6d0f892f4d8) )

	NEO_BIOS_AUDIO_128K( "2k3-m1.bin", CRC(3a4969ff) SHA1(2fc107a023a82053a8df63025829bcf12cee9610) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "271-v1c.v1", 0x000000, 0x800000, CRC(ffa3f8c7) SHA1(7cf4a933973ca23b7f87c81151d8659e6ec4bd20) )
	ROM_LOAD( "271-v2c.v2", 0x800000, 0x800000, CRC(5382c7d1) SHA1(1bf999705eda80ba1e7b0d6bdd010d9bfb18bd76) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "271-c1c.c1", 0x0000000, 0x800000, CRC(b1dc25d0) SHA1(50adc3c60d5b4b3abd10a49db2267306c6dbd772) )
	ROM_LOAD16_BYTE( "271-c2c.c2", 0x0000001, 0x800000, CRC(d5362437) SHA1(66db36522dc09106388c707252df9fe1c88b4856) )
	ROM_LOAD16_BYTE( "271-c3c.c3", 0x1000000, 0x800000, CRC(0a1fbeab) SHA1(9fe30d36ba98d00fda010832ff2f27783dd577c1) )
	ROM_LOAD16_BYTE( "271-c4c.c4", 0x1000001, 0x800000, CRC(87b19a0c) SHA1(b72a8e7d9124ce859b5149bb4381ba481c161ea5) )
	ROM_LOAD16_BYTE( "271-c5c.c5", 0x2000000, 0x800000, CRC(704ea371) SHA1(e75b80422f0d72eac826f8ffadf79efeccaab124) )
	ROM_LOAD16_BYTE( "271-c6c.c6", 0x2000001, 0x800000, CRC(20a1164c) SHA1(c9843b37612a16fc95f6851793b1cfb5d49d811d) )
	ROM_LOAD16_BYTE( "271-c7c.c7", 0x3000000, 0x800000, CRC(189aba7f) SHA1(7152195a57ad36b28290810fe87ed8c206262ba9) )
	ROM_LOAD16_BYTE( "271-c8c.c8", 0x3000001, 0x800000, CRC(20ec4fdc) SHA1(deb5f7ec5a090e419b9d1a6a74877bee081198e2) )
ROM_END


	/* Unlicensed Prototypes */

ROM_START( diggerma ) /* Unlicensed Prototype, no official game ID # */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "dig-p1.bin", 0x000000, 0x080000, CRC(eda433d7) SHA1(abb14c66777ab0fe4ac76a402e253a49df7178d8) )

	NEO_SFIX_128K( "dig-s1.bin", CRC(9b3168f0) SHA1(9be8c625686a1482f7399e5a856cfe2fef25ec52) )

	NEO_BIOS_AUDIO_128K( "dig-m1.bin", CRC(e777a234) SHA1(9f3974ac07859337bc0203f903c40ae3f60dc1fb) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "dig-v1.bin", 0x000000, 0x080000, CRC(ee15bda4) SHA1(fe2206728e6efd02d6302869a98b196eb19a17df) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "dig-c1.bin", 0x000000, 0x080000, CRC(3db0a4ed) SHA1(6214faa883d97ea05809b6af7e0c85a236a18a28) )
	ROM_LOAD16_BYTE( "dig-c2.bin", 0x000001, 0x080000, CRC(3e632161) SHA1(83711c4286fb1d9f3f91414ac6e5fed36618033e) )
ROM_END

// MVS cart
ROM_START( lasthope )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ngdt-300.p1", 0x000000, 0x100000, CRC(3776a88f) SHA1(ea8b669da06d7c6b5ff7fa97a195f56a9253a7a1) )

	NEO_SFIX_64K( "ngdt-300.s1", CRC(0c0ff9e6) SHA1(c87d1ea8731ac1e63ab960b8182dd1043bcc10bb) )

	NEO_BIOS_AUDIO_128K( "ngdt-300.m1", CRC(113c870f) SHA1(854425eb4be0d7fa088a6c3bf6078fdd011707f5) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "ngdt-300.v1", 0x000000, 0x200000, CRC(b765bafe) SHA1(b2048c44089bf250c8dcfabb27c7981e9ee5002a) )
	ROM_LOAD( "ngdt-300.v2", 0x200000, 0x200000, CRC(9fd0d559) SHA1(09e70d5e1c6e172a33f48feb3e442515c34a8f3d) )
	ROM_LOAD( "ngdt-300.v3", 0x400000, 0x200000, CRC(6d5107e2) SHA1(4ba74836e3d0421a28af47d3d8341ac16af1d7d7) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "ngdt-300.c1", 0x000000, 0x400000, CRC(53ef41b5) SHA1(a8f1fe546403b609e12f0df211c05d7ac479d98d) )
	ROM_LOAD16_BYTE( "ngdt-300.c2", 0x000001, 0x400000, CRC(f9b15ab3) SHA1(d8ff2f43686bfc8c2f7ead3ef445e51c15dfbf16) )
	ROM_LOAD16_BYTE( "ngdt-300.c3", 0x800000, 0x400000, CRC(50cc21cf) SHA1(0350aaef480c5fa12e68e540a4c974dbf5870add) )
	ROM_LOAD16_BYTE( "ngdt-300.c4", 0x800001, 0x400000, CRC(8486ad9e) SHA1(19a2a73c825687e0cb9fd62bde00db91b5409529))
ROM_END

 /*******
  Update 
**********/
	
ROM_START( samsho5a ) /* Encrypted Set, Alternate Set */ /* MVS VERSION, Build Date: Mon Oct 20 10:11:27 2003 */
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "p1.bin", 0x000000, 0x400000, CRC(7795fffe) SHA1(2e74a4dbed553a01f1cb2f3db896375de5f1d212) ) /* EPROM */
	ROM_LOAD16_WORD_SWAP( "p2.bin", 0x400000, 0x400000, CRC(2b844fe9) SHA1(899fe6457db4a724bdd9c7e4a912eab50a5221d3) ) /* EPROM */

	ROM_Y_ZOOM

	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
	ROM_REGION( 0x20000, "fixed", 0 )
	ROM_FILL( 0x000000, 0x20000, 0x000000 )
	ROM_REGION( 0x20000, "fixedbios", 0 )
	ROM_LOAD( "sfix.sfix", 0x000000, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) )

	/* Encrypted */
	NEO_BIOS_AUDIO_ENCRYPTED_512K( "270-m1.m1", CRC(49c9901a) SHA1(2623e9765a0eba58fee2de72851e9dc502344a3d) ) /* mask rom 27c040 */

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "270-v1.v1", 0x000000, 0x800000, CRC(62e434eb) SHA1(1985f5e88f8e866f9683b6cea901aa28c04b80bf) ) /* mask rom TC5364205 */
	ROM_LOAD( "270-v2.v2", 0x800000, 0x800000, CRC(180f3c9a) SHA1(6d7dc2605ead6e78704efa127e7e0dfe621e2c54) ) /* mask rom TC5364205 */

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "270-c1.c1", 0x0000000, 0x800000, CRC(14ffffac) SHA1(2ccebfdd0c7907679ae95bf6eca85b8d322441e2) ) /* Plane 0,1 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "270-c2.c2", 0x0000001, 0x800000, CRC(401f7299) SHA1(94e48cdf1682b1250f53c59f3f71d995e928d17b) ) /* Plane 2,3 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "270-c3.c3", 0x1000000, 0x800000, CRC(838f0260) SHA1(d5c8d3c6e7221d04e0b20882a847752e5ba95635) ) /* Plane 0,1 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "270-c4.c4", 0x1000001, 0x800000, CRC(041560a5) SHA1(d165e533699f15b1e079c82f97db3542b3a7dd66) ) /* Plane 2,3 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "270-c5.c5", 0x2000000, 0x800000, CRC(bd30b52d) SHA1(9f8282e684415b4045218cf764ef7d75a70e3240) ) /* Plane 0,1 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "270-c6.c6", 0x2000001, 0x800000, CRC(86a69c70) SHA1(526732cdb408cf680af9da39057bce6a4dfb5e13) ) /* Plane 2,3 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "270-c7.c7", 0x3000000, 0x800000, CRC(d28fbc3c) SHA1(a82a6ba6760fad14d9309f9147cb7d80bd6f70fc) ) /* Plane 0,1 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "270-c8.c8", 0x3000001, 0x800000, CRC(02c530a6) SHA1(7a3fafa6075506c6ef78cc4ec2cb72118ec83cb9) ) /* Plane 2,3 */ /* mask rom TC5364205 */
ROM_END

ROM_START( sengoku3a ) /* Original Version - Encrypted GFX */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "261-pg1.p1", 0x100000, 0x100000, CRC(5b557201) SHA1(d01421d1dc80fe7d2a46b9f79c0f344b3c81c1e7) ) /* mask rom TC5316200 */
	ROM_CONTINUE( 0x000000, 0x100000 )

	ROM_Y_ZOOM

	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
	ROM_REGION( 0x20000, "fixed", 0 )
	ROM_FILL( 0x000000, 0x20000, 0x000000 )
	ROM_REGION( 0x20000, "fixedbios", 0 )
	ROM_LOAD( "sfix.sfix", 0x000000, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) )

	NEO_BIOS_AUDIO_512K( "261-m1.m1", CRC(7d501c39) SHA1(8e6bcc428f5ac7532d9c9be7e07ad0821461a080) ) /* mask rom TC534000 */

	ROM_REGION( 0x0e00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "261-v1.v1", 0x000000, 0x400000, CRC(64c30081) SHA1(f9ebd20cf59b72e864b7274c1bdb6d99ecaf4595) ) /* mask rom TC5332204 */
	ROM_LOAD( "261-v2.v2", 0x400000, 0x400000, CRC(392a9c47) SHA1(7ab90a54089236ca6c3ef1af8e566a8025d38159) ) /* mask rom TC5332204 */
	ROM_LOAD( "261-v3.v3", 0x800000, 0x400000, CRC(c1a7ebe3) SHA1(1d7bb481451f5ee0457e954bb5210300182c3c9c) ) /* mask rom TC5332204 */
	ROM_LOAD( "261-v4.v4", 0xc00000, 0x200000, CRC(9000d085) SHA1(11157b355ab4eb6627e9f322ed875332d3d77349) ) /* mask rom TC5316200 */

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "261-c1.c1", 0x0000000, 0x800000, CRC(ded84d9c) SHA1(d960523b813d4fae06d716298d4e431a5c77a0c5) ) /* Plane 0,1 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "261-c2.c2", 0x0000001, 0x800000, CRC(b8eb4348) SHA1(619d24312549932959481fa58f43f11c048e1ca5) ) /* Plane 2,3 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "261-c3.c3", 0x1000000, 0x800000, CRC(84e2034a) SHA1(38ec4ae4b86933a25c9a03799b8cade4b1346401) ) /* Plane 0,1 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "261-c4.c4", 0x1000001, 0x800000, CRC(0b45ae53) SHA1(a19fb21408ab633aee8bbf38bf43b5e26766b355) ) /* Plane 2,3 */ /* mask rom TC5364205 */
ROM_END

ROM_START( vlinernw ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "epr_7a.p1", 0x000000, 0x080000, CRC(052f93ed) SHA1(3a5330073d21fd068d44956680cfae7faa4f3951) ) /* AM27C400 */

	NEO_SFIX_128K( "s-1.s1", CRC(972d8c31) SHA1(41f09ef28a3791668ea304c74b8b06c117a50e9a) )

	NEO_BIOS_AUDIO_64K( "m-1.m1", CRC(9b92b7d1) SHA1(2c9b777feb9a8e43fa1bd942aba5afe3b5427d94) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", ROMREGION_ERASE00 )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "c-1.c1", 0x000000, 0x80000, CRC(5118f7c0) SHA1(b6fb6e9cbb660580d98e00780ebf248c0995145a) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "c-2.c2", 0x000001, 0x80000, CRC(efe9b33e) SHA1(910c651aadce9bf59e51c338ceef62287756d2e8) ) /* Plane 2,3 */
ROM_END

ROM_START( vliner7e ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "epr_7e.p1", 0x000000, 0x080000, CRC(49a94db5) SHA1(5e3066ebe3afde9e59444b8c6e092a3713a173c0) ) /* AM27C400 */

	NEO_SFIX_128K( "s-1.s1", CRC(972d8c31) SHA1(41f09ef28a3791668ea304c74b8b06c117a50e9a) )

	NEO_BIOS_AUDIO_64K( "m-1.m1", CRC(9b92b7d1) SHA1(2c9b777feb9a8e43fa1bd942aba5afe3b5427d94) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", ROMREGION_ERASE00 )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "c-1.c1", 0x000000, 0x80000, CRC(5118f7c0) SHA1(b6fb6e9cbb660580d98e00780ebf248c0995145a) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "c-2.c2", 0x000001, 0x80000, CRC(efe9b33e) SHA1(910c651aadce9bf59e51c338ceef62287756d2e8) ) /* Plane 2,3 */
ROM_END

ROM_START( vliner6e ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "epr_6e.p1", 0x000000, 0x080000, CRC(72a2c043) SHA1(b34bcc10ff33e4465126a6865fe8bf6b6a3d6cee) ) /* AM27C400 */

	NEO_SFIX_128K( "s-1.s1", CRC(972d8c31) SHA1(41f09ef28a3791668ea304c74b8b06c117a50e9a) )

	NEO_BIOS_AUDIO_64K( "m-1.m1", CRC(9b92b7d1) SHA1(2c9b777feb9a8e43fa1bd942aba5afe3b5427d94) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", ROMREGION_ERASE00 )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "c-1.c1", 0x000000, 0x80000, CRC(5118f7c0) SHA1(b6fb6e9cbb660580d98e00780ebf248c0995145a) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "c-2.c2", 0x000001, 0x80000, CRC(efe9b33e) SHA1(910c651aadce9bf59e51c338ceef62287756d2e8) ) /* Plane 2,3 */
ROM_END

ROM_START( vliner54 ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "epr_54.p1", 0x000000, 0x080000, CRC(172efc18) SHA1(8ca739f8780a9e6fa19ac2c3e931d75871603f58) )

	NEO_SFIX_128K( "s-1.s1", CRC(972d8c31) SHA1(41f09ef28a3791668ea304c74b8b06c117a50e9a) )

	NEO_BIOS_AUDIO_64K( "m-1.m1", CRC(9b92b7d1) SHA1(2c9b777feb9a8e43fa1bd942aba5afe3b5427d94) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", ROMREGION_ERASE00 )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "c-1.c1", 0x000000, 0x80000, CRC(5118f7c0) SHA1(b6fb6e9cbb660580d98e00780ebf248c0995145a) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "c-2.c2", 0x000001, 0x80000, CRC(efe9b33e) SHA1(910c651aadce9bf59e51c338ceef62287756d2e8) ) /* Plane 2,3 */
ROM_END

ROM_START( vliner53 ) /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "epr_53.p1", 0x000000, 0x080000, CRC(e263dce8) SHA1(c95e5b77c99828ee1b849d000a69fdd6bde502f8) )

	NEO_SFIX_128K( "s-1.s1", CRC(972d8c31) SHA1(41f09ef28a3791668ea304c74b8b06c117a50e9a) )

	NEO_BIOS_AUDIO_64K( "m-1.m1", CRC(9b92b7d1) SHA1(2c9b777feb9a8e43fa1bd942aba5afe3b5427d94) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", ROMREGION_ERASE00 )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "c-1.c1", 0x000000, 0x80000, CRC(5118f7c0) SHA1(b6fb6e9cbb660580d98e00780ebf248c0995145a) ) /* Plane 0,1 */
	ROM_LOAD16_BYTE( "c-2.c2", 0x000001, 0x80000, CRC(efe9b33e) SHA1(910c651aadce9bf59e51c338ceef62287756d2e8) ) /* Plane 2,3 */
ROM_END

ROM_START( wh2h ) /* AES VERSION */
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "057-pg1.p1", 0x100000, 0x100000, CRC(cde9aff5) SHA1(003f79cbff1383b59588ccee4b372027e506235c) ) /* TC5316200 */
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "057-s1.s1", CRC(fcaeb3a4) SHA1(1f3f85e38b8552333261c04ae5af0d6e3b310622) ) /* TC531000 */

	NEO_BIOS_AUDIO_128K( "057-m1.m1", CRC(8fa3bc77) SHA1(982f92978671e4ee66630948e6bb7565b37b5dc0) ) /* TC531001 */

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "057-v1.v1", 0x000000, 0x200000, CRC(8877e301) SHA1(1bab988d74ea8fd12db201c257ec844622cf5f4e) ) /* TC5316200 */
	ROM_LOAD( "057-v2.v2", 0x200000, 0x200000, CRC(c1317ff4) SHA1(4c28b2b5998abaeaa5143f2f3a9ba52c6041f4f3) ) /* TC5316200 */

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "057-c1.c1", 0x000000, 0x200000, CRC(21c6bb91) SHA1(a2c17d0c91dd59528d8fa7fe110af8b20b25ff99) ) /* Plane 0,1 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "057-c2.c2", 0x000001, 0x200000, CRC(a3999925) SHA1(0ee861a77850d378d03c1bf00b9692abd860c759) ) /* Plane 2,3 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "057-c3.c3", 0x400000, 0x200000, CRC(b725a219) SHA1(4857687d156a9150a69b97d2729245a51c144a0c) ) /* Plane 0,1 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "057-c4.c4", 0x400001, 0x200000, CRC(8d96425e) SHA1(0f79c868a6a33ad25e38d842f30ec4440d809033) ) /* Plane 2,3 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "057-c5.c5", 0x800000, 0x200000, CRC(b20354af) SHA1(da7609fd467f2f4d71d92970f438a04d11ab1cc1) ) /* Plane 0,1 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "057-c6.c6", 0x800001, 0x200000, CRC(b13d1de3) SHA1(7d749c23a33d90fe50279e884540d71cf1aaaa6b) ) /* Plane 2,3 */ /* TC5316200 */
ROM_END

ROM_START( rbff1k ) /* KOREAN VERSION */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "095-p1k.p1",  0x000000, 0x100000, CRC(f705364b) SHA1(2668e15663a2c7ec7396f40e4f5f454505968ce8) ) /* TC538200 */
	ROM_LOAD16_WORD_SWAP( "095-p2.sp2", 0x100000, 0x200000, CRC(cc15826e) SHA1(44d6ac6c0ca697a6f367dcfd809b1e1771cb0635) ) /* TC5316200 */

	NEO_SFIX_128K( "095-s1.s1", CRC(b6bf5e08) SHA1(b527355c35ea097f3448676f2ffa65b8e56ae30c) ) /* TC531000 */

	NEO_BIOS_AUDIO_128K( "095-m1.m1", CRC(653492a7) SHA1(39e511fb9ed5d2135dc8428a31d0baafb2ab36e0) ) /* TC531001 */

	ROM_REGION( 0xc00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "069-v1.v1", 0x000000, 0x400000, CRC(2bdbd4db) SHA1(5f4fecf69c2329d699cbd45829c19303b1e2a80e) ) /* TC5332204 */
	ROM_LOAD( "069-v2.v2", 0x400000, 0x400000, CRC(a698a487) SHA1(11b8bc53bc26a51f4a408e900e3769958625c4ed) ) /* TC5332204 */
	ROM_LOAD( "095-v3.v3", 0x800000, 0x400000, CRC(189d1c6c) SHA1(f0b8cd1ee40ea3feeb2800f0723b451ec8240203) ) /* TC5332201 */

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "069-c1.c1", 0x0000000, 0x400000, CRC(e302f93c) SHA1(d8610b14900b2b8fe691b67ca9b1abb335dbff74) ) /* Plane 0,1 */ /* TC5332205 */
	ROM_LOAD16_BYTE( "069-c2.c2", 0x0000001, 0x400000, CRC(1053a455) SHA1(69501bfac68739e63d798045b812badd251d57b8) ) /* Plane 2,3 */ /* TC5332205 */
	ROM_LOAD16_BYTE( "069-c3.c3", 0x0800000, 0x400000, CRC(1c0fde2f) SHA1(cf6c2ef56c03a861de3b0b6dc0d7c9204d947f9d) ) /* Plane 0,1 */ /* TC5332205 */
	ROM_LOAD16_BYTE( "069-c4.c4", 0x0800001, 0x400000, CRC(a25fc3d0) SHA1(83cb349e2f1032652060b233e741fb893be5af16) ) /* Plane 2,3 */ /* TC5332205 */
	ROM_LOAD16_BYTE( "095-c5.c5", 0x1000000, 0x400000, CRC(8b9b65df) SHA1(e2a7e20855501f240bcd22f5cc92fcb4a9806abe) ) /* Plane 0,1 */ /* TC5332202 */
	ROM_LOAD16_BYTE( "095-c6.c6", 0x1000001, 0x400000, CRC(3e164718) SHA1(53217f938c8964c1ca68a6fd5249c4169a5ac8e6) ) /* Plane 2,3 */ /* TC5332202 */
	ROM_LOAD16_BYTE( "095-c7.c7", 0x1800000, 0x200000, CRC(ca605e12) SHA1(5150b835247fd705bc1dece97d423d9c20a51416) ) /* Plane 0,1 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "095-c8.c8", 0x1800001, 0x200000, CRC(4e6beb6c) SHA1(c0ac7cfc832ace6ad52c58f5da3a8101baead749) ) /* Plane 2,3 */ /* TC5316200 */
ROM_END

ROM_START( rbff1ka ) /* KOREAN VERSION */
	/* This is a bug fixed revision applied over the original cart. The original P1 and P2 stayed in the cart and this */
	/* 512k ROM was added to replace the first 512k of P1. */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "095-p1k.p1", 0x000000, 0x100000, CRC(f705364b) SHA1(2668e15663a2c7ec7396f40e4f5f454505968ce8) ) /* TC538200 */
	ROM_LOAD16_WORD_SWAP( "095-p2.sp2", 0x100000, 0x200000, CRC(cc15826e) SHA1(44d6ac6c0ca697a6f367dcfd809b1e1771cb0635) ) /* TC5316200 */
	/* the rom below acts as a patch to the program rom in the cart, replacing the first 512kb */
	ROM_LOAD16_WORD_SWAP( "095-eprk.ep1", 0x000000, 0x080000, CRC(422093ed) SHA1(1b4cceec9b622d35f1bfdf01e314771b98483348) ) /* M27C4002 */
	/* no label on eprom, correct chip label unknown */

	NEO_SFIX_128K( "095-s1.s1", CRC(b6bf5e08) SHA1(b527355c35ea097f3448676f2ffa65b8e56ae30c) ) /* TC531000 */

	NEO_BIOS_AUDIO_128K( "095-m1.m1", CRC(653492a7) SHA1(39e511fb9ed5d2135dc8428a31d0baafb2ab36e0) ) /* TC531001 */

	ROM_REGION( 0xc00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "069-v1.v1", 0x000000, 0x400000, CRC(2bdbd4db) SHA1(5f4fecf69c2329d699cbd45829c19303b1e2a80e) ) /* TC5332204 */
	ROM_LOAD( "069-v2.v2", 0x400000, 0x400000, CRC(a698a487) SHA1(11b8bc53bc26a51f4a408e900e3769958625c4ed) ) /* TC5332204 */
	ROM_LOAD( "095-v3.v3", 0x800000, 0x400000, CRC(189d1c6c) SHA1(f0b8cd1ee40ea3feeb2800f0723b451ec8240203) ) /* TC5332201 */

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "069-c1.c1", 0x0000000, 0x400000, CRC(e302f93c) SHA1(d8610b14900b2b8fe691b67ca9b1abb335dbff74) ) /* Plane 0,1 */ /* TC5332205 */
	ROM_LOAD16_BYTE( "069-c2.c2", 0x0000001, 0x400000, CRC(1053a455) SHA1(69501bfac68739e63d798045b812badd251d57b8) ) /* Plane 2,3 */ /* TC5332205 */
	ROM_LOAD16_BYTE( "069-c3.c3", 0x0800000, 0x400000, CRC(1c0fde2f) SHA1(cf6c2ef56c03a861de3b0b6dc0d7c9204d947f9d) ) /* Plane 0,1 */ /* TC5332205 */
	ROM_LOAD16_BYTE( "069-c4.c4", 0x0800001, 0x400000, CRC(a25fc3d0) SHA1(83cb349e2f1032652060b233e741fb893be5af16) ) /* Plane 2,3 */ /* TC5332205 */
	ROM_LOAD16_BYTE( "095-c5.c5", 0x1000000, 0x400000, CRC(8b9b65df) SHA1(e2a7e20855501f240bcd22f5cc92fcb4a9806abe) ) /* Plane 0,1 */ /* TC5332202 */
	ROM_LOAD16_BYTE( "095-c6.c6", 0x1000001, 0x400000, CRC(3e164718) SHA1(53217f938c8964c1ca68a6fd5249c4169a5ac8e6) ) /* Plane 2,3 */ /* TC5332202 */
	ROM_LOAD16_BYTE( "095-c7.c7", 0x1800000, 0x200000, CRC(ca605e12) SHA1(5150b835247fd705bc1dece97d423d9c20a51416) ) /* Plane 0,1 */ /* TC5316200 */
	ROM_LOAD16_BYTE( "095-c8.c8", 0x1800001, 0x200000, CRC(4e6beb6c) SHA1(c0ac7cfc832ace6ad52c58f5da3a8101baead749) ) /* Plane 2,3 */ /* TC5316200 */
ROM_END

ROM_START( roboarma ) /* MVS AND AES VERSION*/
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "032-epr.p1", 0x000000, 0x080000, CRC(27c773cb) SHA1(597ca73f142b1129cc7780540bb9cfacd47bc6ce) ) /* D27C4000 */
	/* Found on legitimate Robo Army MVS and AES Carts. Debug code button which check control a sound test has been patched out because in a multislot situation that code could have been enabled
	that would stop roboarmy from working, sending it into an infinite loop ; correct chip label unknown */

	NEO_SFIX_128K( "032-s1.s1", CRC(ac0daa1b) SHA1(93bae4697dc403fce19422752a514326ccf66a91) ) /* TC531000 */

	NEO_BIOS_AUDIO_128K( "032-m1.m1", CRC(35ec952d) SHA1(8aed30e26d7e2c70dbce5de752df416091066f7b) ) /* TC531001 */

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "032-v1.v1", 0x000000, 0x100000, CRC(63791533) SHA1(4479e9308cdc906b9e03b985303f4ebedd00512f) ) /* TC538200 */
	ROM_LOAD( "032-v2.v2", 0x100000, 0x100000, CRC(eb95de70) SHA1(b34885201116d2b3bbdee15ec7b5961cf5c069e1) ) /* TC538200 */

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "032-c1.c1", 0x000000, 0x100000, CRC(97984c6c) SHA1(deea59c0892f05dc7db98cb57b3eb83688dc57f0) ) /* Plane 0,1 */ /* TC538200 */
	ROM_LOAD16_BYTE( "032-c2.c2", 0x000001, 0x100000, CRC(65773122) SHA1(2c0162a8e971e5e57933e4ae16040bf824ffdefe) ) /* Plane 2,3 */ /* TC538200 */
	ROM_LOAD16_BYTE( "032-c3.c3", 0x200000, 0x080000, CRC(40adfccd) SHA1(b11f866dd70ba0ed9123424508355cb948b19bdc) ) /* Plane 0,1 */ /* TC534200 */
	ROM_LOAD16_BYTE( "032-c4.c4", 0x200001, 0x080000, CRC(462571de) SHA1(5c3d610d492f91564423873b3b434dcda700373f) ) /* Plane 2,3 */ /* TC534200 */
ROM_END

ROM_START( rotdh ) /* Encrypted Set */ /* AES VERSION */
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "264-pk1.p1",  0x000000, 0x100000, CRC(ff2fa719) SHA1(03009e3693648ac0d892390c3bba2ceac6c9564b) )
	ROM_LOAD16_WORD_SWAP( "264-pk2.sp2", 0x100000, 0x200000, CRC(0df2e112) SHA1(c521783483117859a2b250190be77f6d49412ae8) )

	ROM_Y_ZOOM

	ROM_REGION( 0x20000, "fixed", 0 )
	ROM_FILL( 0x000000, 0x20000, 0x000000 )
	ROM_REGION( 0x20000, "fixedbios", 0 )
	ROM_LOAD( "sfix.sfix", 0x000000, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) )

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "264-m1.m1", CRC(4dbd7b43) SHA1(6b63756b0d2d30bbf13fbd219833c81fd060ef96) ) /* mask rom 27c010 */

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "264-v1.v1", 0x000000, 0x800000, CRC(fa005812) SHA1(73723126dab5a640ac11955ed6da1bf7a91394f5) ) /* mask rom TC5364205 */
	ROM_LOAD( "264-v2.v2", 0x800000, 0x800000, CRC(c3dc8bf0) SHA1(a105e37262d9500a30fb8a5dac05aa4fab2562a3) ) /* mask rom TC5364205 */

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "264-c1.c1", 0x0000000, 0x800000, CRC(4f148fee) SHA1(0821463765fad8fbd0dfbbabb7807337d0333719) ) /* Plane 0,1 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "264-c2.c2", 0x0000001, 0x800000, CRC(7cf5ff72) SHA1(ccb2f94bce943576d224cb326806942426d25584) ) /* Plane 2,3 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "264-c3.c3", 0x1000000, 0x800000, CRC(64d84c98) SHA1(8faf153f465ce6fb7770b27a7ce63caf11dd4086) ) /* Plane 0,1 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "264-c4.c4", 0x1000001, 0x800000, CRC(2f394a95) SHA1(82347e8f2b48b0522d7d91fd3f372d5768934ab2) ) /* Plane 2,3 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "264-c5.c5", 0x2000000, 0x800000, CRC(6b99b978) SHA1(8fd0a60029b41668f9e1e3056edd3c90f62efa83) ) /* Plane 0,1 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "264-c6.c6", 0x2000001, 0x800000, CRC(847d5c7d) SHA1(a2ce03f6302edf81f2645de9ec61df1a281ddd78) ) /* Plane 2,3 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "264-c7.c7", 0x3000000, 0x800000, CRC(231d681e) SHA1(87836e64dc816f8bf1c834641535ea96baacc024) ) /* Plane 0,1 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "264-c8.c8", 0x3000001, 0x800000, CRC(c5edb5c4) SHA1(253378c8739daa5da4edb15eff7050820b2b3755) ) /* Plane 2,3 */ /* mask rom TC5364205 */
ROM_END

ROM_START( kof99k ) /* Original Version - Encrypted Code & GFX */ /* KOREAN VERSION */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kb.neo-sma",   0x0c0000, 0x040000, CRC(9fccc688) SHA1(1a24d0fe7cabe7b346f538e099f1357bbf77bc89) ) /* stored in the custom chip */
	ROM_LOAD16_WORD_SWAP( "151-pg1k.p1",  0x100000, 0x400000, CRC(ef259292) SHA1(e02f2d0c71eac74424507e4845991fbc12821045) ) /* mask rom TC5332205 */
	ROM_LOAD16_WORD_SWAP( "151-pg2k.p2",  0x500000, 0x400000, CRC(f3898ec2) SHA1(c7fd230fbb97a9b171aeae8ff1a5cd39ba7fa9eb) ) /* mask rom TC5332205 */

	ROM_Y_ZOOM

	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
	ROM_REGION( 0x20000, "fixed", 0 )
	ROM_FILL( 0x000000, 0x20000, 0x000000 )
	ROM_REGION( 0x20000, "fixedbios", 0 )
	ROM_LOAD( "sfix.sfix", 0x000000, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) )

	NEO_BIOS_AUDIO_128K( "251-m1.m1", CRC(5e74539c) SHA1(6f49a9343cbd026b2c6720ff3fa2e5b1f85e80da) ) /* TC531001 */

	ROM_REGION( 0x0e00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "251-v1.v1", 0x000000, 0x400000, CRC(ef2eecc8) SHA1(8ed13b9db92dba3124bc5ba66e3e275885ece24a) ) /* TC5332204 */
	ROM_LOAD( "251-v2.v2", 0x400000, 0x400000, CRC(73e211ca) SHA1(0e60fa64cab6255d9721e2b4bc22e3de64c874c5) ) /* TC5332204 */
	ROM_LOAD( "251-v3.v3", 0x800000, 0x400000, CRC(821901da) SHA1(c6d4975bfaa19a62ed59126cadf2578c0a5c257f) ) /* TC5332204 */
	ROM_LOAD( "251-v4.v4", 0xc00000, 0x200000, CRC(b49e6178) SHA1(dde6f76e958841e8c99b693e13ced9aa9ef316dc) ) /* TC5316200 */

    ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "251-c1.c1", 0x0000000, 0x800000, CRC(0f9e93fe) SHA1(c7d77f0833c6f526f632e4f2dce59e302f6b9a15) ) /* Plane 0,1 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "251-c2.c2", 0x0000001, 0x800000, CRC(e71e2ea3) SHA1(39c7a326fddbcca3b29c68cdc96aad4d62295c0f) ) /* Plane 2,3 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "251-c3.c3", 0x1000000, 0x800000, CRC(238755d2) SHA1(01125b5c7a28e350f091280b041954fd1ac7c98f) ) /* Plane 0,1 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "251-c4.c4", 0x1000001, 0x800000, CRC(438c8b22) SHA1(ffbc643f5b27dd00f2f95d4ef4c5f29ee814722b) ) /* Plane 2,3 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "251-c5.c5", 0x2000000, 0x800000, CRC(0b0abd0a) SHA1(d5ad324fe523bdc6f09209d236cc4932524a48f1) ) /* Plane 0,1 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "251-c6.c6", 0x2000001, 0x800000, CRC(65bbf281) SHA1(79ae174667a23dabcfe865b6cd6133c86098452e) ) /* Plane 2,3 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "251-c7.c7", 0x3000000, 0x800000, CRC(ff65f62e) SHA1(7cd335fede05b56e15db90ce407c1183a78da4e9) ) /* Plane 0,1 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "251-c8.c8", 0x3000001, 0x800000, CRC(8d921c68) SHA1(42acf1d27d52a8e3b6262eb7df50693c0b135565) ) /* Plane 2,3 */ /* TC5364205 */
ROM_END

ROM_START( kotm2a ) /* MVS VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "039_p1.p1", 0x000000, 0x080000, CRC(8d186638) SHA1(c3874bbb1bfcb220173afb2e0a2123ffaeb7bd2b) ) /* TC534200 */
	ROM_LOAD16_WORD_SWAP( "039-p2.p2", 0x080000, 0x080000, CRC(28661afe) SHA1(6c85ff6ab334b1ca744f726f42dac211537e7315) ) /* TC534200 */

	NEO_SFIX_128K( "039-s1.s1", CRC(63ee053a) SHA1(7d4b92bd022708975b1470e8f24d1f5a712e1b94) ) /* TC531000 */

	NEO_BIOS_AUDIO_128K( "039-m1.m1", CRC(0c5b2ad5) SHA1(15eb5ea10fecdbdbcfd06225ae6d88bb239592e7) ) /* TC531001 */

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "039-v2.v2", 0x000000, 0x200000, CRC(86d34b25) SHA1(89bdb614b0c63d678962da52e2f596750d20828c) ) /* TC5316200 */
	ROM_LOAD( "039-v4.v4", 0x200000, 0x100000, CRC(8fa62a0b) SHA1(58ac2fdd73c542eb8178cfc4adfa0e5940183283) ) /* TC538200 */

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD16_BYTE( "039-c1.c1", 0x000000, 0x100000, CRC(6d1c4aa9) SHA1(4fbc9d7cb37522ec298eefbe38c75a2d050fbb4a) ) /* Plane 0,1 */ /* TC5316200 */
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_LOAD16_BYTE( "039-c2.c2", 0x000001, 0x100000, CRC(f7b75337) SHA1(4d85f85948c3e6ed38b0b0ccda79de3ce026e2d9) ) /* Plane 2,3 */ /* TC5316200 */
	ROM_CONTINUE( 0x400001, 0x100000 )
	ROM_LOAD16_BYTE( "039-c3.c3", 0x200000, 0x080000, CRC(bfc4f0b2) SHA1(f4abe2b52882b966412f3b503b8f2c8f49b57968) ) /* Plane 0,1 */ /* TC534200 */
	ROM_LOAD16_BYTE( "039-c4.c4", 0x200001, 0x080000, CRC(81c9c250) SHA1(e3a34ff69081a8681b5ca895915892dcdccfa7aa) ) /* Plane 2,3 */ /* TC534200 */
ROM_END

ROM_START( bjourneyh ) /* AES VERSION */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "022-hp1.p1", 0x000000, 0x100000, CRC(62cbe7b2) SHA1(f9a8fd98702c623ae793804ba50d09751e3fee4c) ) /* TC538200 */

	NEO_SFIX_128K( "022-s1.s1", CRC(843c3624) SHA1(dbdf86c193b7c1d795f8c21f2c103c1d3e18abbe) ) /* TC531000 */

	NEO_BIOS_AUDIO_128K( "022-m1.m1", CRC(8e1d4ab6) SHA1(deabc11ab81e7e68a3e041c03a127ae28d0d7264) ) /* TC531001 */

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "022-v11.v11", 0x000000, 0x100000, CRC(2cb4ad91) SHA1(169ec7303c4275155a66a88cc08270c24132bb36) ) /* TC538200 */
	ROM_LOAD( "022-v22.v22", 0x100000, 0x100000, CRC(65a54d13) SHA1(a591fbcedca8f679dacbebcd554e3aa3fd163e92) ) /* TC538200 */

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "022-c1.c1", 0x000000, 0x100000, CRC(4d47a48c) SHA1(6e282285be72583d828e7765b1c1695ecdc44777) ) /* Plane 0,1 */ /* TC538200 */
	ROM_LOAD16_BYTE( "022-c2.c2", 0x000001, 0x100000, CRC(e8c1491a) SHA1(c468d2556b3de095aaa05edd1bc16d71303e9478) ) /* Plane 2,3 */ /* TC538200 */
	ROM_LOAD16_BYTE( "022-c3.c3", 0x200000, 0x080000, CRC(66e69753) SHA1(974b823fc62236fbc23e727f25b61a805a707a9e) ) /* Plane 0,1 */ /* TC534200 */
	ROM_LOAD16_BYTE( "022-c4.c4", 0x200001, 0x080000, CRC(71bfd48a) SHA1(47288be69e6992d09ebef108b4de9ffab6293dc8) ) /* Plane 2,3 */ /* TC534200 */
ROM_END

ROM_START( burningfpa ) /* later prototype - Sx, Vx and Cx data all matches final game, but with different rom arranagement, Px & Mx unique */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "018_p1_1f28.podd", 0x000001, 0x080000, CRC(f7d15752) SHA1(334b7e5c8e9099d39424e72db66846d0b9e534de) )
	ROM_LOAD16_BYTE( "018_p2_3217.peven", 0x000000, 0x080000, CRC(ffae22fb) SHA1(82f2f81fe96b3c6953985964e12e93e79410ab9e) )

	NEO_SFIX_128K( "018_s1_4491.s1", CRC(6799ea0d) SHA1(ec75ef9dfdcb0b123574fc6d81ebaaadfba32fb5) )

	NEO_BIOS_AUDIO_128K( "018_m1_d13e.m1", CRC(2b0c0415) SHA1(a5a0d5e3ea2ef77b6f5cd14f2907ab2f1aed76b7) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "018_v11_6c00.v11", 0x000000, 0x080000, CRC(b55b9670) SHA1(b0ff38b2dca1361ad155e90be3674dbea1c0a53c) )
	ROM_LOAD( "018_v12_8146.v12", 0x080000, 0x080000, CRC(a0bcf260) SHA1(5d1f2613cf4a292557f37e6f44a90b20d11ed8cd) )
	ROM_LOAD( "018_v13_b813.v13", 0x100000, 0x080000, CRC(270f4707) SHA1(29e763acc9fd4b94d8b5d0ad917e20d8a66bbe49) )
	ROM_LOAD( "018_v24_22ee.v24", 0x180000, 0x080000, CRC(924e3d69) SHA1(927091f9a098f00eb303f5567f4ee926bcb170e3) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "018_c1_2505.c1", 0x000000, 0x80000, CRC(3a441c6a) SHA1(0347d47a689af67426be42b4c99da101ee01ce11) ) /* Plane 0 */
	ROM_LOAD32_BYTE( "018_c2_3f55.c2", 0x000002, 0x80000, CRC(bb72404b) SHA1(7620fccc50ecacf732bb1382abef42212d369f8c) ) /* Plane 2 */
	ROM_LOAD32_BYTE( "018_c3_a20d.c3", 0x000001, 0x80000, CRC(87bffd2f) SHA1(0f7c835029a3f561861a1a07987dad23a32a899c) ) /* Plane 1 */
	ROM_LOAD32_BYTE( "018_c4_c6e1.c4", 0x000003, 0x80000, CRC(33803163) SHA1(888ba63618a2ca541883a612f0c75ffa96f1c528) ) /* Plane 3 */
	ROM_LOAD32_BYTE( "018_c5_2cd1.c5", 0x200000, 0x80000, CRC(74391952) SHA1(0f7451ff74901e7250214a7604a37add56ad7e1f) ) /* Plane 0 */
	ROM_LOAD32_BYTE( "018_c6_8135.c6", 0x200002, 0x80000, CRC(95e220e6) SHA1(cef4f7c697ab6d20e1b5c85df773d0f1a79e3008) ) /* Plane 2 */
	ROM_LOAD32_BYTE( "018_c7_d009.c7", 0x200001, 0x80000, CRC(41326c0d) SHA1(64bbecb560d2795ae5292776604ea318a9ae53a6) ) /* Plane 1 */
	ROM_LOAD32_BYTE( "018_c8_dc63.c8", 0x200003, 0x80000, CRC(ed3b1f04) SHA1(0cb0d30e294e7ff398d553d0f08befb53ac65269) ) /* Plane 3 */
ROM_END

ROM_START( burningfpb ) /* later prototype, but Sx, Cx, Vx etc. not yet final, Eproms are labeled Ver07 from Feb 1991 */
	ROM_REGION( 0x100000, "maincpu", ROMREGION_BE|ROMREGION_16BIT )
	ROM_LOAD16_BYTE( "p1.bin", 0x000001, 0x080000, CRC(f05ce157) SHA1(87c515ba009ef952942434f48d9a3849d354b6e3) )
	ROM_LOAD16_BYTE( "p2.bin", 0x000000, 0x080000, CRC(768ddc90) SHA1(a125f7bcadf4d8630ae3d08911fe061d15252c76) )

	NEO_SFIX_128K( "s1.bin", CRC(3effc183) SHA1(706bf3649bd08798be031263b9edadb7ecfa122a) )

	NEO_BIOS_AUDIO_128K( "m1.bin", CRC(3031af09) SHA1(72d3776f8c818f5db984e7a1b2fa7cb4a9c8d1ee) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "v11.bin", 0x000000, 0x080000, CRC(20b40b70) SHA1(21e0e069650ad4a90567509f2932bb74f3f4205a) )
	ROM_LOAD( "v12.bin", 0x080000, 0x080000, CRC(a0bcf260) SHA1(5d1f2613cf4a292557f37e6f44a90b20d11ed8cd) ) // matches final
	ROM_LOAD( "v13.bin", 0x100000, 0x080000, CRC(a4e0e58a) SHA1(33e9b60e3aaca8e3f625a4238ec768ea04cd58d0) )
	ROM_LOAD( "v24-bad.bin", 0x180000, 0x080000, BAD_DUMP CRC(4389e65a) SHA1(2f18ac9ba390bb09abacefc9ccfa3bd6a45d515b) ) // chip was physically damaged
	ROM_LOAD( "018_v24_22ee.v24", 0x180000, 0x080000, CRC(924e3d69) SHA1(927091f9a098f00eb303f5567f4ee926bcb170e3) ) // load over it with the final data, could be different however

	ROM_REGION( 0x400000, "sprites", 0 ) // note, ROM_LOAD32_BYTE
	ROM_LOAD32_BYTE( "c1.bin", 0x000000, 0x80000, CRC(8fd6a9bb) SHA1(8f840385ba8e8a7f3d6260f48f1ecb27ccf05c5c) ) /* Plane 0 */
	ROM_LOAD32_BYTE( "c2.bin", 0x000002, 0x80000, CRC(7c3464b8) SHA1(3f3544a7a70827b81ce6978627b7f21edf0072c7) ) /* Plane 2 */
	ROM_LOAD32_BYTE( "c3.bin", 0x000001, 0x80000, CRC(0ac8f1be) SHA1(66d22a7a58fe86ed747bb27e480254826e1d921b) ) /* Plane 1 */
	ROM_LOAD32_BYTE( "c4.bin", 0x000003, 0x80000, CRC(3af6b235) SHA1(e8903a8ab92e6df29f80b9fe6c5926038e2b2896) ) /* Plane 3 */
	ROM_LOAD32_BYTE( "c5.bin", 0x200000, 0x80000, CRC(707205ab) SHA1(fe6a1122958084a04ffa9892004d3f3513f43fa2) ) /* Plane 0 */
	ROM_LOAD32_BYTE( "c6.bin", 0x200002, 0x80000, CRC(10d0d2cf) SHA1(f1df3b327ab9af71ed6d03a3b788334928c4dbae) ) /* Plane 2 */
	ROM_LOAD32_BYTE( "c7.bin", 0x200001, 0x80000, CRC(def06900) SHA1(4106203f0a14e6c723cacf77ba75ce3aea563a34) ) /* Plane 1 */
	ROM_LOAD32_BYTE( "c8.bin", 0x200003, 0x80000, CRC(6fdc1691) SHA1(3842735456550734b703a0243c38dd83d4722b0c) ) /* Plane 3 */
ROM_END

ROM_START( garouha ) /* Original Version - Encrypted GFX */ /* AES VERSION */
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "neo-sma", 0x0c0000, 0x040000, CRC(9aa450e6) SHA1(ba9c6fe10ef97255b004fcbf05065826d219a968) )  /* stored in the custom chip */
	/* standard program roms are identical to 'garou' set, only content of custom chip above differs */
	ROM_LOAD16_WORD_SWAP( "253-ep1.p1", 0x100000, 0x200000, CRC(ea3171a4) SHA1(bbda40f652baa0dc5fc6a006c001a1bdb0df43f6) ) /* M27C160 */
	ROM_LOAD16_WORD_SWAP( "253-ep2.p2", 0x300000, 0x200000, CRC(382f704b) SHA1(0ace9c84a8b8a0524fd9a503e7d872de1bf1bd52) ) /* M27C160 */
	ROM_LOAD16_WORD_SWAP( "253-ep3.p3", 0x500000, 0x200000, CRC(e395bfdd) SHA1(6b50f5ac15bf66b7e4e9bff57594fd3d7530c831) ) /* M27C160 */
	ROM_LOAD16_WORD_SWAP( "253-ep4.p4", 0x700000, 0x200000, CRC(da92c08e) SHA1(5556f983ebcebc33160e90a6a6cf589d54c8cedc) ) /* M27C160 */

	ROM_Y_ZOOM

	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
	ROM_REGION( 0x80000, "fixed", 0 )   /* larger char set */
	ROM_FILL( 0x000000, 0x20000, 0x000000 )
	ROM_REGION( 0x20000, "fixedbios", 0 )
	ROM_LOAD( "sfix.sfix", 0x000000, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) )

	NEO_BIOS_AUDIO_256K( "253-m1.m1", CRC(36a806be) SHA1(90fb44dc0c3fb57946a0f35716056abb84a0f191) ) /* TC532000 */

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "253-v1.v1", 0x000000, 0x400000, CRC(263e388c) SHA1(11f05feee170370c4bfc5053af79246a6e3de5dc) ) /* TC5332204 */
	ROM_LOAD( "253-v2.v2", 0x400000, 0x400000, CRC(2c6bc7be) SHA1(c9c61054ce1a47bf1bf77a31117726b499df24a4) ) /* TC5332204 */
	ROM_LOAD( "253-v3.v3", 0x800000, 0x400000, CRC(0425b27d) SHA1(986863c98fc3445487242dcf2ea75b075e7f33ee) ) /* TC5332204 */
	ROM_LOAD( "253-v4.v4", 0xc00000, 0x400000, CRC(a54be8a9) SHA1(d7123e79b43e8adfaa5ecadbfcbeb6be890ec311) ) /* TC5332204 */

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "253-c1.c1", 0x0000000, 0x800000, CRC(0603e046) SHA1(5ef4557ce90ba65d36129de97be1fdc049c4a3d0) ) /* Plane 0,1 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "253-c2.c2", 0x0000001, 0x800000, CRC(0917d2a4) SHA1(d4ed3a13ae22f880fb399671c1752f1a0283f316) ) /* Plane 2,3 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "253-c3.c3", 0x1000000, 0x800000, CRC(6737c92d) SHA1(678f0c9cc1267bd131546981b9989bfb7289d8ba) ) /* Plane 0,1 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "253-c4.c4", 0x1000001, 0x800000, CRC(5ba92ec6) SHA1(aae36b050a3a0321026a96eba06dd184c0e2acca) ) /* Plane 2,3 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "253-c5.c5", 0x2000000, 0x800000, CRC(3eab5557) SHA1(47c433015aa81a0b0a1d3ee51382c4948b80c023) ) /* Plane 0,1 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "253-c6.c6", 0x2000001, 0x800000, CRC(308d098b) SHA1(b052f1fa9fbc69606004c250e2505360eaa24949) ) /* Plane 2,3 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "253-c7.c7", 0x3000000, 0x800000, CRC(c0e995ae) SHA1(8675ca787d28246174c313167f82557f021366fc) ) /* Plane 0,1 */ /* TC5364205 */
	ROM_LOAD16_BYTE( "253-c8.c8", 0x3000001, 0x800000, CRC(21a11303) SHA1(fd61221ad257c185ef5c1f9694bd6b840b591af3) ) /* Plane 2,3 */ /* TC5364205 */
ROM_END

ROM_START( gpilotsp ) /* prototype - different revisions of the 68k and z80 programs, gfx + samples different ROM arrangement but same data, rest identical */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "p1", 0x000001, 0x080000, CRC(c42125b4) SHA1(b5879d06152bba0c0211c44fff4837b54405e7ee) )
	ROM_LOAD16_BYTE( "p2", 0x000000, 0x080000, CRC(5a4db1f3) SHA1(535b6abd266bba174d20bfff17b2668c6a36d1e6) )

	NEO_SFIX_128K( "s1", CRC(a6d83d53) SHA1(9a8c092f89521cc0b27a385aa72e29cbaca926c5) )

	NEO_BIOS_AUDIO_128K( "m1", CRC(32a108cf) SHA1(4d38a283376725e1c1aca0d5aeedd4862146ba1f) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "v11", 0x000000, 0x080000, CRC(8cc44140) SHA1(0a88d8962e057bf0cabd4819d4ba67e093c49b82) )
	ROM_LOAD( "v12", 0x080000, 0x080000, CRC(415c61cd) SHA1(638e5fd9b02b4553df42f00188a7ac52a5a7bf84) )
	ROM_LOAD( "v13", 0x100000, 0x080000, CRC(4a9e6f03) SHA1(d3ac11f333b03d8a318921bdaefb14598e289a14) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "v21", 0x000000, 0x080000, CRC(7abf113d) SHA1(5b2a0e70f2eaf4638b44702dacd4cb17838fb1d5) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "c11", 0x000000, 0x80000, CRC(7a5158b3) SHA1(01dd241534c16e81ce1113a53495606d8f907e1e) ) /* Plane 0 */
	ROM_LOAD32_BYTE( "c12", 0x000002, 0x80000, CRC(41e67a5a) SHA1(21df717cea93c0c4c5773e98ffefcdc2a06b83c4) ) /* Plane 2 */
	ROM_LOAD32_BYTE( "c13", 0x000001, 0x80000, CRC(5f80c0d0) SHA1(48a5c081de88811b170da794634f1a82e42bd472) ) /* Plane 1 */
	ROM_LOAD32_BYTE( "c14", 0x000003, 0x80000, CRC(61227b93) SHA1(563283401cf648edd7cc881969a1107d78f31b75) ) /* Plane 3 */
	ROM_LOAD32_BYTE( "c15", 0x200000, 0x80000, CRC(96de9bb5) SHA1(c3d42b1dd27cc153310a6fc14a02380b6b673574) ) /* Plane 0 */
	ROM_LOAD32_BYTE( "c16", 0x200002, 0x80000, CRC(2b904c85) SHA1(9e162449af1f37cc22900df09e37226e74d62d35) ) /* Plane 2 */
	ROM_LOAD32_BYTE( "c17", 0x200001, 0x80000, CRC(c0d7517d) SHA1(db60e23d1b3323ad757c1fda009f2c08abd5630b) ) /* Plane 1 */
	ROM_LOAD32_BYTE( "c18", 0x200003, 0x80000, CRC(75569e35) SHA1(fac74ec97c6612bffdfd1239c115d6247eb7fabc) ) /* Plane 3 */
ROM_END

ROM_START( pnyaanv ) /* Encrypted Set */ /* MVS ONLY RELEASE */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pn202.p1", 0x000000, 0x100000, CRC(bf34e71c) SHA1(cfa7a2c7c41601a758414faf34e59583d7537363) )

	ROM_Y_ZOOM

	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
	ROM_REGION( 0x20000, "fixed", 0 )
	ROM_FILL( 0x000000, 0x20000, 0x000000 )
	ROM_REGION( 0x20000, "fixedbios", 0 )
	ROM_LOAD( "sfix.sfix", 0x000000, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) )

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "267-m1.m1", CRC(c7853ccd) SHA1(1b7a4c5093cf0fe3861ce44fd1d3b30c71ad0abe) ) /* mask rom TC534000 */

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "267-v1.v1", 0x000000, 0x400000, CRC(e2e8e917) SHA1(7f412d55aebff3d38a225a88c632916295ab0584) ) /* mask rom TC5332204 */

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "267-c1.c1", 0x0000000, 0x800000, CRC(5eebee65) SHA1(7eb3eefdeb24e19831d0f51d4ea07a0292c25ab6) ) /* Plane 0,1 */ /* mask rom TC5364205 */
	ROM_LOAD16_BYTE( "267-c2.c2", 0x0000001, 0x800000, CRC(2b67187b) SHA1(149c3efd3c444fd0d35a97fa2268102bf76be3ed) ) /* Plane 2,3 */ /* mask rom TC5364205 */
ROM_END

ROM_START( viewpoinp ) // crashes during stage 4 on real hardware (but stage 5 can be loaded with memcard)
	ROM_REGION( 0x100000, "maincpu", ROMREGION_BE|ROMREGION_16BIT )
	ROM_LOAD16_BYTE( "p1", 0x000001, 0x080000, CRC(0adb5eee) SHA1(1766652601cfb69b227aa0a9cecb7039b45c19b5) )
	ROM_LOAD16_BYTE( "p2", 0x000000, 0x080000, CRC(31129194) SHA1(b088a0d400808a75a95895083845defdc01ed531) )

	NEO_SFIX_128K( "s1", CRC(9fea5758) SHA1(5c6f01da89f2639cf741ee7c39e27023b8083052) )

	NEO_BIOS_AUDIO_128K( "m1", CRC(8e69f29a) SHA1(7a25f4997996434ea1b7d0d1ca9e7aaf966cbd03) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "v1", 0x000000, 0x100000, CRC(7e9af736) SHA1(0a47080d48bf220f7388fa1338924b6b94149c33) )
	ROM_LOAD( "v2", 0x100000, 0x100000, CRC(503a9c51) SHA1(2ecfe6c0cf348a01121399176bb84bf6a6ff2a45) )
	ROM_LOAD( "v3", 0x200000, 0x100000, CRC(dfa8d079) SHA1(d33f94bd132aa7d5b953cc1be8c2bb22f63bd13c) )
	ROM_LOAD( "v4", 0x300000, 0x100000, CRC(612b9292) SHA1(edf407150997a83c2d003be972e1f9dc781b07d1) )

	ROM_REGION( 0x400000, "sprites", 0 ) // the actual GFX are the same, but there's no gap between 0x200000-0x3fffff on the prototype, and the data pointers in the program ROM differ because of this
	ROM_LOAD32_BYTE( "c1", 0x000000, 0x080000, CRC(97a3183b) SHA1(2531681c28f39adc9de2dc360970c38b71fcf0d7) )
	ROM_LOAD32_BYTE( "c2", 0x000002, 0x080000, CRC(f637667a) SHA1(477d44f7d8505eecf97010343fd186681bbe3318) )
	ROM_LOAD32_BYTE( "c3", 0x000001, 0x080000, CRC(b017d2d1) SHA1(160bd4f3f4c09a244a9cfdd076f37299ec0ae4d5) )
	ROM_LOAD32_BYTE( "c4", 0x000003, 0x080000, CRC(10f1624a) SHA1(762fd106886c7f13cb29c97c3a3af9fbd6b30405) )
	ROM_LOAD32_BYTE( "c5", 0x200000, 0x080000, CRC(714a8bc4) SHA1(5f69a7e6acaf6916d76f3de6465a5b548d90af68) )
	ROM_LOAD32_BYTE( "c6", 0x200002, 0x080000, CRC(5bc32495) SHA1(d9e2635de3fe60d4adcc11d4acde2d613808c0b8) )
	ROM_LOAD32_BYTE( "c7", 0x200001, 0x080000, CRC(28a0a127) SHA1(488fa8acd474cd357e3d18043341bc7b5a1a654e) )
	ROM_LOAD32_BYTE( "c8", 0x200003, 0x080000, CRC(439c9036) SHA1(7a5b965ceab9343ece3b6d02cc6dbfc83ec67f04) )
ROM_END

ROM_START( stakwindev )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "088d.p1", 0x000001, 0x080000, CRC(96b58fa4) SHA1(23c8c2a4d7a16838fb54306fb193b355edc75060) )
	ROM_LOAD16_BYTE( "088d.p2", 0x000000, 0x080000, CRC(4e7202ee) SHA1(ab10dda5594ad8a21af219c6907a9841de7384c3) )

	NEO_SFIX_128K( "088d.s1", CRC(2193d089) SHA1(1b6f57d2f4265f210194488356fc3653dfa35932) )

	NEO_BIOS_AUDIO_512K( "088d.m1", CRC(daedbcd7) SHA1(d6d0e67ff7865ff5a0262aba381468e198d50536) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "088d.v1", 0x000000, 0x80000, CRC(ac590b85) SHA1(47ff2ba9648b7145c29b534cd1f6839abb43bee2) )
	ROM_LOAD( "088d.v2", 0x080000, 0x80000, CRC(23ad8a91) SHA1(da620c182fe9fc36421da73f2937e627d9a641bf) )
	ROM_LOAD( "088d.v3", 0x100000, 0x80000, CRC(e2d216b6) SHA1(28b70e57a352ef6a08a5564f7756113a66e7dbb7) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD32_BYTE( "088d.c1",   0x000000, 0x80000, CRC(fb2f29d3) SHA1(1f4cf27d7da1262bae28a8dd88c56d8a9324e982) )
	ROM_LOAD32_BYTE( "088d.c2",   0x000002, 0x80000, CRC(6108e6db) SHA1(f4cdb5df29698f1ba362a227b82d43c3baaa8948) )
	ROM_LOAD32_BYTE( "088d.c3",   0x000001, 0x80000, CRC(702a21b1) SHA1(79006062b516bda35bb77c864ba9ea26135ee8ed) )
	ROM_LOAD32_BYTE( "088d.c4",   0x000003, 0x80000, CRC(3223b05f) SHA1(1595f8029f71c3acd949ddd5539d62424c0b697e) )
	ROM_LOAD32_BYTE( "088d.c5",   0x200000, 0x80000, CRC(36b93e77) SHA1(19431b1ad44b9418f26b94c15572d11caec0994e) )
	ROM_LOAD32_BYTE( "088d.c6",   0x200002, 0x80000, CRC(a7a104c8) SHA1(421a8ef11e299b7379a8198c871c8f11ad97deb0) )
	ROM_LOAD32_BYTE( "088d.c7",   0x200001, 0x80000, CRC(f0d8b2ca) SHA1(2565a44d3ee9375af595d84638c7a76f631f8f9b) )
	ROM_LOAD32_BYTE( "088d.c8",   0x200003, 0x80000, CRC(3bdd06eb) SHA1(dce84eb477229dfa8233cde8b946b64db1efae1d) )
	ROM_LOAD32_BYTE( "088d.c9",   0x400000, 0x80000, CRC(25621e44) SHA1(3e380c1f52233dd1346c0363d920d1f96491cc45) )
	ROM_LOAD32_BYTE( "088d.c10",  0x400002, 0x80000, CRC(17b2115e) SHA1(8c5d1b12ac7e739a7ac1f2189a2f3ca959d06377) )
	ROM_LOAD32_BYTE( "088d.c11",  0x400001, 0x80000, CRC(7d3cd161) SHA1(5ac30c35e815dd2b0235394c1768e419395a1b5a) )
	ROM_LOAD32_BYTE( "088d.c12",  0x400003, 0x80000, CRC(c6970ed6) SHA1(e963d0a5fb718e0eec2115d63ab34a0de0523792) )
ROM_END

ROM_START( froman2b )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "098.p1", 0x000000, 0x80000, CRC(09675541) SHA1(6afb89d43e67f93e40f3877cbedfec9566e3ff0f))

	NEO_SFIX_128K( "098.s1", CRC(0e6a7c73) SHA1(31b1194524dcc80ec4d63bac088b6fb4909f496c) )

	NEO_BIOS_AUDIO_128K( "098.m1", CRC(da4878cf) SHA1(ce13d18a4c5d01974df8542c67c4df00dbc6e7c1) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "098.v1", 0x000000, 0x100000, CRC(6f8ccddc) SHA1(696df2d0f416c2374b0eb7c858486054688c5bca) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "098.c1", 0x0000000, 0x400000, CRC(29148bf7) SHA1(75097fbe8877720afbcbe4dbe30bc600466d759f) )
	ROM_LOAD16_BYTE( "098.c2", 0x0000001, 0x400000, CRC(226b1263) SHA1(dee6a4a0a727c1d8a6d298cb38ed1b9901992d5b) )
ROM_END

 /********
  Earlier 
***********/

ROM_START( 2020bbe )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "030.p1", 0x000000, 0x080000, CRC(d396c9cb) SHA1(47ba421d14d05b965a8d44e7475b227a208e5a07) )

	NEO_SFIX_128K( "030.s1", CRC(7015b8fc) SHA1(8c09bc3e6c62e0f7c9557c1e10c901be325bae7f) )

	NEO_BIOS_AUDIO_128K( "030.m1", CRC(4cf466ec) SHA1(6a003b53c7a4af9d7529e2c10f27ffc4e58dcda5) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "030.v1", 0x000000, 0x100000, CRC(d4ca364e) SHA1(b0573744b0ea2ef1e2167a225f0d254883f5af04) )
	ROM_LOAD( "030.v2", 0x100000, 0x100000, CRC(54994455) SHA1(76eb62b86e8ed51a77f44313d5cc8091b3f58d57) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "030.c1", 0x000000, 0x100000, CRC(4f5e19bd) SHA1(ef7975c4b33a7aea4a25a385f604799f054d3200) )
	ROM_LOAD16_BYTE( "030.c2", 0x000001, 0x100000, CRC(d6314bf0) SHA1(0920cc580d7997fcb0170dd619af2f305d635577) )
	ROM_LOAD16_BYTE( "030e.c3", 0x200000, 0x80000, CRC(6a87ae30) SHA1(b2ca080d8233f43cfb2e60d894af65c7b3f8b809) )
	ROM_LOAD16_BYTE( "030e.c4", 0x200001, 0x80000, CRC(bef75dd0) SHA1(8df572804d36d6b25d94b64e8be17a42babbbe95) )
ROM_END

ROM_START( 3countbe )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "043e.p1", 0x000000, 0x80000, CRC(eb2714c4) SHA1(ba5dbfee4160f27ff36060b777d64b93dc2e929c) )
	ROM_LOAD16_WORD_SWAP( "043e.p2", 0x080000, 0x80000, CRC(5e764567) SHA1(3e34d051e8e1483073e4fcce0b688e50a1e713ce) )

	NEO_SFIX_128K( "043.s1", CRC(c362d484) SHA1(a3c029292572842feabe9aa8c3372628fb63978d) )

	NEO_BIOS_AUDIO_128K( "043.m1", CRC(7eab59cb) SHA1(5ae4107457e091f73960bfba39b589ae36d51ca3) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "043.v1", 0x000000, 0x200000, CRC(63688ce8) SHA1(5c6ac29a0cc0655a87cfe3ada8706838b86b86e4) )
	ROM_LOAD( "043.v2", 0x200000, 0x200000, CRC(c69a827b) SHA1(f5197ea87bb6573fa6aef3a1713c3679c58c1e74) )

	ROM_REGION( 0x0800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "043e.c1", 0x0000000, 0x200000, CRC(d290cc33) SHA1(f794e86da80930b273a134b82d39c6a8887f5228) )
	ROM_LOAD16_BYTE( "043e.c2", 0x0000001, 0x200000, CRC(0b28095d) SHA1(9f8184bab13939d2ef80e007462ed083c6cdd46f) )
	ROM_LOAD16_BYTE( "043e.c3", 0x0400000, 0x200000, CRC(bcc0cb35) SHA1(8bbee3201212be19ab53598c8663205cf27b6b4e) )
	ROM_LOAD16_BYTE( "043e.c4", 0x0400001, 0x200000, CRC(4d1ff7b9) SHA1(469fda8aaca673cb25b6b3c5534d78a990140d38) )
ROM_END

ROM_START( aof3e )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "096.p1",  0x000000, 0x100000, CRC(9edb420d) SHA1(150d80707325ece351c72c21c6186cfb5996adba) )
	ROM_LOAD16_WORD_SWAP( "096.p2", 0x100000, 0x200000, CRC(4d5a2602) SHA1(4c26d6135d2877d9c38169662033e9d0cc24d943) )

	NEO_SFIX_128K( "096.s1", CRC(cc7fd344) SHA1(2c6846cf8ea61fb192ba181dbccb63594d572c0e) )

	NEO_BIOS_AUDIO_128K( "096.m1", CRC(cb07b659) SHA1(940b379957c2987d7ab0443cb80c3ff58f6ba559) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "096.v1", 0x000000, 0x200000, CRC(e2c32074) SHA1(69426e7e63fc31a73d1cd056cc9ae6a2c4499407) )
	ROM_LOAD( "096.v2", 0x200000, 0x200000, CRC(a290eee7) SHA1(e66a98cd9740188bf999992b417f8feef941cede) )
	ROM_LOAD( "096.v3", 0x400000, 0x200000, CRC(199d12ea) SHA1(a883bf34e685487705a8dafdd0b8db15eb360e80) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "096e.c1", 0x0400000, 0x200000, CRC(f6c74731) SHA1(7cd585d40b0993e361a24f917aa220504f12c543) )
	ROM_CONTINUE(               0x0000000, 0x200000 )
	ROM_LOAD16_BYTE( "096e.c2", 0x0400001, 0x200000, CRC(f587f149) SHA1(496446ecc7b39a034b4e28218afb147577a04ab5) )
	ROM_CONTINUE(               0x0000001, 0x200000 )
	ROM_LOAD16_BYTE( "096e.c3", 0x0c00000, 0x200000, CRC(7749f5e6) SHA1(f777d55d10684e78b05c1301529b67ed6b6b4445) )
	ROM_CONTINUE(               0x0800000, 0x200000 )
	ROM_LOAD16_BYTE( "096e.c4", 0x0c00001, 0x200000, CRC(cbd58369) SHA1(ff457eecbeef245db4e67ce4e8eddaf368bba93d) )
	ROM_CONTINUE(               0x0800001, 0x200000 )
	ROM_LOAD16_BYTE( "096e.c5", 0x1400000, 0x200000, CRC(1718bdcd) SHA1(a34e4b3aa41cc39415db7dacabe99ca6f8893545) )
	ROM_CONTINUE(               0x1000000, 0x200000 )
	ROM_LOAD16_BYTE( "096e.c6", 0x1400001, 0x200000, CRC(4fca967f) SHA1(83eea4b7d166feb4274bd2d658f4fdcb20629a40) )
	ROM_CONTINUE(               0x1000001, 0x200000 )
	ROM_LOAD16_BYTE( "096.c7",  0x1800000, 0x200000, CRC(51bd8ab2) SHA1(c8def9c64de64571492b5b7e14b794e3c18f1393) )
	ROM_LOAD16_BYTE( "096.c8",  0x1800001, 0x200000, CRC(9a34f99c) SHA1(fca72d95ec42790a7f1e771a1e25dbc5bec5fc19) )
ROM_END

ROM_START( blazstre )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "239.p1",  0x000000, 0x100000, CRC(183682f8) SHA1(dcee1c2cf4a991ca1f9f2b40c4a738f21682807b) )
	ROM_LOAD16_WORD_SWAP( "239.p2", 0x100000, 0x200000, CRC(9a9f4154) SHA1(f8805453d0995c8fa16cd9accfb7a990071ca630) )

	NEO_SFIX_128K( "239.s1", CRC(d56cb498) SHA1(420ce56431dc7f3f7de84fcbc8c0a17b5eab205e) )

	NEO_BIOS_AUDIO_128K( "239.m1", CRC(d31a3aea) SHA1(e23abfeb23052f0358edcf2c83401025fe632511) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "239.v1", 0x000000, 0x400000, CRC(1b8d5bf7) SHA1(67fc1f7e36e92a89cd1d415eb31a2892f57b0d04) )
	ROM_LOAD( "239.v2", 0x400000, 0x400000, CRC(74cf0a70) SHA1(b00451a2a30de2517ae3eca35eb1fe985b950eb8) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "239e.c1", 0x0400000, 0x200000, CRC(754744e0) SHA1(8f498bc1722189c037568d0fe72d2012e87a4c85) )
	ROM_CONTINUE(               0x0000000, 0x200000 )
	ROM_LOAD16_BYTE( "239e.c2", 0x0400001, 0x200000, CRC(af98c037) SHA1(954a860c79544310685ee22b29fd2153bee8acce) )
	ROM_CONTINUE(               0x0000001, 0x200000 )
	ROM_LOAD16_BYTE( "239e.c3", 0x0c00000, 0x200000, CRC(7b39b590) SHA1(27c606539f626df039ba7376dc1feeee8dc82911) )
	ROM_CONTINUE(               0x0800000, 0x200000 )
	ROM_LOAD16_BYTE( "239e.c4", 0x0c00001, 0x200000, CRC(6e731b30) SHA1(3499b8d9fbb881cdaf5d3022533ae1fd45a125e9) )
	ROM_CONTINUE(               0x0800001, 0x200000 )
	ROM_LOAD16_BYTE( "239e.c5", 0x1400000, 0x200000, CRC(9ceb113b) SHA1(cb1318ff1e814fc797ba17f9fc0764d944eedf86) )
	ROM_CONTINUE(               0x1000000, 0x200000 )
	ROM_LOAD16_BYTE( "239e.c6", 0x1400001, 0x200000, CRC(6a78e810) SHA1(f55e95d467851d790b10612ebc2e0dee352f49b9) )
	ROM_CONTINUE(               0x1000001, 0x200000 )
	ROM_LOAD16_BYTE( "239e.c7", 0x1c00000, 0x200000, CRC(50d28eca) SHA1(3e0f513fe07d16484a8c3896c8cb1b14c7e1a7bb) )
	ROM_CONTINUE(               0x1800000, 0x200000 )
	ROM_LOAD16_BYTE( "239e.c8", 0x1c00001, 0x200000, CRC(cdbbb7d7) SHA1(eadd2711bcb54e1ea6c449b459843ac3c0ac8415) )
	ROM_CONTINUE(               0x1800001, 0x200000 )
ROM_END

ROM_START( goalx3e )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "209.p1", 0x100000, 0x100000, CRC(2a019a79) SHA1(422a639e74284fef2e53e1b49cf8803b0a7e80c6) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "209.s1", CRC(c0eaad86) SHA1(99412093c9707d51817893971e73fb8469cdc9d0) )

	NEO_BIOS_AUDIO_64K( "263e.m1", CRC(dd945773) SHA1(2304d070864da79dceb29c64e8d71b7db0992d1e) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "209.v1", 0x000000, 0x200000, CRC(ef214212) SHA1(3e05ccaa2d06decb18b379b96f900c0e6b39ce70) )

	ROM_REGION( 0xa00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "209e.c1", 0x400000, 0x200000, CRC(d061f1f5) SHA1(7cde2f4c6cc54fb0ffbe1d407831d652610a3aaf) )
	ROM_CONTINUE(               0x000000, 0x200000 )
	ROM_LOAD16_BYTE( "209e.c2", 0x400001, 0x200000, CRC(3f63c1a2) SHA1(3ce2c66fb2bee3face976e9f8973ccc483101ae5) )
	ROM_CONTINUE(               0x000001, 0x200000 )
	ROM_LOAD16_BYTE( "209.c3",  0x800000, 0x100000, CRC(5f91bace) SHA1(3864be27dce6d8f8828d3bf09bfc8116116a2b56) )
	ROM_LOAD16_BYTE( "209.c4",  0x800001, 0x100000, CRC(1e9f76f2) SHA1(b57fdc226bfe328b8848127fb4292295f1287bf6) )
ROM_END

ROM_START( kabukikle )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "092.p1", 0x100000, 0x100000, CRC(28ec9b77) SHA1(7cdc789a99f8127f437d68cbc41278c926be9efd) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "092.s1", CRC(a3d68ee2) SHA1(386f6110a16967a72fbf788f9d968fddcdcd2889) )

	NEO_BIOS_AUDIO_128K( "092.m1", CRC(91957ef6) SHA1(7b6907532a0e02ceb643623cbd689cf228776ed1) )

	ROM_REGION( 0x700000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "092.v1", 0x000000, 0x200000, CRC(69e90596) SHA1(1a2007d7784b3ce90d115980c3353862f1664d45) )
	ROM_LOAD( "092.v2", 0x200000, 0x200000, CRC(7abdb75d) SHA1(0bff764889fe02f37877514c7fc450250839f632) )
	ROM_LOAD( "092.v3", 0x400000, 0x200000, CRC(eccc98d3) SHA1(b0dfbdb1ea045cb961323ac6906ab342256c3dc7) )
	ROM_LOAD( "092.v4", 0x600000, 0x100000, CRC(a7c9c949) SHA1(574bc55b45e81ce357b14f5992426115de25cd35) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "092e.c1", 0x400000, 0x200000, CRC(4d896a58) SHA1(03567f31de0fa947264f49817370345e7023c2c4) )
	ROM_CONTINUE(         0x000000, 0x200000 )
	ROM_LOAD16_BYTE( "092e.c2", 0x400001, 0x200000, CRC(3cf78a18) SHA1(82ab69d0899ed2d79e2097f842883dbd542c6f59) )
	ROM_CONTINUE(         0x000001, 0x200000 )
	ROM_LOAD16_BYTE( "092e.c3", 0xc00000, 0x200000, CRC(58c454e7) SHA1(64dca760e473fabada869037d6c24cbc58663911) )
	ROM_CONTINUE(         0x800000, 0x200000 )
	ROM_LOAD16_BYTE( "092e.c4", 0xc00001, 0x200000, CRC(e1a8aa6a) SHA1(3e33d6e0d6a0feb8cc43dc511a2792922742547d) )
	ROM_CONTINUE(         0x800001, 0x200000 )
ROM_END

ROM_START( kof95e )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "084.p1",0x100000, 0x100000, CRC(2cba2716) SHA1(f6c2d0537c9c3e0938065c65b1797c47198fcff8) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "084.s1", CRC(de716f8a) SHA1(f7386454a943ed5caf625f67ee1d0197b1c6fa13) )

	NEO_BIOS_AUDIO_128K( "084.m1", CRC(6f2d7429) SHA1(6f8462e4f07af82a5ca3197895d5dcbb67bdaa61) )

	ROM_REGION( 0x900000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "084.v1", 0x000000, 0x400000, CRC(84861b56) SHA1(1b6c91ddaed01f45eb9b7e49d9c2b9b479d50da6) )
	ROM_LOAD( "084.v2", 0x400000, 0x200000, CRC(b38a2803) SHA1(dbc2c8606ca09ed7ff20906b022da3cf053b2f09) )
	ROM_LOAD( "084.v3", 0x800000, 0x100000, CRC(d683a338) SHA1(eb9866b4b286edc09963cb96c43ce0a8fb09adbb) )

	ROM_REGION( 0x1a00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "084e.c1", 0x0400000, 0x200000, CRC(33bf8657) SHA1(79b0f0eb4e5c172f36c296ccabeb474804f7645a) )
	ROM_CONTINUE(         0x0000000, 0x200000 )
	ROM_LOAD16_BYTE( "084e.c2", 0x0400001, 0x200000, CRC(f21908a4) SHA1(a0bec5961396e62af553ba5293b1007cdf9fbf62) )
	ROM_CONTINUE(         0x0000001, 0x200000 )
	ROM_LOAD16_BYTE( "084e.c3", 0x0c00000, 0x200000, CRC(0cee1ddb) SHA1(f63c05020c5bee37c2598fd235d76157baea6c68) )
	ROM_CONTINUE(         0x0800000, 0x200000 )
	ROM_LOAD16_BYTE( "084e.c4", 0x0c00001, 0x200000, CRC(729db15d) SHA1(6167a601463d7aaba1c8d470b346a82e9aef8bb5) )
	ROM_CONTINUE(         0x0800001, 0x200000 )
	ROM_LOAD16_BYTE( "084.c5", 0x1000000, 0x200000, CRC(8a2c1edc) SHA1(67866651bc0ce27122285a66b0aab108acf3d065) )
	ROM_LOAD16_BYTE( "084.c6", 0x1000001, 0x200000, CRC(f593ac35) SHA1(302c92c63f092a8d49429c3331e5e5678f0ea48d) )
	ROM_LOAD16_BYTE( "084.c7", 0x1800000, 0x100000, CRC(9904025f) SHA1(eec770746a0ad073f7d353ab16a2cc3a5278d307) )
	ROM_LOAD16_BYTE( "084.c8", 0x1800001, 0x100000, CRC(78eb0f9b) SHA1(2925ea21ed2ce167f08a25589e94f28643379034) )
ROM_END

ROM_START( kotm2e )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "039.p1", 0x000000, 0x080000, CRC(b372d54c) SHA1(b70fc6f72e16a66b6e144cc01370548e3398b8b8) )
	ROM_LOAD16_WORD_SWAP( "039.p2", 0x080000, 0x080000, CRC(28661afe) SHA1(6c85ff6ab334b1ca744f726f42dac211537e7315) )

	NEO_SFIX_128K( "039.s1", CRC(63ee053a) SHA1(7d4b92bd022708975b1470e8f24d1f5a712e1b94) )

	NEO_BIOS_AUDIO_128K( "039.m1", CRC(0c5b2ad5) SHA1(15eb5ea10fecdbdbcfd06225ae6d88bb239592e7) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "039.v2", 0x000000, 0x200000, CRC(86d34b25) SHA1(89bdb614b0c63d678962da52e2f596750d20828c) )
	ROM_LOAD( "039.v4", 0x200000, 0x100000, CRC(8fa62a0b) SHA1(58ac2fdd73c542eb8178cfc4adfa0e5940183283) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "039.c1", 0x000000, 0x100000, CRC(6d1c4aa9) SHA1(4fbc9d7cb37522ec298eefbe38c75a2d050fbb4a) )
	ROM_CONTINUE( 0x400000, 0x100000 )
	ROM_LOAD16_BYTE( "039.c2", 0x000001, 0x100000, CRC(f7b75337) SHA1(4d85f85948c3e6ed38b0b0ccda79de3ce026e2d9) )
	ROM_CONTINUE( 0x400001, 0x100000 )
	ROM_LOAD16_BYTE( "039e.c3", 0x200000, 0x100000, CRC(40156dca) SHA1(909b04757f1b90f225dde3a4c65c6a7d3e0d7289) )
	ROM_CONTINUE(         0x600000, 0x100000 )
	ROM_LOAD16_BYTE( "039e.c4", 0x200001, 0x100000, CRC(b0d44111) SHA1(9ef02149c87aeeb9fca611e57139e3ccf9ae72cd) )
	ROM_CONTINUE(         0x600001, 0x100000 )
ROM_END

ROM_START( magdrp3e )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "233.p1", 0x000000, 0x100000, CRC(931e17fa) SHA1(4a95c4b79d0878485ce272e9f4c4f647bec0e070) )

	NEO_SFIX_128K( "233.s1", CRC(7399e68a) SHA1(b535ee56a0f0995f04674e676f6aa636ffad26aa) )

	NEO_BIOS_AUDIO_128K( "233.m1", CRC(5beaf34e) SHA1(2905d26945932cddc2dd3a1dc5abba8aa3baee14) )

	ROM_REGION( 0x480000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "233.v1", 0x000000, 0x400000, CRC(58839298) SHA1(18cae7bba997c52780761cbf119c4e4b34397a61) )
	ROM_LOAD( "233.v2", 0x400000, 0x080000, CRC(d5e30df4) SHA1(bbbc0ff5b975471bd682f85976ac4a93f6d44f2e) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "233e.c1", 0x400000, 0x200000, CRC(734db3d6) SHA1(6d12b3ef34aae066f8c5cae5f6a272c8f482bdd0) )
	ROM_CONTINUE(         0x000000, 0x200000 )
	ROM_LOAD16_BYTE( "233e.c2", 0x400001, 0x200000, CRC(d78f50e5) SHA1(102526982596a9d3052d3f3181a98558c596c907) )
	ROM_CONTINUE(         0x000001, 0x200000 )
	ROM_LOAD16_BYTE( "233e.c3", 0xc00000, 0x200000, CRC(ec65f472) SHA1(23271ca8617d08f23417dd071333c91ef90715b5) )
	ROM_CONTINUE(         0x800000, 0x200000 )
	ROM_LOAD16_BYTE( "233e.c4", 0xc00001, 0x200000, CRC(f55dddf3) SHA1(fec0930e5cb26be4d73bfa8c76ef37eb4bbec60a) )
	ROM_CONTINUE(         0x800001, 0x200000 )
ROM_END

ROM_START( msluge )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "201.p1", 0x100000, 0x100000, CRC(08d8daa5) SHA1(b888993dbb7e9f0a28a01d7d2e1da00ef9cf6f38) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "201.s1", CRC(2f55958d) SHA1(550b53628daec9f1e1e11a398854092d90f9505a) )

	NEO_BIOS_AUDIO_128K( "201.m1", CRC(c28b3253) SHA1(fd75bd15aed30266a8b3775f276f997af57d1c06) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "201.v1", 0x000000, 0x400000, CRC(23d22ed1) SHA1(cd076928468ad6bcc5f19f88cb843ecb5e660681) )
	ROM_LOAD( "201.v2", 0x400000, 0x400000, CRC(472cf9db) SHA1(5f79ea9286d22ed208128f9c31ca75552ce08b57) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "201e.c1", 0x400000, 0x200000, CRC(d00bd152) SHA1(eb688dba2233bece1c3ba120ac8eb342f37fba37) )
	ROM_CONTINUE(         0x000000, 0x200000 )
	ROM_LOAD16_BYTE( "201e.c2", 0x400001, 0x200000, CRC(ddff1dea) SHA1(e6ac8950d8ad8498270097a248c4b49876804197) )
	ROM_CONTINUE(         0x000001, 0x200000 )
	ROM_LOAD16_BYTE( "201e.c3", 0xc00000, 0x200000, CRC(d3d5f9e5) SHA1(7d259314c2198ee81a380d76728c3c1ac2c8b528) )
	ROM_CONTINUE(         0x800000, 0x200000 )
	ROM_LOAD16_BYTE( "201e.c4", 0xc00001, 0x200000, CRC(5ac1d497) SHA1(313249ea47b3553974cde1c4c36f1ff3adeb07d1) )
	ROM_CONTINUE(         0x800001, 0x200000 )
ROM_END

ROM_START( neobombee )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "093.p1", 0x000000, 0x100000, CRC(a1a71d0d) SHA1(059284c84f61a825923d86d2f29c91baa2c439cd) )

	NEO_SFIX_128K( "093.s1", CRC(4b3fa119) SHA1(41cb0909bfb017eb6f2c530cb92a423319ed7ab1) )

	NEO_BIOS_AUDIO_128K( "093.m1", CRC(e81e780b) SHA1(c56c53984e0f92e180e850c60a75f550ee84917c) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "093e.v1", 0x200000, 0x200000, CRC(43057e99) SHA1(b24a44daf54ec76801e7dc863645022dc2d4abdb) )
	ROM_CONTINUE(  0x000000, 0x200000 )
	ROM_LOAD( "093.v2", 0x400000, 0x200000, CRC(a92b8b3d) SHA1(b672c97b85d2f52eba3cb26025008ebc7a18312a) )

	ROM_REGION( 0x900000, "sprites", 0 )
	ROM_LOAD16_BYTE( "093e.c1", 0x400000, 0x200000, CRC(b90ebed4) SHA1(e9e441fb9b425505e500e0e0b40ef11a43b2d4b2) )
	ROM_CONTINUE(         0x000000, 0x200000 )
	ROM_LOAD16_BYTE( "093e.c2", 0x400001, 0x200000, CRC(41e62b4f) SHA1(2fb1f752643d7dd3470ade76229e3756818412f7) )
	ROM_CONTINUE(         0x000001, 0x200000 )
	ROM_LOAD16_BYTE( "093.c3", 0x800000, 0x080000, CRC(e37578c5) SHA1(20024caa0f09ee887a6418dd02d02a0df93786fd) )
	ROM_LOAD16_BYTE( "093.c4", 0x800001, 0x080000, CRC(59826783) SHA1(0110a2b6186cca95f75225d4d0269d61c2ad25b1) )
ROM_END

ROM_START( neodrifte )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "213.p1", 0x100000, 0x100000, CRC(e397d798) SHA1(10f459111db4bab7aaa63ca47e83304a84300812) )
	ROM_CONTINUE( 0x000000, 0x100000)

	NEO_SFIX_128K( "213.s1", CRC(b76b61bc) SHA1(5fdb407d16ab9e33c4f26ee09ff70891ae1d2bd0) )

	NEO_BIOS_AUDIO_128K( "213.m1", CRC(200045f1) SHA1(7a6cd1c8d4447ea260d7ff4520c676b8d685f2e4) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "213.v1", 0x000000, 0x200000, CRC(a421c076) SHA1(129f05c1a28a6493442f47a79c2d3577a1a43ef5) )
	ROM_LOAD( "213.v2", 0x200000, 0x200000, CRC(233c7dd9) SHA1(be7f980aa83831b6605aaaf4ec904180bb96c935) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "213e.c1", 0x400000, 0x200000, CRC(62c5edc9) SHA1(df3ed81b37fc03503c8702741d361f44adfcd481) )
	ROM_CONTINUE(         0x000000, 0x200000 )
	ROM_LOAD16_BYTE( "213e.c2", 0x400001, 0x200000, CRC(9dc9c72a) SHA1(c3960b18d940233332c2b1ee2b2b94685c724d1e) )
	ROM_CONTINUE(         0x000001, 0x200000 )
ROM_END

ROM_START( ninjamse )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "217.p1",  0x000000, 0x100000, CRC(3e97ed69) SHA1(336bcae375a5109945d11356503bf0d9f4a9a50a) )
	ROM_LOAD16_WORD_SWAP( "217.p2", 0x100000, 0x200000, CRC(191fca88) SHA1(e318e5931704779bbe461719a5eeeba89bd83a5d) )

	NEO_SFIX_128K( "217.s1", CRC(8ff782f0) SHA1(90099c154357042ba658d4ef6abe4d9335bb7172) )

	NEO_BIOS_AUDIO_128K( "217.m1", CRC(d00fb2af) SHA1(6bcaa52e1641cc24288e1f22f4dc98e8d8921b90) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "217.v1", 0x000000, 0x400000, CRC(1c34e013) SHA1(5368e413d2188c4fd063b6bb7d5f498ff83ea812) )
	ROM_LOAD( "217.v2", 0x400000, 0x200000, CRC(22f1c681) SHA1(09da03b2e63d180e55173ff25e8735c4162f027b) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "217e.c1", 0x0400000, 0x200000, CRC(58f91ae0) SHA1(365e8b865bbd3a8a5ffc7d8ffa0e7694a0bf3a2a) )
	ROM_CONTINUE(         0x0000000, 0x200000 )
	ROM_LOAD16_BYTE( "217e.c2", 0x0400001, 0x200000, CRC(4258147f) SHA1(c996477ba1da2ee38e46fb3dc0ecfd322ff3dd52) )
	ROM_CONTINUE(         0x0000001, 0x200000 )
	ROM_LOAD16_BYTE( "217e.c3", 0x0c00000, 0x200000, CRC(36c29ce3) SHA1(90bfcf4c4d72fdc3d87055afb8ec56ab6cee7003) )
	ROM_CONTINUE(         0x0800000, 0x200000 )
	ROM_LOAD16_BYTE( "217e.c4", 0x0c00001, 0x200000, CRC(17e97a6e) SHA1(ecf5905a8116f2ae1ae7a42f13e0ebe770fadb14) )
	ROM_CONTINUE(         0x0800001, 0x200000 )
	ROM_LOAD16_BYTE( "217e.c5", 0x1400000, 0x200000, CRC(4683ffc0) SHA1(b3667cb143e2eb7a199e8b55e1815dd35abcf1ff) )
	ROM_CONTINUE(         0x1000000, 0x200000 )
	ROM_LOAD16_BYTE( "217e.c6", 0x1400001, 0x200000, CRC(de004f4a) SHA1(4b685e6efbfa74d7fcab2d1c8569df20662e2a6e) )
	ROM_CONTINUE(         0x1000001, 0x200000 )
	ROM_LOAD16_BYTE( "217e.c7", 0x1c00000, 0x200000, CRC(3e1885c0) SHA1(0fc611cbaebce6db3ff2caf54819a335aaf8dcab) )
	ROM_CONTINUE(         0x1800000, 0x200000 )
	ROM_LOAD16_BYTE( "217e.c8", 0x1c00001, 0x200000, CRC(5a5df034) SHA1(1863cdc8af52590b94c4a55f9333fc00d9b0b8a6) )
	ROM_CONTINUE(         0x1800001, 0x200000 )
ROM_END

ROM_START( pulstare )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "089.p1",  0x000000, 0x100000, CRC(5e5847a2) SHA1(b864d0ec4184b785569ddbf67c2115b5ab86ee3e) )
	ROM_LOAD16_WORD_SWAP( "089.p2", 0x100000, 0x200000, CRC(028b774c) SHA1(fc5da2821a5072f2b78245fc59b6e3eeef116d16) )

	NEO_SFIX_128K( "089.s1", CRC(c79fc2c8) SHA1(914c224fb3c461a68d7425cae724cf22bd5f985d) )

	NEO_BIOS_AUDIO_128K( "089.m1", CRC(ff3df7c7) SHA1(59d2ef64f734f6026073b365300221909057a512) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "089.v1", 0x000000, 0x400000, CRC(6f726ecb) SHA1(e8e2a46af690ce6c7ee64a58ab5010d22df9548c) )
	ROM_LOAD( "089.v2", 0x400000, 0x400000, CRC(9d2db551) SHA1(83f7e5db7fb1502ceadcd334df90b11b1bba78e5) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "089e.c1", 0x0400000, 0x200000, CRC(63020fc6) SHA1(68053804dabd146b4d39b0f39d63a30d322972f8) )
	ROM_CONTINUE(         0x0000000, 0x200000 )
	ROM_LOAD16_BYTE( "089e.c2", 0x0400001, 0x200000, CRC(260e9d4d) SHA1(99870c597003a3c70c6b4d11aefe5fe4e58f03f9) )
	ROM_CONTINUE(         0x0000001, 0x200000 )
	ROM_LOAD16_BYTE( "089e.c3", 0x0c00000, 0x200000, CRC(21ef41d7) SHA1(55b26f0f168da50a16de3de3365365df69c4998d) )
	ROM_CONTINUE(         0x0800000, 0x200000 )
	ROM_LOAD16_BYTE( "089e.c4", 0x0c00001, 0x200000, CRC(3b9e288f) SHA1(9bbf0ca0981dd44ed0651ffc978d60877802ec3d) )
	ROM_CONTINUE(         0x0800001, 0x200000 )
	ROM_LOAD16_BYTE( "089e.c5", 0x1400000, 0x200000, CRC(6fe9259c) SHA1(ff3b4da68ed01067dd0f0cde341a0da277b5401c) )
	ROM_CONTINUE(         0x1000000, 0x200000 )
	ROM_LOAD16_BYTE( "089e.c6", 0x1400001, 0x200000, CRC(dc32f2b4) SHA1(3ff3d81622946d6ab21a940f2bbc3999855aa6bf) )
	ROM_CONTINUE(         0x1000001, 0x200000 )
	ROM_LOAD16_BYTE( "089.c7", 0x1800000, 0x200000, CRC(6a5618ca) SHA1(9a1d5f998b0dfabacf9dad45c94bef2bb43e5e0c) )
	ROM_LOAD16_BYTE( "089.c8", 0x1800001, 0x200000, CRC(a223572d) SHA1(2791b1212f57937b2b2a95bc9e420c06d0c37669) )
ROM_END

ROM_START( ragnagrde )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "218.p1", 0x100000, 0x100000, CRC(ca372303) SHA1(67991e4fef9b36bc7d909810eebb857ac2f906f1) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "218.s1", CRC(7d402f9a) SHA1(59ec29d03e62e7a8bef689a124a9164f43b2ace1) )

	NEO_BIOS_AUDIO_128K( "218.m1", CRC(17028bcf) SHA1(7a4e8f33ce9b41beac2152b8f6003f247699e2e1) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "218.v1", 0x000000, 0x400000, CRC(61eee7f4) SHA1(5b11b1a0b1b74dfbc2998cbda9f8f7a5e9059957) )
	ROM_LOAD( "218.v2", 0x400000, 0x400000, CRC(6104e20b) SHA1(18e8aae3e51e141977d523a10e737ff68fe81910) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "218e.c1", 0x0400000, 0x200000, CRC(18f61d79) SHA1(d815f57710403c76dc7b119b13dea629feb3c341) )
	ROM_CONTINUE(         0x0000000, 0x200000 )
	ROM_LOAD16_BYTE( "218e.c2", 0x0400001, 0x200000, CRC(dbf4ff4b) SHA1(8fa0fb1df9e771089d72077642a847ea2066e401) )
	ROM_CONTINUE(         0x0000001, 0x200000 )
	ROM_LOAD16_BYTE( "218e.c3", 0x0c00000, 0x200000, CRC(108d5589) SHA1(04e25114cbf283f2a824f9e2127dc5ed96dc6d50) )
	ROM_CONTINUE(         0x0800000, 0x200000 )
	ROM_LOAD16_BYTE( "218e.c4", 0x0c00001, 0x200000, CRC(7962d5ac) SHA1(fd126e19fcff517ade00bd2394d675949d7cce1c) )
	ROM_CONTINUE(         0x0800001, 0x200000 )
	ROM_LOAD16_BYTE( "218e.c5", 0x1400000, 0x200000, CRC(4b74021a) SHA1(021dfa2dbfb06933362c7e34350e24ab23d34ebc) )
	ROM_CONTINUE(         0x1000000, 0x200000 )
	ROM_LOAD16_BYTE( "218e.c6", 0x1400001, 0x200000, CRC(f5cf90bc) SHA1(6a1ea01b1610bb20f8dc68943ff622e7e600257b) )
	ROM_CONTINUE(         0x1000001, 0x200000 )
	ROM_LOAD16_BYTE( "218e.c7", 0x1c00000, 0x200000, CRC(32189762) SHA1(355c9780ed73e48316bb9402b972a47810fa8807) )
	ROM_CONTINUE(         0x1800000, 0x200000 )
	ROM_LOAD16_BYTE( "218e.c8", 0x1c00001, 0x200000, CRC(d5915828) SHA1(996930728f5f6aea180aba110e5214dc37f5b84a) )
	ROM_CONTINUE(         0x1800001, 0x200000 )
ROM_END

ROM_START( rbffspece )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "223.p1",  0x000000, 0x100000, CRC(f84a2d1d) SHA1(fc19225d9dbdb6bd0808023ee32c7829f6ffdef6) )
	ROM_LOAD16_WORD_SWAP( "223e.p2", 0x300000, 0x200000, CRC(27e3e54b) SHA1(09f8912c9f105e54bac9781680859988f43917e8) )
	ROM_CONTINUE( 0x100000, 0x200000 )

	NEO_SFIX_128K( "223.s1", CRC(7ecd6e8c) SHA1(465455afc4d83cbb118142be4671b2539ffafd79) )

	NEO_BIOS_AUDIO_128K( "223.m1", CRC(3fee46bf) SHA1(e750f85233953853618fcdff980a4721af1710a3) )

	ROM_REGION( 0xc00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "223.v1", 0x000000, 0x400000, CRC(76673869) SHA1(78a26afa29f73de552ffabdbf3fc4bf26be8ae9e) )
	ROM_LOAD( "223.v2", 0x400000, 0x400000, CRC(7a275acd) SHA1(8afe87ce822614262b72a90b371fc79155ac0d0c) )
	ROM_LOAD( "223.v3", 0x800000, 0x400000, CRC(5a797fd2) SHA1(94958e334f86d4d71059af8138f255b8d97a3b01) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "223e.c1", 0x0400000, 0x200000, CRC(436edad4) SHA1(1ee871a7b720b46a84845dbfd6c0dcb1ffc95502) )
	ROM_CONTINUE(         0x0000000, 0x200000 )
	ROM_LOAD16_BYTE( "223e.c2", 0x0400001, 0x200000, CRC(cc7dc384) SHA1(31c6c872d0a3a0a7a55195f703eba36f1a631b9f) )
	ROM_CONTINUE(         0x0000001, 0x200000 )
	ROM_LOAD16_BYTE( "223e.c3", 0x0c00000, 0x200000, CRC(375954ea) SHA1(6e5e54f614f7985b309cbcc8ca9e441860074d8f) )
	ROM_CONTINUE(         0x0800000, 0x200000 )
	ROM_LOAD16_BYTE( "223e.c4", 0x0c00001, 0x200000, CRC(c1a98dd7) SHA1(e9094ee40374bd5134c9060ba6526fd00e9eb8b0) )
	ROM_CONTINUE(         0x0800001, 0x200000 )
	ROM_LOAD16_BYTE( "223e.c5", 0x1400000, 0x200000, CRC(12c5418e) SHA1(133e15a6667e17041782ffa594845b121548e63c) )
	ROM_CONTINUE(         0x1000000, 0x200000 )
	ROM_LOAD16_BYTE( "223e.c6", 0x1400001, 0x200000, CRC(c8ad71d5) SHA1(d55bd1395a48509fb091fa2321606c88a988583e) )
	ROM_CONTINUE(         0x1000001, 0x200000 )
	ROM_LOAD16_BYTE( "223e.c7", 0x1c00000, 0x200000, CRC(5c33d1d8) SHA1(924121e9e29e46b5158f8caa47799230065d1b00) )
	ROM_CONTINUE(         0x1800000, 0x200000 )
	ROM_LOAD16_BYTE( "223e.c8", 0x1c00001, 0x200000, CRC(efdeb140) SHA1(faf7e7a38891b08d2dd17f427fda05586cceab7f) )
	ROM_CONTINUE(         0x1800001, 0x200000 )
ROM_END

ROM_START( roboarme )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "032.p1", 0x000000, 0x080000, CRC(cd11cbd4) SHA1(23163e3da2f07e830a7f4a02aea1cb01a54ccbf3) )

	NEO_SFIX_128K( "032.s1", CRC(ac0daa1b) SHA1(93bae4697dc403fce19422752a514326ccf66a91) )

	NEO_BIOS_AUDIO_128K( "032e.m1", CRC(98edc671) SHA1(04ed65ccaa1197fa55fcefe2caed2772e7040bdb) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "032e.v1", 0x000000, 0x080000, CRC(daff9896) SHA1(2f8a39b98ff2f4a0c8901b1befcc69e0cc5f5aed) )
	ROM_LOAD( "032e.v2", 0x080000, 0x080000, CRC(8781b1bc) SHA1(4e3cc22ac0acd4033cd4a327269c68b5f56bbe34) )
	ROM_LOAD( "032e.v3", 0x100000, 0x080000, CRC(b69c1da5) SHA1(7d5ea49338aeef711fc64755abed51fcdd939d48) )
	ROM_LOAD( "032e.v4", 0x180000, 0x080000, CRC(2c929c17) SHA1(7e053035573de9f601de80d200d09ed4844506fe) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "032e.c1", 0x000000, 0x080000, CRC(e17fa618) SHA1(14347886b776c24d2dd8b19353ad8897d5f7e56c) )
	ROM_LOAD16_BYTE( "032e.c2", 0x000001, 0x080000, CRC(d5ebdb4d) SHA1(cc811af611cc528fd3a9d1bdd8ab427fe9fea693) )
	ROM_LOAD16_BYTE( "032e.c3", 0x100000, 0x080000, CRC(aa4d7695) SHA1(2d6c5b4f6fce82b5800fae17b4a94cf8a41216f4) )
	ROM_LOAD16_BYTE( "032e.c4", 0x100001, 0x080000, CRC(8d4ebbe3) SHA1(384ee64db1726b0aef2d3ce8b1d914b56e7925d9) )
	ROM_LOAD16_BYTE( "032.c5",  0x200000, 0x080000, CRC(40adfccd) SHA1(b11f866dd70ba0ed9123424508355cb948b19bdc) )
	ROM_LOAD16_BYTE( "032.c6",  0x200001, 0x080000, CRC(462571de) SHA1(5c3d610d492f91564423873b3b434dcda700373f) )
ROM_END

ROM_START( samsho3e )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "087h.p1", 0x000000, 0x100000, CRC(282a336e) SHA1(e062f1939d36a45f185b5dbd726cdd833dc7c28c) )
	ROM_LOAD16_WORD_SWAP( "087k.p2", 0x100000, 0x200000, CRC(9bbe27e0) SHA1(b18117102159903c8e8f4e4226e1cc91a400e816) )

	NEO_SFIX_128K( "087.s1", CRC(74ec7d9f) SHA1(d79c479838a7ca51735a44f91f1968ec5b3c6b91) )

	NEO_BIOS_AUDIO_128K( "087.m1", CRC(8e6440eb) SHA1(e3f72150af4e326543b29df71cda27d73ec087c1) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "087.v1", 0x000000, 0x400000, CRC(84bdd9a0) SHA1(adceceb00569eca13fcc2e0f0d9f0d9b06a06851) )
	ROM_LOAD( "087.v2", 0x400000, 0x200000, CRC(ac0f261a) SHA1(5411bdff24cba7fdbc3397d45a70fb468d7a44b3) )

	ROM_REGION( 0x1a00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "087e.c1", 0x0400000, 0x200000, CRC(e079f767) SHA1(0c2e983e68f3a3b25713b2aa8a5f39bc03561672) )
	ROM_CONTINUE(         0x0000000, 0x200000 )
	ROM_LOAD16_BYTE( "087e.c2", 0x0400001, 0x200000, CRC(fc045909) SHA1(7cb6b5d8abaf6bf54853e28454cc1f518298fdfa) )
	ROM_CONTINUE(         0x0000001, 0x200000 )
	ROM_LOAD16_BYTE( "087e.c3", 0x0c00000, 0x200000, CRC(c61218d7) SHA1(d92344a019bc5c8091ac4c8e6b7d9b2e99309bbe) )
	ROM_CONTINUE(         0x0800000, 0x200000 )
	ROM_LOAD16_BYTE( "087e.c4", 0x0c00001, 0x200000, CRC(054ec754) SHA1(324b06a80b6b268781081731756ddb1254c23991) )
	ROM_CONTINUE(         0x0800001, 0x200000 )
	ROM_LOAD16_BYTE( "087e.c5", 0x1400000, 0x200000, CRC(05feee47) SHA1(d5be7ca85dca73d900a30bb635a531ba39891251) )
	ROM_CONTINUE(         0x1000000, 0x200000 )
	ROM_LOAD16_BYTE( "087e.c6", 0x1400001, 0x200000, CRC(ef7d9e29) SHA1(853f73769de504a6747f538829b3f9a0b7e841bc) )
	ROM_CONTINUE(         0x1000001, 0x200000 )
	ROM_LOAD16_BYTE( "087e.c7", 0x1800000, 0x080000, CRC(7a01f666) SHA1(d177f165fc7bbd9742e0e236ef8182b48d89e982) )
	ROM_LOAD16_BYTE( "087e.c8", 0x1800001, 0x080000, CRC(ffd009c2) SHA1(1b49e36596ca6bef3d7c943491b496eb759975d7) )
ROM_END

ROM_START( samsho4e )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "222.p1",  0x000000, 0x100000, CRC(1a5cb56d) SHA1(9a0a5a1c7c5d428829f22d3d17f7033d43a51b5b) )
	ROM_LOAD16_WORD_SWAP( "222e.p2", 0x300000, 0x200000, CRC(7587f09b) SHA1(4cbd14b1e5158ab2c96b0860afc550b5dc746ca7) )
	ROM_CONTINUE( 0x100000, 0x200000 )

	NEO_SFIX_128K( "222.s1", CRC(8d3d3bf9) SHA1(9975ed9b458bdd14e23451d2534153f68a5e4e6c) )

	NEO_BIOS_AUDIO_128K( "222.m1", CRC(7615bc1b) SHA1(b936f7b341f6fe0921b4c41049734684583e3596) )

	ROM_REGION( 0xa00000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "222.v1", 0x000000, 0x400000, CRC(7d6ba95f) SHA1(03cb4e0d770e0b332b07b64cacef624460b84c78) )
	ROM_LOAD( "222.v2", 0x400000, 0x400000, CRC(6c33bb5d) SHA1(fd5d4e08a962dd0d22c52c91bad5ec7f23cfb901) )
	ROM_LOAD( "222.v3", 0x800000, 0x200000, CRC(831ea8c0) SHA1(f2987b7d09bdc4311e972ce8a9ab7ca9802db4db) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "222e.c1", 0x0400000, 0x200000, CRC(289100fa) SHA1(ead308ba395e4ddaa3e4e096cc6d264529132373) )
	ROM_CONTINUE(         0x0000000, 0x200000 )
	ROM_LOAD16_BYTE( "222e.c2", 0x0400001, 0x200000, CRC(c2716ea0) SHA1(06f2d218c0c90d978b03e8312fc1e79157a479f8) )
	ROM_CONTINUE(         0x0000001, 0x200000 )
	ROM_LOAD16_BYTE( "222e.c3", 0x0c00000, 0x200000, CRC(6659734f) SHA1(200c97e449057298b38cf67b053c241f2edfa740) )
	ROM_CONTINUE(         0x0800000, 0x200000 )
	ROM_LOAD16_BYTE( "222e.c4", 0x0c00001, 0x200000, CRC(91ebea00) SHA1(6574795885dd1e29f02e4973a391ff1964675896) )
	ROM_CONTINUE(         0x0800001, 0x200000 )
	ROM_LOAD16_BYTE( "222e.c5", 0x1400000, 0x200000, CRC(e22254ed) SHA1(56212ab8e24a78a990fa92fbb911f85e72783883) )
	ROM_CONTINUE(         0x1000000, 0x200000 )
	ROM_LOAD16_BYTE( "222e.c6", 0x1400001, 0x200000, CRC(00947b2e) SHA1(8e986b2f348d2977e9c0272e4d0879def07bcf1e) )
	ROM_CONTINUE(         0x1000001, 0x200000 )
	ROM_LOAD16_BYTE( "222e.c7", 0x1c00000, 0x200000, CRC(e3e3b0cd) SHA1(a722d14ea2c0a6882534568b5fc6e068605c13d8) )
	ROM_CONTINUE(         0x1800000, 0x200000 )
	ROM_LOAD16_BYTE( "222e.c8", 0x1c00001, 0x200000, CRC(f33967f1) SHA1(780a05ba8c1873748842599a71672140d1ffd2e8) )
	ROM_CONTINUE(         0x1800001, 0x200000 )
ROM_END

ROM_START( shocktre )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "238.p1",  0x000000, 0x100000, CRC(5677456f) SHA1(f76169fa5c90871d65e2a16fd1bb036c90533ac8) )
	ROM_LOAD16_WORD_SWAP( "238.p2", 0x100000, 0x400000, CRC(5b4a09c5) SHA1(de04036cba2da4bb2da73d902d1822b82b4f67a9) )

	NEO_SFIX_128K( "238.s1", CRC(1f95cedb) SHA1(adfa74868147fd260481e4c387d254d3b6de83f4) )

	NEO_BIOS_AUDIO_128K( "238.m1", CRC(075b9518) SHA1(ac21b88a860b9572bf24432b4cadcc96d108055d) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "238.v1", 0x000000, 0x400000, CRC(260c0bef) SHA1(9c4f80ce4bb205afed11bb8b8926d20748eb5512) )
	ROM_LOAD( "238.v2", 0x400000, 0x200000, CRC(4ad7d59e) SHA1(bfdf2684f7f38af4e75ad0068ff9463dc2601598) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "238e.c1", 0x0400000, 0x200000, CRC(aad087fc) SHA1(7246269496d53b4af2ee12a69620f29272ea9037) )
	ROM_CONTINUE(         0x0000000, 0x200000 )
	ROM_LOAD16_BYTE( "238e.c2", 0x0400001, 0x200000, CRC(7e39df1f) SHA1(ecead5bf06dc5719de0ae7593560b37e0f1481b0) )
	ROM_CONTINUE(         0x0000001, 0x200000 )
	ROM_LOAD16_BYTE( "238e.c3", 0x0c00000, 0x200000, CRC(6682a458) SHA1(2dc2c8c88d5c471869b08596eef585ad18f2b370) )
	ROM_CONTINUE(         0x0800000, 0x200000 )
	ROM_LOAD16_BYTE( "238e.c4", 0x0c00001, 0x200000, CRC(cbef1f17) SHA1(25080c4f4ac4e7075c4f976d8fa6ab4d8f7d7237) )
	ROM_CONTINUE(         0x0800001, 0x200000 )
	ROM_LOAD16_BYTE( "238e.c5", 0x1400000, 0x200000, CRC(e17762b1) SHA1(1cc8cb9e485d86e5e0e50bcbe0e81cfb273f0664) )
	ROM_CONTINUE(         0x1000000, 0x200000 )
	ROM_LOAD16_BYTE( "238e.c6", 0x1400001, 0x200000, CRC(28beab71) SHA1(683abb317b1b95ba122859aea701f52197c10208) )
	ROM_CONTINUE(         0x1000001, 0x200000 )
	ROM_LOAD16_BYTE( "238e.c7", 0x1c00000, 0x200000, CRC(a47e62d2) SHA1(39285f78a9ed1138034de91efb7045084a5925f0) )
	ROM_CONTINUE(         0x1800000, 0x200000 )
	ROM_LOAD16_BYTE( "238e.c8", 0x1c00001, 0x200000, CRC(e8e890fb) SHA1(abbbfa0e162d7711d62df08a9721d8c923888c78) )
	ROM_CONTINUE(         0x1800001, 0x200000 )
ROM_END

ROM_START( sonicw3e )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "097.p1", 0x100000, 0x100000, CRC(0547121d) SHA1(e0bb6c614f572b74ba9a9f0d3d5b69fbc91ebc52) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "097.s1", CRC(8dd66743) SHA1(39214bb25a1d5b44a8524010be05bf5a0211981f) )

	NEO_BIOS_AUDIO_128K( "097.m1", CRC(b20e4291) SHA1(0e891ab53f9fded510295dfc7818bc59b4a9dd97) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "097.v1", 0x000000, 0x400000, CRC(6f885152) SHA1(8175804d5c1420c5d37b733d4a8fa2aa81e59f1b) )
	ROM_LOAD( "097e.v2", 0x400000, 0x100000, CRC(32187ccd) SHA1(35a93de2a23bdec181c504d9c21a871bf86edee1) )

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "097e.c1", 0x400000, 0x200000, CRC(3ca97864) SHA1(5fa9dbc698a239cbd8ea1d54e6a301a65406c8d7) )
	ROM_CONTINUE(         0x000000, 0x200000 )
	ROM_LOAD16_BYTE( "097e.c2", 0x400001, 0x200000, CRC(1da4b3a9) SHA1(7de21780a9d606e22be3ad597d6e0f1480089b31) )
	ROM_CONTINUE(         0x000001, 0x200000 )
	ROM_LOAD16_BYTE( "097.c3", 0x800000, 0x200000, CRC(c339fff5) SHA1(58dfd1e30dc0ad3f816a5dbd1cc7e7ccbb792c53) )
	ROM_LOAD16_BYTE( "097.c4", 0x800001, 0x200000, CRC(84a40c6e) SHA1(061a13fba5fed883e5ee9566cedc208df2511bcf) )
ROM_END

ROM_START( ssidek4e )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "215.p1", 0x100000, 0x100000, CRC(519b4ba3) SHA1(5aa59514b23aa663f2c4014ee94a31e9f59151de) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "215.s1", CRC(f0fe5c36) SHA1(b7badd6d2ac3788ce5cace1fcf5cdad14734e4e6) )

	NEO_BIOS_AUDIO_128K( "215.m1", CRC(a932081d) SHA1(376a45e19edb780ac8798c41ae2260c8a8a4bba8) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "215e.v1", 0x200000, 0x200000, CRC(c4bfed62) SHA1(6fec1880eef16f2d1bce152f3c73fb3ea1a931a0) )
	ROM_CONTINUE(  0x000000, 0x200000 )
	ROM_LOAD( "215.v2", 0x400000, 0x200000, CRC(1bfa218b) SHA1(344836a578bde3c0ab59b58c8734f868e7403c26) )

	ROM_REGION( 0x1400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "215e.c1", 0x0400000, 0x200000, CRC(288a9225) SHA1(403acb892c0d0f2e5cdf4b0bb4b5843ab6e95874) )
	ROM_CONTINUE(         0x0000000, 0x200000 )
	ROM_LOAD16_BYTE( "215e.c2", 0x0400001, 0x200000, CRC(3fc9d1c4) SHA1(247dd81fe521876b3970c3ec8e260ada5618df8c) )
	ROM_CONTINUE(         0x0000001, 0x200000 )
	ROM_LOAD16_BYTE( "215e.c3", 0x0c00000, 0x200000, CRC(fedfaebe) SHA1(145007cf98b16c0d82385ce5df0b17806eb93ed8) )
	ROM_CONTINUE(         0x0800000, 0x200000 )
	ROM_LOAD16_BYTE( "215e.c4", 0x0c00001, 0x200000, CRC(877a5bb2) SHA1(7234b1cd5ae299a3596f05f7e9387b72dd425b36) )
	ROM_CONTINUE(         0x0800001, 0x200000 )
	ROM_LOAD16_BYTE( "215.c5", 0x1000000, 0x200000, CRC(0c6f97ec) SHA1(b8d297f0ba2b04404eb0f7c6673ecc206fadae0c) )
	ROM_LOAD16_BYTE( "215.c6", 0x1000001, 0x200000, CRC(329c5e1b) SHA1(015c36b8d3efab9b4647f110ecb5c118a9c80f43) )
ROM_END

ROM_START( turfmste )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "200.p1", 0x100000, 0x100000, CRC(28c83048) SHA1(e7ef87e1de21d2bb17ef17bb08657e92363f0e9a) )
	ROM_CONTINUE( 0x000000, 0x100000)

	NEO_SFIX_128K( "200.s1", CRC(9a5402b2) SHA1(ae1a0b5450869d61b2bb23671c744d3dda8769c4) )

	NEO_BIOS_AUDIO_128K( "200.m1", CRC(9994ac00) SHA1(7bded797f3b80fd00bcbe451ac0abe6646b19a14) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "200.v1", 0x000000, 0x200000, CRC(00fd48d2) SHA1(ddfee09328632e598fd51537b3ae8593219b2111) )
	ROM_LOAD( "200.v2", 0x200000, 0x200000, CRC(082acb31) SHA1(2f1c053040e9d50a6d45fd7bea1b96742bae694f) )
	ROM_LOAD( "200.v3", 0x400000, 0x200000, CRC(7abca053) SHA1(e229bc0ea82a371d6ee8fd9fe442b0fd141d0a71) )
	ROM_LOAD( "200.v4", 0x600000, 0x200000, CRC(6c7b4902) SHA1(d55e0f542d928a9a851133ff26763c8236cbbd4d) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "200e.c1", 0x400000, 0x200000, CRC(8c6733f2) SHA1(c4d20a8df03bbb6bb72b8fc089d4833b79c75cee) )
	ROM_CONTINUE(         0x000000, 0x200000 )
	ROM_LOAD16_BYTE( "200e.c2", 0x400001, 0x200000, CRC(596cc256) SHA1(705f949b3ba721b2e7973eaf2b2f9283dfef778c) )
	ROM_CONTINUE(         0x000001, 0x200000 )
ROM_END

ROM_START( twinspre )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "224.p1", 0x100000, 0x100000, CRC(7697e445) SHA1(5b55ca120f77a931d40719b14e0bfc8cac1d628c) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "224.s1", CRC(eeed5758) SHA1(24e48f396716e145b692468762cf595fb7267873) )

	NEO_BIOS_AUDIO_128K( "224.m1", CRC(364d6f96) SHA1(779b95a6476089b71f48c8368d9043ee1dba9032) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "224.v1", 0x000000, 0x400000, CRC(ff57f088) SHA1(1641989b8aac899dbd68aa2332bcdf9b90b33564) )
	ROM_LOAD( "224.v2", 0x400000, 0x200000, CRC(7ad26599) SHA1(822030037b7664795bf3d64e1452d0aecc22497e) )

	ROM_REGION( 0xa00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "224e.c1", 0x400000, 0x200000, CRC(73b2a70b) SHA1(7444cbfc6d29810fcd6eae93508609e919e3c153) )
	ROM_CONTINUE(         0x000000, 0x200000 )
	ROM_LOAD16_BYTE( "224e.c2", 0x400001, 0x200000, CRC(3a3e506c) SHA1(076e78a68b26822c3c69fe8fbc0104dcec8dd880) )
	ROM_CONTINUE(         0x000001, 0x200000 )
	ROM_LOAD16_BYTE( "224.c3", 0x800000, 0x100000, CRC(c59e4129) SHA1(93f02d1b4fbb152a9d336494fbff0d7642921de5) )
	ROM_LOAD16_BYTE( "224.c4", 0x800001, 0x100000, CRC(b5532e53) SHA1(7d896c25ba97f6e5d43c13d4df4ba72964a976ed) )
ROM_END

ROM_START( tws96e )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "086.p1", 0x000000, 0x100000, CRC(03e20ab6) SHA1(3a0a5a54649178ce7a6158980cb4445084b40fb5) )

	NEO_SFIX_128K( "086.s1", CRC(6f5e2b3a) SHA1(273341489f6625d35a4a920042a60e2b86373847) )

	NEO_BIOS_AUDIO_64K( "086e.m1", CRC(860ba8c7) SHA1(6457964fd2fdda1d4f57787fff0cec76b47692cb) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "086.v1", 0x000000, 0x200000, CRC(97bf1986) SHA1(b80d3a37e18d0a52f1e0092dc300989c9647efd1) )
	ROM_LOAD( "086.v2", 0x200000, 0x200000, CRC(b7eb05df) SHA1(ff2b55c7021c248cfdcfc9cd3658f2896bcbca38) )

	ROM_REGION( 0xa00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "086e.c1", 0x400000, 0x200000, CRC(d301a867) SHA1(6ec5ef48943750ac03d7b574b1aa87b84f01dfab) )
	ROM_CONTINUE(         0x000000, 0x200000 )
	ROM_LOAD16_BYTE( "086e.c2", 0x400001, 0x200000, CRC(305fc74f) SHA1(27b3c9eb96dadea05a5f3252e425eb605e12c619) )
	ROM_CONTINUE(         0x000001, 0x200000 )
	ROM_LOAD16_BYTE( "086.c3", 0x800000, 0x100000, CRC(750ddc0c) SHA1(9304a83d81afd544d88be0cd3ee47ae401d2da0e) )
	ROM_LOAD16_BYTE( "086.c4", 0x800001, 0x100000, CRC(7a6e7d82) SHA1(b1bb82cec3d68367d5e01e63c44c11b67e577411) )
ROM_END

ROM_START( wakuwk7e )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "225.p1",  0x000000, 0x100000, CRC(b14da766) SHA1(bdffd72ff705fc6b085a4026217bac1c4bc93163) )
	ROM_LOAD16_WORD_SWAP( "225.p2", 0x100000, 0x200000, CRC(fe190665) SHA1(739d9a8fc2da34381654d9e291141eacc210ae5c) )

	NEO_SFIX_128K( "225.s1", CRC(71c4b4b5) SHA1(9410f13807f01082dc86f2d84051be4bed8e9f7c) )

	NEO_BIOS_AUDIO_128K( "225.m1", CRC(0634bba6) SHA1(153aaf016440500df7a4454f3f2f2911219cb7d8) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "225.v1", 0x000000, 0x400000, CRC(6195c6b4) SHA1(66c06b5904aedb256e3997bbec60f8ab50c6ff0c) )
	ROM_LOAD( "225.v2", 0x400000, 0x400000, CRC(6159c5fe) SHA1(9015e93416497f1ef877c717afed40f7ecfa42e4) )

	ROM_REGION( 0x1800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "225e.c1", 0x0400000, 0x200000, CRC(d91d386f) SHA1(35cd98aa5153f5da2d106ea2e138f419ea8eeccd) )
	ROM_CONTINUE(         0x0000000, 0x200000 )
	ROM_LOAD16_BYTE( "225e.c2", 0x0400001, 0x200000, CRC(36b5cf41) SHA1(6a135cf0b950a7ea5a5084d8affbe7b318566f13) )
	ROM_CONTINUE(         0x0000001, 0x200000 )
	ROM_LOAD16_BYTE( "225e.c3", 0x0c00000, 0x200000, CRC(02fcff2f) SHA1(e160d6410185a9bf7dd7dd81cdbecf3d0c524ede) )
	ROM_CONTINUE(         0x0800000, 0x200000 )
	ROM_LOAD16_BYTE( "225e.c4", 0x0c00001, 0x200000, CRC(cd7f1241) SHA1(51b3d47025e705eee6d95da52ecd74de3be52029) )
	ROM_CONTINUE(         0x0800001, 0x200000 )
	ROM_LOAD16_BYTE( "225e.c5", 0x1400000, 0x200000, CRC(03d32f25) SHA1(19ca7a77dfd645170ec2e77a8836ce4ba5b4da3a) )
	ROM_CONTINUE(         0x1000000, 0x200000 )
	ROM_LOAD16_BYTE( "225e.c6", 0x1400001, 0x200000, CRC(d996a90a) SHA1(f0365056a7b4f660b00c670a17efbb9f70e8db5d) )
	ROM_CONTINUE(         0x1000001, 0x200000 )
ROM_END

ROM_START( whpe )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "090.p1", 0x100000, 0x100000, CRC(afaa4702) SHA1(83d122fddf17d4774353abf4a0655f3939f7b752) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "090.s1", CRC(174a880f) SHA1(c35d315d728d119a6e9aa42e0593937c90897449) )

	NEO_BIOS_AUDIO_128K( "090.m1", CRC(28065668) SHA1(0c60d4afa1dccad0135e733104f056be73b54e4e) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "090.v1", 0x000000, 0x200000, CRC(30cf2709) SHA1(d1845033f16de2470afd3858ee0efb45176d9ed7) )
	ROM_LOAD( "064.v2", 0x200000, 0x200000, CRC(b6527edd) SHA1(2bcf5bfa6e117cf4a3728a5e5f5771313c93f22a) )
	ROM_LOAD( "090.v3", 0x400000, 0x200000, CRC(1908a7ce) SHA1(78f31bcfea33eb94752bbf5226c481baec1af5ac) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD16_BYTE( "090e.c1", 0x0400000, 0x200000, CRC(aecd5bb1) SHA1(9f36deef46c7918417ccfb16abf77659686f80f2) )
	ROM_CONTINUE(       0x0000000, 0x200000 )
	ROM_LOAD16_BYTE( "090e.c2", 0x0400001, 0x200000, CRC(7566ffc0) SHA1(93f7be5dbf7657e264c434d1dc6dc5d9bd82feb0) )
	ROM_CONTINUE(       0x0000001, 0x200000 )
	ROM_LOAD16_BYTE( "064.c3", 0x0800000, 0x200000, CRC(436d1b31) SHA1(059776d77b91377ed0bcfc278802d659c917fc0f) )
	ROM_LOAD16_BYTE( "064.c4", 0x0800001, 0x200000, CRC(f9c8dd26) SHA1(25a9eea1d49b21b4a988beb32c25bf2f7796f227) )
	ROM_LOAD16_BYTE( "064.c5", 0x1000000, 0x200000, CRC(8e34a9f4) SHA1(67b839b426ef3fad0a85d951fdd44c0a45c55226) )
	ROM_LOAD16_BYTE( "064.c6", 0x1000001, 0x200000, CRC(a43e4766) SHA1(54f282f2b1ff2934cca7acbb4386a2b99a29df3a) )
	ROM_LOAD16_BYTE( "064.c7", 0x1800000, 0x200000, CRC(59d97215) SHA1(85a960dc7f364df13ee0c2f99a4c53aefb081486) )
	ROM_LOAD16_BYTE( "064.c8", 0x1800001, 0x200000, CRC(fc092367) SHA1(69ff4ae909dd857de3ca8645d63f8b4bde117448) )
ROM_END

ROM_START( wjammere )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "065e.p1", 0x000000, 0x080000, CRC(e81e7a31) SHA1(bb1a8922afe269f6e3ea63c3a377c2a6e2171d2d) )

	NEO_SFIX_128K( "065.s1", CRC(074b5723) SHA1(86d3b3bb5414f43e4d3b7a2af0db23cc71ce8412) )

	NEO_BIOS_AUDIO_128K( "065.m1", CRC(52c23cfc) SHA1(809a7e072ad9acbffc25e9bd27cdb97638d09d07) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "065.v1", 0x000000, 0x100000, CRC(ce8b3698) SHA1(7d75e2a5cf8c90be422f8b425447e81597fe145a) )
	ROM_LOAD( "065.v2", 0x100000, 0x100000, CRC(659f9b96) SHA1(62f40365212153bc3b92a1187fa44f6cdc7f7b83) )
	ROM_LOAD( "065.v3", 0x200000, 0x100000, CRC(39f73061) SHA1(ec57cd58e7f8569cff925d11e2320d588ce4fe49) )
	ROM_LOAD( "065.v4", 0x300000, 0x100000, CRC(5dee7963) SHA1(f8e6de73d65dd80b29c711f00835a574a770cb4e) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "065.c1", 0x000000, 0x100000, CRC(c7650204) SHA1(42918d700d59864f8ab15caf968a062a563c9b09) )
	ROM_LOAD16_BYTE( "065.c2", 0x000001, 0x100000, CRC(d9f3e71d) SHA1(fad1f64061eac1bf85bf6d75d2eae974a8c94069) )
	ROM_LOAD16_BYTE( "065.c3", 0x200000, 0x100000, CRC(40986386) SHA1(65795a50197049681265946713d416c9cdb68f08) )
	ROM_LOAD16_BYTE( "065.c4", 0x200001, 0x100000, CRC(715e15ff) SHA1(ac8b8b01f5c7384b883afbe0cf977430378e3fef) )
ROM_END

 /********************
  Multi Game Doctor 2 
***********************/

ROM_START( 2020bbd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n030001a.038", 0x000001, 0x040000, CRC(efb016a2) SHA1(6bac3f89124e9af5c04e7e5b110e467a4ed85771) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "030.s1", CRC(7015b8fc) SHA1(8c09bc3e6c62e0f7c9557c1e10c901be325bae7f) ) // n030001a.378

	NEO_BIOS_AUDIO_128K( "n030001a.4f8", CRC(bf755068) SHA1(7f624a691f7e51481949462141778da3e1eb0b91) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n030001a.1f8", 0x000000, 0x080000, CRC(33e7886e) SHA1(78bd48fea1e2b1595661c8b957fe489c11e50b92) )
	ROM_LOAD( "n030001a.1fc", 0x080000, 0x080000, CRC(e7ca3882) SHA1(40fb282ad0560d5933badd03da927d395d2a70b5) )
	ROM_LOAD( "n030001b.1f8", 0x100000, 0x080000, CRC(3cf9a433) SHA1(3065079247f1f4a44452a9bb84c9a969fbd3773b) )
	ROM_LOAD( "n030001b.1fc", 0x180000, 0x080000, CRC(88b10192) SHA1(ef486cc57a9cba6c4382b9fd8839e3beb57e916d) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n030001a.538", 0x000000, 0x40000, CRC(746bf48a) SHA1(93006169cb4e26bf72372c5354e60f814f39df3a) )
	ROM_CONTINUE( 0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n030001a.638", 0x000001, 0x40000, CRC(5c123d9c) SHA1(98ce390641ad11823db5de779e01bf06c2eabb8a) )
	ROM_CONTINUE( 0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n030001a.53c", 0x100000, 0x40000, CRC(57bdcec0) SHA1(6a0cfc50386dff079be93a9ee96722ea1b3df9fc) )
	ROM_CONTINUE( 0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n030001a.63c", 0x100001, 0x40000, CRC(2f4bb615) SHA1(5cfda589291579edbabfc84894e1b9a8875588f2) )
	ROM_CONTINUE( 0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n030001b.538", 0x200000, 0x40000, CRC(0b054a38) SHA1(4a917b0dcbe4b270eadc4b99532d6912b3d3117f) )
	ROM_CONTINUE( 0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n030001b.638", 0x200001, 0x40000, CRC(b2a86447) SHA1(d7048c283853cbe52ef6733aed1f9a3bf22d70ec) )
	ROM_CONTINUE( 0x200003, 0x40000 )
ROM_END

ROM_START( 3countbd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n043001a.038", 0x000001, 0x040000, CRC(10dbe66a) SHA1(b3a50100f0d41f2cc9ad92687aaba52340b6d67d) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n043001a.03c", 0x080001, 0x040000, CRC(6d5bfb61) SHA1(8ba73917d8c29a5400fcc3b58e0cbbd100dd3182) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "043.s1", CRC(c362d484) SHA1(a3c029292572842feabe9aa8c3372628fb63978d) ) // n043001a.378

	NEO_BIOS_AUDIO_128K( "n043001a.4f8", CRC(3377cda3) SHA1(5712cd0717585914120ebf307391e1e3171f5396) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n043001a.1f8", 0x000000, 0x080000, CRC(2abe6ab0) SHA1(9d717d52889c9af76fc6790a0e97c54eabd3b931) )
	ROM_LOAD( "n043001a.1fc", 0x080000, 0x080000, CRC(d3fa2743) SHA1(9f065d708cad0b98e7b7b4c4e96a2a4f8da76e7e) )
	ROM_LOAD( "n043001b.1f8", 0x100000, 0x080000, CRC(f591b0a1) SHA1(68bcac77543eca84232f1628a32828cc9c4081bb) )
	ROM_LOAD( "n043001b.1fc", 0x180000, 0x080000, CRC(01f3999e) SHA1(4f9ec67e52aabe6a0d2e2210824349e25dd9269d) )
	ROM_LOAD( "n043001c.1f8", 0x200000, 0x080000, CRC(f76aa00e) SHA1(6dbde96b083c34ee77ce512edaa2284061172df5) )
	ROM_LOAD( "n043001c.1fc", 0x280000, 0x080000, CRC(851ce851) SHA1(58d2c904224c50cd9c2b5c5710bb8539b94af604) )
	ROM_LOAD( "n043001d.1f8", 0x300000, 0x080000, CRC(9e2c8366) SHA1(89ababf09a578750fed508475bcfb562bc9116a6) )
	ROM_LOAD( "n043001d.1fc", 0x380000, 0x080000, CRC(b1a0ccb0) SHA1(ccadb887818477906071edf85408bfe5d74e919a) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n043001a.538", 0x000000, 0x40000, CRC(be0d2fe0) SHA1(6c59673b5b7c362596374f45b0fc739e5608d4d2) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n043001a.638", 0x000001, 0x40000, CRC(f56dafa5) SHA1(2b9b1a1ed0a00b1bf3c7e490ac0995836c263dba) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n043001a.53c", 0x100000, 0x40000, CRC(fdb4df65) SHA1(ac59c3aaa5f794a21942015a41c3daa6a94d564c) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n043001a.63c", 0x100001, 0x40000, CRC(f2f68b2a) SHA1(3cd321ee4699be888a4c380a3202a2c4932cc240) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n043001b.538", 0x200000, 0x40000, CRC(714c2c01) SHA1(2a5e612807a6000824cc0ae848774c5e5bdcb572) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n043001b.638", 0x200001, 0x40000, CRC(b15a7f25) SHA1(c5488becc87fe5be5a402f5358cd4c6c7e7e0474) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n043001b.53c", 0x300000, 0x40000, CRC(c57ce8b0) SHA1(241d98fdf2cfb33321387c396b98011744b472c4) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n043001b.63c", 0x300001, 0x40000, CRC(25f00cd3) SHA1(55f51d80efab87ea1ea2bdcb92b97eeab3097b93) )
	ROM_CONTINUE(             0x300003, 0x40000 )
	ROM_LOAD32_BYTE( "n043001c.538", 0x400000, 0x40000, CRC(2e7e59df) SHA1(a0a5afd8259eff487d80a43405b6368bfb8a7862) )
	ROM_CONTINUE(             0x400002, 0x40000 )
	ROM_LOAD32_BYTE( "n043001c.638", 0x400001, 0x40000, CRC(341438e4) SHA1(233703b8ecd61ba173bf6636677f4f8e8972e8f4) )
	ROM_CONTINUE(             0x400003, 0x40000 )
	ROM_LOAD32_BYTE( "n043001c.53c", 0x500000, 0x40000, CRC(a93185ce) SHA1(8b979391f3dba5ee4869bbe8417cbe04f781a3bd) )
	ROM_CONTINUE(             0x500002, 0x40000 )
	ROM_LOAD32_BYTE( "n043001c.63c", 0x500001, 0x40000, CRC(fb8adce8) SHA1(e7a269db6b1f03cab4535b41caaae27e7d98dd4b) )
	ROM_CONTINUE(             0x500003, 0x40000 )
	ROM_LOAD32_BYTE( "n043001d.538", 0x600000, 0x40000, CRC(410938c5) SHA1(230e4c466a38fee7432be7352b99b9331c227532) )
	ROM_CONTINUE(             0x600002, 0x40000 )
	ROM_LOAD32_BYTE( "n043001d.638", 0x600001, 0x40000, CRC(74d995c5) SHA1(fd269844104c598cda96cc8823c0acdbddeaa9ba) )
	ROM_CONTINUE(             0x600003, 0x40000 )
	ROM_LOAD32_BYTE( "n043001d.53c", 0x700000, 0x40000, CRC(50d66909) SHA1(4458e59e7fdddd8c2383d4f0edd025a08eaa1222) )
	ROM_CONTINUE(             0x700002, 0x40000 )
	ROM_LOAD32_BYTE( "n043001d.63c", 0x700001, 0x40000, CRC(521b6df1) SHA1(aa8a072f1abe4a0bb62a917dd2662dfdbaef0faa) )
	ROM_CONTINUE(             0x700003, 0x40000 )
ROM_END

ROM_START( alpham2d )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n007001a.038", 0x000001, 0x040000, CRC(4400b34c) SHA1(99cd25c0383e8ffba2d83f2d9c5c6452fe69c362) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n007001a.03c", 0x080001, 0x040000, CRC(b0366875) SHA1(591a02a5cef01e190eaed922894920571f4f6bdb) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "007.s1", CRC(85ec9acf) SHA1(39a11974438ad36a2cc84307151b31474c3c5518) ) // n007001a.378

	NEO_BIOS_AUDIO_64K( "n007001a.478", CRC(0449acf5) SHA1(1275ba5dad1c5123f727dd4193b8ee2cb910760d) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n007001a.178", 0x000000, 0x080000, CRC(7ec0e76d) SHA1(5f84f0a236b5cb7dd02b588806bc7f6e35eb515d) )
	ROM_LOAD( "n007001a.17c", 0x080000, 0x080000, CRC(7a796ead) SHA1(0a5b2683acc680edef3d3aa44681e0d648dce53f) )
	ROM_LOAD( "n007001b.178", 0x100000, 0x080000, CRC(70bc86a5) SHA1(00ef9faf9b094bca2fd654b26eb03e6e40bd6f80) )
	ROM_LOAD( "n007001b.17c", 0x180000, 0x080000, CRC(29963a92) SHA1(fb2ff29e48cfee33c0f8c12f849b35bd5be27ec9) )

	ROM_REGION( 0x400000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "n007001a.278", 0x000000, 0x080000, CRC(45f5e914) SHA1(d89d9917a0aaf1c662d5633a52a29bd670577830) )
	ROM_LOAD( "n007001a.27c", 0x080000, 0x080000, CRC(07524063) SHA1(559c3f1b33cfb112dd8d70726be07cac1cafd72f) )
	ROM_LOAD( "n007001b.278", 0x100000, 0x080000, CRC(c3178623) SHA1(687e63943a22cfff9778cb41ef6c9b9ac6f43334) )
	ROM_LOAD( "n007001b.27c", 0x180000, 0x080000, CRC(65bca6b7) SHA1(8c96d98e86799f1a47b5a66d439e01d7935c213c) )
	ROM_LOAD( "n007001c.278", 0x200000, 0x080000, CRC(27cd2250) SHA1(ab5af5762f48f670b2d0a31fdd38539956681035) )
	ROM_LOAD( "n007001c.27c", 0x280000, 0x080000, CRC(43025293) SHA1(c8b612f4bead98d6e06dcf6cb8254fc8487e2c06) )
	ROM_LOAD( "n007001d.278", 0x300000, 0x080000, CRC(ae0a679a) SHA1(7fd81af67238eae3dba64502eeff41933de795e8) )
	ROM_LOAD( "n007001d.27c", 0x380000, 0x080000, CRC(6a2e400d) SHA1(656b026767596a6395f3e30f97140884cb0da5a0) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n007001a.538", 0x000000, 0x40000, CRC(c516b09e) SHA1(910b6197fef78138da2c5b18507d12d841a518e5) )
	ROM_CONTINUE( 0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n007001a.638", 0x000001, 0x40000, CRC(6b674581) SHA1(3cbf29302c2677abe79ae10ef95097c6d62ca88c) )
	ROM_CONTINUE( 0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n007001a.53c", 0x100000, 0x40000, CRC(d9a0ff6c) SHA1(f2577736d516471a6757a8134916fbf7316a9809) )
	ROM_CONTINUE( 0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n007001a.63c", 0x100001, 0x40000, CRC(4ff21008) SHA1(496a27d902342dbb3685ad8354981e76dc839f47) )
	ROM_CONTINUE( 0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n007001b.538", 0x200000, 0x40000, CRC(3a7fe4fd) SHA1(ad4d93ed7d472579b6ba5fd4809a96762f0c0c2e) )
	ROM_CONTINUE( 0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n007001b.638", 0x200001, 0x40000, CRC(d0e8eef3) SHA1(560594bf1ec6ca32b38d0fe73b4cb5b5ecb56d56) )
	ROM_CONTINUE( 0x200003, 0x40000 )
ROM_END

ROM_START( androdund )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n049001a.038", 0x000001, 0x040000, CRC(4639b419) SHA1(617765aea2cb26ae52b25b2f7a541caf14effac9) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n049001a.03c", 0x080001, 0x040000, CRC(11beb098) SHA1(8c8fafba019e94fcf56643fbeeae161840e4263d) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "049.s1", CRC(6349de5d) SHA1(bcc44b9576d7bedd9a39294530bb66f707690c72) ) // n049001a.378

	NEO_BIOS_AUDIO_128K( "n049001a.4f8", CRC(1a009f8c) SHA1(7782dfe48e143417f34fba5353e6deb63efeaa8a) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n049001a.1f8", 0x000000, 0x080000, CRC(577c85b3) SHA1(2c3072401fe73497dca0e9009ae2ba4053fe936d) )
	ROM_LOAD( "n049001a.1fc", 0x080000, 0x080000, CRC(e14551c4) SHA1(763a9912b9df55defb190af3f29ae034f6dd78d6) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n049001a.538", 0x000000, 0x40000, CRC(ca08e432) SHA1(4202685ea0eaa29772d3d451ed9240202e4626a4) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n049001a.638", 0x000001, 0x40000, CRC(7a0deb9e) SHA1(50953e69b8462d4b981c91c74c307bcb539b0ceb) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n049001a.53c", 0x100000, 0x40000, CRC(fcbcb305) SHA1(42fe48127593e7714f7675506de8d0ae08a70164) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n049001a.63c", 0x100001, 0x40000, CRC(b1c640f5) SHA1(6e667f4c197243f6389c952229efa90bd3a66b50) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n049001b.538", 0x200000, 0x40000, CRC(806ab937) SHA1(78867c587420b938be1a76f0b87dea4d21fbe1b0) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n049001b.638", 0x200001, 0x40000, CRC(33bee10f) SHA1(3e01859e6455c9e941f9afcf31d62a4de4806eca) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n049001b.53c", 0x300000, 0x40000, CRC(e7e1a2be) SHA1(91a68ed46975811f1abaf4d1d912f514328c7189) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n049001b.63c", 0x300001, 0x40000, CRC(70f0d263) SHA1(fccb548d4b1754c475ceb46f3e49e4e9607e6651) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( aofd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n044001a.038", 0x000001, 0x040000, CRC(95102254) SHA1(b4b9a0b35c2fab78fa9fd590f0f22da4e4153ac2) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "044.s1", CRC(89903f39) SHA1(a04a0c244a5d5c7a595fcf649107969635a6a8b6) ) // n044001a.378

	NEO_BIOS_AUDIO_128K( "044001a.4f8", CRC(981345f8) SHA1(5eb6a5a3f633d74a48555808e2562a0ba16d8675) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n044001a.1f8", 0x000000, 0x080000, CRC(a4d8747f) SHA1(d9963375edd22d194c17e50fa398b12bbe2a777f) )
	ROM_LOAD( "n044001a.1fc", 0x080000, 0x080000, CRC(55219d13) SHA1(97fa9b1461e9dbf6c1580e1f814df68c79b61016) )
	ROM_LOAD( "n044001b.1f8", 0x100000, 0x080000, CRC(6eae81fa) SHA1(37d5ea320913b77a3fcdd2e1db1447a9cd77d094) )
	ROM_LOAD( "n044001b.1fc", 0x180000, 0x080000, CRC(f91676e9) SHA1(5c3e8f4230a2b18af8cea4ee32c23408de575c0c) )
	ROM_LOAD( "n044001c.1f8", 0x200000, 0x080000, CRC(d0c8bcd2) SHA1(126d56214a51027a340153b0dc29268ef7d36256) )
	ROM_LOAD( "n044001c.1fc", 0x280000, 0x080000, CRC(167db9b2) SHA1(960c32b4163d7cadba26d4f64627bce08d4da65b) )
	ROM_LOAD( "n044001d.1f8", 0x300000, 0x080000, CRC(f03969fe) SHA1(5e30c9162bdb8236ccd7ec1e99107da656764fe8) )
	ROM_LOAD( "n044001d.1fc", 0x380000, 0x080000, CRC(a823a19a) SHA1(5662874b80b9df94c60f7100eefa229e95bd91d5) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n044001a.538", 0x000000, 0x40000, CRC(a2e4a168) SHA1(7a0090f85235ae2a50498ab3538fef2f8afa7242) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n044001a.638", 0x000001, 0x40000, CRC(ca12c80f) SHA1(c7e4b241719f04860abf5fbb6e1712a802e43dee) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n044001a.53c", 0x100000, 0x40000, CRC(da389ef7) SHA1(b3c6ec60c5bdb63943a23eed028d9c952b11fc24) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n044001a.63c", 0x100001, 0x40000, CRC(d59746b0) SHA1(4d66e8384be5ce2917cf7db099000c229fb2d767) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n044001b.538", 0x200000, 0x40000, CRC(2a0c385b) SHA1(7d8e20a81e15f6806af43edb7d35e65052c32cbd) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n044001b.638", 0x200001, 0x40000, CRC(8b73b3da) SHA1(046e4a02f2c305ded91b22e09bf421d4f3d84f0c) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n044001b.53c", 0x300000, 0x40000, CRC(4a4317bf) SHA1(805405d440e4dba2cdc8b89629b0ab9616b5d357) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n044001b.63c", 0x300001, 0x40000, CRC(9fc3f8ea) SHA1(5a0520980b69724cdd011841844545dafc259ff9) )
	ROM_CONTINUE(             0x300003, 0x40000 )
	ROM_LOAD32_BYTE( "n044001c.538", 0x400000, 0x40000, CRC(471d9e57) SHA1(54200bd380f8f6b19f64768033b97a96aa8a8640) )
	ROM_CONTINUE(             0x400002, 0x40000 )
	ROM_LOAD32_BYTE( "n044001c.638", 0x400001, 0x40000, CRC(cbf8a72e) SHA1(182b7f98f414533f1ea294f3ea8b25e98857e0cd) )
	ROM_CONTINUE(             0x400003, 0x40000 )
	ROM_LOAD32_BYTE( "n044001c.53c", 0x500000, 0x40000, CRC(23fe5675) SHA1(a03b0739c3b98150a610aada2c945165a58a56d7) )
	ROM_CONTINUE(             0x500002, 0x40000 )
	ROM_LOAD32_BYTE( "n044001c.63c", 0x500001, 0x40000, CRC(5ec93c96) SHA1(6a5869fe778774ef1a641068e65e33a1ea2bd15b) )
	ROM_CONTINUE(             0x500003, 0x40000 )
	ROM_LOAD32_BYTE( "n044001d.538", 0x600000, 0x40000, CRC(204e7b29) SHA1(944865fb04e554f217dbaa2259834e1c413afe50) )
	ROM_CONTINUE(             0x600002, 0x40000 )
	ROM_LOAD32_BYTE( "n044001d.638", 0x600001, 0x40000, CRC(47763b6d) SHA1(b7e6cb423e3c49bca60ff190ff105001e3579701) )
	ROM_CONTINUE(             0x600003, 0x40000 )
	ROM_LOAD32_BYTE( "n044001d.53c", 0x700000, 0x40000, CRC(7f6d5144) SHA1(8f39666259d8fe187ae6da532372b6c606737246) )
	ROM_CONTINUE(             0x700002, 0x40000 )
	ROM_LOAD32_BYTE( "n044001d.63c", 0x700001, 0x40000, CRC(4408f4eb) SHA1(dc045494f6865def21448caab13b2ad6ee520f37) )
	ROM_CONTINUE(             0x700003, 0x40000 )
ROM_END

ROM_START( bakatonod )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n036001a.038", 0x000001, 0x040000, CRC(083ca651) SHA1(8d947e5de3db3a8cf4195de3b149d4a7994704c1) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n036001a.03c", 0x080001, 0x040000, CRC(b3bc26ae) SHA1(c0a741198627a78f7a100ee406d994b50e63012f) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "036.s1", CRC(f3ef4485) SHA1(c30bfceed7e669e4c97b0b3ec2e9f4271e5b6662) ) // n036001a.378

	NEO_BIOS_AUDIO_64K( "n036001a.4f8", CRC(a5e05789) SHA1(63985ed5b3491d0f7b0e2f59785f590bfe122330) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n036001a.1f8", 0x000000, 0x080000, CRC(d3edbde6) SHA1(c8628a47e275137e340f2005775272a58a594d81) )
	ROM_LOAD( "n036001a.1fc", 0x080000, 0x080000, CRC(cc487705) SHA1(3bc30dc485917a01756ed33b3507133549e3c1f8) )
	ROM_LOAD( "n036001b.1f8", 0x100000, 0x080000, CRC(e28cf9b3) SHA1(6c0bc9f5f496edb89dd8dc7acbec3c361bcef0f3) )
	ROM_LOAD( "n036001b.1fc", 0x180000, 0x080000, CRC(96c3ece9) SHA1(357ed280157897e26eeecce080da9757f1c03b35) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n036001a.538", 0x000000, 0x40000, CRC(acb82025) SHA1(6bc9b61fdbcb04a1acc0c692a066791bf412d814) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n036001a.638", 0x000001, 0x40000, CRC(647ba28f) SHA1(761884eabcf3be81614ee1d2cf6a86515b3fb628) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n036001a.53c", 0x100000, 0x40000, CRC(c6954f8e) SHA1(b7f09c1d5800ea82abee8f0b00d0c9395882fe00) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n036001a.63c", 0x100001, 0x40000, CRC(dffefa4f) SHA1(bdc9bd4d09808a51d8fb27c337f0382d5ddd58df) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n036001b.538", 0x200000, 0x40000, CRC(eb751be8) SHA1(50db6c2055160396f7a6e4ada9fa52a458046ad2) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n036001b.638", 0x200001, 0x40000, CRC(6135247a) SHA1(0c23a0894484689124873cfc37a4e0a05e226f2d) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n036001b.53c", 0x300000, 0x40000, CRC(1d39bad6) SHA1(8f275cc73844760725b476264db0543a1327fb21) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n036001b.63c", 0x300001, 0x40000, CRC(0d40c953) SHA1(f77d84cb6b9bfe580f69a319d4f4fd98389e6d49) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( bstarsd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n002001a.038", 0x000001, 0x040000, CRC(68ce5b06) SHA1(cab050a4efcf346463609910b367f7f6c1c0158b) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "002.s1", CRC(1a7fd0c6) SHA1(3fc701b7afddab369ddf9dedfbc5e1aaf80b8af3) ) // n002001a.378

	NEO_BIOS_AUDIO_64K( "n002001a.478", CRC(79a8f4c2) SHA1(08ca2b72fd9b0ed068dc918ecda51d13203a3481) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "002.v11", 0x000000, 0x080000, CRC(b7b925bd) SHA1(644c92fa90e74998e73714f74b1e0680ee372a07) ) // n002001a.178
	ROM_LOAD( "002.v12", 0x080000, 0x080000, CRC(329f26fc) SHA1(2c8009edc88c6b26f7be5beb2b8d260aac394ee1) ) // n002001a.17c
	ROM_LOAD( "002.v13", 0x100000, 0x080000, CRC(0c39f3c8) SHA1(db8f8670639601215707d918d4fb93221460446a) ) // n002001b.178
	ROM_LOAD( "002.v14", 0x180000, 0x080000, CRC(c7e11c38) SHA1(5abf2a7877e0162c758a4dcf09f183930fa7ef24) ) // n002001b.17c

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "002.v21", 0x000000, 0x080000, CRC(04a733d1) SHA1(84159368c0f6de2c3b8121227201cd3422455cf6) ) // n002001a.278

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n002001a.538", 0x000000, 0x40000, CRC(c55a7229) SHA1(23a28f8ba6c1339dde4f674bbca6e6cffafabcc7) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n002001a.638", 0x000001, 0x40000, CRC(cd3eeb2d) SHA1(3997788c063cea48a901ff6033574d2c8a9e0516) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n002001a.53c", 0x100000, 0x40000, CRC(a0074bd9) SHA1(f1b1ba3630befd595d141bfc580b1bbe01bee324) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n002001a.63c", 0x100001, 0x40000, CRC(d651fecf) SHA1(3e7bbda2ecd487e568f8e8eb9b141941d6a761b9) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n002001b.538", 0x200000, 0x40000, CRC(d57767e6) SHA1(cf18dd9cf6f9da09af7be5e0c9f7f12eaa61c129) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n002001b.638", 0x200001, 0x40000, CRC(5d0a8692) SHA1(1a0f767d11f73fd41aa2f1840fc300fb23b8d262) )
	ROM_CONTINUE(             0x200003, 0x40000 )
ROM_END

ROM_START( burningfd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n018001a.038", 0x000001, 0x040000, CRC(188c5e11) SHA1(0f82b0e6fd93f43579f7cb2871e6840c738696af) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "018.s1", CRC(6799ea0d) SHA1(ec75ef9dfdcb0b123574fc6d81ebaaadfba32fb5) ) // n018001a.378

	NEO_BIOS_AUDIO_128K( "n018001a.4f8", CRC(58d10c2b) SHA1(5f1f01af284f6520d09ae1c5f6f176153a013f90) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n018001a.1f8", 0x000000, 0x080000, CRC(b55b9670) SHA1(b0ff38b2dca1361ad155e90be3674dbea1c0a53c) )
	ROM_LOAD( "n018001a.1fc", 0x080000, 0x080000, CRC(a0bcf260) SHA1(5d1f2613cf4a292557f37e6f44a90b20d11ed8cd) )
	ROM_LOAD( "n018001b.1f8", 0x100000, 0x080000, CRC(270f4707) SHA1(29e763acc9fd4b94d8b5d0ad917e20d8a66bbe49) )
	ROM_LOAD( "n018001b.1fc", 0x180000, 0x080000, CRC(924e3d69) SHA1(927091f9a098f00eb303f5567f4ee926bcb170e3) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n018001a.538", 0x000000, 0x40000, CRC(4ddc137b) SHA1(02add8810ed4df43feda93dd61c308bf1752e1dc) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n018001a.638", 0x000001, 0x40000, CRC(7d7d87dc) SHA1(efd24a8b6112c38e7d4bca46dfae227a80883be7) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n018001a.53c", 0x100000, 0x40000, CRC(896d8545) SHA1(415e5982275d43666d5b33c1a599e5fe073e0ab1) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n018001a.63c", 0x100001, 0x40000, CRC(39fe5307) SHA1(6be6306324ff63715e5ddb33c9565a538472e014) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n018001b.538", 0x200000, 0x40000, CRC(2b2cb196) SHA1(2826b07d72adb0c83cd84dbfc3d9a6eae93bd3b7) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n018001b.638", 0x200001, 0x40000, CRC(03aa8a36) SHA1(e68f12e869b0c947a0b2a0dd591edbe995e95775) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n018001b.53c", 0x300000, 0x40000, CRC(0f49caa9) SHA1(5a86c3b2a29b1bee10a2649c0106e0a4948f5ecf) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n018001b.63c", 0x300001, 0x40000, CRC(f759626e) SHA1(29e123c8d40334a53fceae33308d92a0dd3ac80d) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( crswordd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n037001a.038", 0x000001, 0x040000, CRC(42c78fe1) SHA1(4e680092f87baa8ce1ec375bedfd393b553bad11) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "037.s1", CRC(74651f27) SHA1(bff7ff2429d2be82c1647abac2ee45b339b3b310) ) // n037001a.378

	NEO_BIOS_AUDIO_64K( "n037001a.4f8", CRC(66633e5e) SHA1(24611f084643c36069c2e48dac86413a18f9663b) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n037001a.1f8", 0x000000, 0x080000, CRC(525df5c8) SHA1(de8802aa515de5b552df87ba4eb3aa27c12105c9) )
	ROM_LOAD( "n037001a.1fc", 0x080000, 0x080000, CRC(a11ecaf4) SHA1(214ef018628a6acf2464fdd98afadb02e4f609eb) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n037001a.538", 0x000000, 0x40000, CRC(4b373de7) SHA1(4a3cd07cb2b029c28bdea9918d839fa308324921) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n037001a.638", 0x000001, 0x40000, CRC(e05f5f33) SHA1(af11079524edf2db79efd8ab25b33689a0d1080b) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n037001a.53c", 0x100000, 0x40000, CRC(cddf6d69) SHA1(04f002d6648af24ca5c887bcd8b73d3a59becd2c) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n037001a.63c", 0x100001, 0x40000, CRC(91ab11a4) SHA1(b063bf2ab89382014159fbe5372a0893782fa510) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n037001b.538", 0x200000, 0x40000, CRC(61d25cb3) SHA1(fde39e2a3cc920772981afb6843f69c6b7b55f2d) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n037001b.638", 0x200001, 0x40000, CRC(01357559) SHA1(898db3366147e4c8920de9efb52b9d852dded010) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n037001b.53c", 0x300000, 0x40000, CRC(00bc3d84) SHA1(9eab28250902748563bc6a0dc4bd0ea66126a767) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n037001b.63c", 0x300001, 0x40000, CRC(28c6d19a) SHA1(96aa762ec26a6b954ec7414b74febf6b88e272aa) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( cyberlipd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n010001a.038", 0x000001, 0x040000, CRC(4012e465) SHA1(81caac2b559183f5a87980b6f1ca7e42d5338962) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n010001a.03c", 0x080001, 0x040000, CRC(ee899b19) SHA1(3d0369ad2496e8622fb5a11f751056a2c5fad7bf) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "010.s1", CRC(79a35264) SHA1(c2819a82adbe1f5e489496e0e03477863a5b7665) ) // n010001a.378

	NEO_BIOS_AUDIO_128K( "010.m1", CRC(8be3a078) SHA1(054ec6a061fcc88df1ecbb0a01611a31f37a7709) ) // n010001a.478

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "010.v11", 0x000000, 0x080000, CRC(90224d22) SHA1(5443ee6f90d80d43194cb4b4f0e08851a59e7784) ) // n010001a.178
	ROM_LOAD( "010.v12", 0x080000, 0x080000, CRC(a0cf1834) SHA1(8df57a7941bdae7e446a6056039adb012cdde246) ) // n010001a.17c
	ROM_LOAD( "010.v13", 0x100000, 0x080000, CRC(ae38bc84) SHA1(c0937b4f89b8b26c8a0e747b234f44ad6a3bf2ba) ) // n010001b.178
	ROM_LOAD( "010.v14", 0x180000, 0x080000, CRC(70899bd2) SHA1(8cf01144f0bcf59f09777175ae6b71846b09f3a1) ) // n010001b.17c

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "010.v21", 0x000000, 0x080000, CRC(586f4cb2) SHA1(588460031d84c308e3353ecf714db9986425c21c) ) // n010001a.278

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n010001a.538", 0x000000, 0x40000, CRC(0239fc08) SHA1(27c2a68103ca6898780d72ded57f4447cf5f7f80) )
	ROM_CONTINUE( 0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n010001a.638", 0x000001, 0x40000, CRC(e102a1bd) SHA1(89ffd05845b452423b4cd69c4420eafa0c168507) )
	ROM_CONTINUE( 0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n010001a.53c", 0x100000, 0x40000, CRC(23f03b97) SHA1(f5a2b3c0cf039a84cf78223f089f9fa3a7d9f01a) )
	ROM_CONTINUE( 0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n010001a.63c", 0x100001, 0x40000, CRC(520571d2) SHA1(4be129b679d3962a95ce32f462c58aa08c43b1cd) )
	ROM_CONTINUE( 0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n010001b.538", 0x200000, 0x40000, CRC(065061ed) SHA1(5c1e48e31cc6b5bbc50085abc8102ab436885b23) )
	ROM_CONTINUE( 0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n010001b.638", 0x200001, 0x40000, CRC(2e31e2d2) SHA1(29c88296d10b6b716ab753d2692267e0619d6193) )
	ROM_CONTINUE( 0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n010001b.53c", 0x300000, 0x40000, CRC(e485e72d) SHA1(1fb160f403b6ec1ff28408d141dfe31245dbfb58) )
	ROM_CONTINUE( 0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n010001b.63c", 0x300001, 0x40000, CRC(9e2af4db) SHA1(0089d1a66fa40a25ea78c6da24b4872b4fd12782) )
	ROM_CONTINUE( 0x300003, 0x40000 )
ROM_END

ROM_START( eightmand )
	ROM_REGION(0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n025001a.038", 0x000001, 0x040000, CRC(e23e2631) SHA1(ddc9efe6e386aa89aca052f004492caf39a84d68) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "025.s1", CRC(a402202b) SHA1(75c44e1af459af155f5b892fd18706268dd5e602) ) // n025001a.378

	NEO_BIOS_AUDIO_128K( "n025001a.4f8", CRC(68b6e0ef) SHA1(8a6c221460454d15c3d72dd66a2318be0a3d5072) )

	ROM_REGION(0x200000, "ymsnd:adpcma", 0)
	ROM_LOAD( "n025001a.1f8", 0x000000, 0x080000, CRC(0a2299b4) SHA1(96087ec57bca13a7394566c87310cd5a05eae62a) )
	ROM_LOAD( "n025001a.1fc", 0x080000, 0x080000, CRC(b695e254) SHA1(ca752c4834dcdd8c2829e336abf135e584ade603) )
	ROM_LOAD( "n025001b.1f8", 0x100000, 0x080000, CRC(6c3c3fec) SHA1(69f7cb9a4c39b651898383ec9ee6891565e93baf) )
	ROM_LOAD( "n025001b.1fc", 0x180000, 0x080000, CRC(375764df) SHA1(7288befc006bd10030911efecfbf78146ed5f781) )

	ROM_REGION(0x300000, "sprites", 0)
	ROM_LOAD32_BYTE( "n025001a.538", 0x000000, 0x40000, CRC(c916c9bf) SHA1(ac56aa28b163d21af80f355011112c1921a6797b) )
	ROM_CONTINUE( 0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n025001a.638", 0x000001, 0x40000, CRC(7114bce3) SHA1(a74abb92ec513250abea7487fd49ec2282a6531f) )
	ROM_CONTINUE( 0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n025001a.53c", 0x100000, 0x40000, CRC(4b057b13) SHA1(1d06edc938d8c618847853ae58de9a6e8dd6521f) )
	ROM_CONTINUE( 0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n025001a.63c", 0x100001, 0x40000, CRC(51da9a34) SHA1(850275621db0372839db334161c167c0df0915ac) )
	ROM_CONTINUE( 0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n025001b.538", 0x200000, 0x40000, CRC(12d53af0) SHA1(69bc5c1f6aa4386e851d2d0db04b5a9246257a90) )
	ROM_CONTINUE( 0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n025001b.638", 0x200001, 0x40000, CRC(43cf58f9) SHA1(72b4f27b66d45155aa98d65457c4fdd3b09d08e9) )
	ROM_CONTINUE( 0x200003, 0x40000 )
ROM_END

ROM_START( fatfury1d )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n033001a.038", 0x000001, 0x040000, CRC(47e51379) SHA1(bb1558765f55e0b8e3e0c1c5c79db8cec8b51085) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n033001a.03c", 0x080001, 0x040000, CRC(19d36805) SHA1(6b2d5326a08b06a9152d80a8de054ad9f159a453) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "033.s1", CRC(3c3bdf8c) SHA1(2f3e5feed6c27850b2a0f6fae0b97041690e944c) ) // n033001a.378

	NEO_BIOS_AUDIO_128K( "n033001a.4f8", CRC(a8603979) SHA1(512f2280a43892d4ca003ac63945ce86c5211b97) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n033001a.1f8", 0x000000, 0x080000, CRC(86fabf00) SHA1(df087f58c689128f7696b91e2fcb600ccac017af) )
	ROM_LOAD( "n033001a.1fc", 0x080000, 0x080000, CRC(ead1467b) SHA1(6f4381d7a0625f5d02739a9813ff593c2dc99dde) )
	ROM_LOAD( "n033001b.1f8", 0x100000, 0x080000, CRC(fc3bd6f7) SHA1(8d3094ecd8d5cfe3f58be9ac6d76a2bb65eb1d00) )
	ROM_LOAD( "n033001b.1fc", 0x180000, 0x080000, CRC(d312f6c0) SHA1(3fae32af628ed8d0176a7f6668ff4f2d898c9f7a) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n033001a.538", 0x000000, 0x40000, CRC(9aaa6d73) SHA1(345ed4b75a6459cd0b8fc8f71d58f4951296177f) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n033001a.638", 0x000001, 0x40000, CRC(9cae3703) SHA1(1144ccf448ea7c00ca425fe54f2ce84b8fdb3c78) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n033001a.53c", 0x100000, 0x40000, CRC(a986f4a9) SHA1(a45cc6b5902333d6614b7a2018ebd5ada7c5f075) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n033001a.63c", 0x100001, 0x40000, CRC(308b619f) SHA1(384efb66633a888d7c48d2ab0e918d823178b382) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n033001b.538", 0x200000, 0x40000, CRC(7aefe57d) SHA1(ab97881ff620ab7130d9ce1527c23bcfc0b21a5e) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n033001b.638", 0x200001, 0x40000, CRC(b39a0cde) SHA1(e5829525bc2ffe489ebb0ec4ab0094417f141027) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n033001b.53c", 0x300000, 0x40000, CRC(e3057c96) SHA1(b6a2e55633db0aad7f1ca4e8b42c2a327f772add) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n033001b.63c", 0x300001, 0x40000, CRC(737bc030) SHA1(03ceeabb84dac6f27c6f6ba2b7097b756f411270) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( fbfrenzyd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n034001a.038", 0x000001, 0x040000, CRC(c9fc879c) SHA1(24b8be60a434c3f4944f060607756a830f9365fd) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "034.s1", CRC(8472ed44) CRC(8472ed44) SHA1(42e1a9671dddd090d2a634cff986f6c73ba08b70) ) // n034001a.378

	NEO_BIOS_AUDIO_128K( "n034001a.4f8", CRC(079a203c) SHA1(b0e818400c46331ec42f9bb8fa3feacb6c69006a) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n034001a.1f8", 0x000000, 0x080000, CRC(d295da77) SHA1(3015a07236714af87928a9bff1a9505a9ee9b419) )
	ROM_LOAD( "n034001a.1fc", 0x080000, 0x080000, CRC(249b7f52) SHA1(4aa1e7f73c37ecdd09098a3943c8ff3e919788be) )
	ROM_LOAD( "n034001b.1f8", 0x100000, 0x080000, CRC(e438fb9d) SHA1(0403345549e618a3161c74a37ecae894b6e8d1e0) )
	ROM_LOAD( "n034001b.1fc", 0x180000, 0x080000, CRC(4f9bc109) SHA1(05f47d9b7de8a4f51fce43c14a2f5e7d616058a3) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n034001a.538", 0x000000, 0x40000, CRC(cd377680) SHA1(0ba533dc644b4111361e6f0ef31b2a92bc974efb) )
	ROM_CONTINUE( 0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n034001a.638", 0x000001, 0x40000, CRC(8b76358f) SHA1(ba908221daa9bfe7eaf03e370329fdb4a015da5f) )
	ROM_CONTINUE( 0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n034001a.53c", 0x100000, 0x40000, CRC(2f6d09c2) SHA1(5afffa37d5782c21e0d673ebfaf03f92fb5b91e4) )
	ROM_CONTINUE( 0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n034001a.63c", 0x100001, 0x40000, CRC(77e45dd2) SHA1(a4412ddfde175405c85eba2e56eec3d9878575d3) )
	ROM_CONTINUE( 0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n034001b.538", 0x200000, 0x40000, CRC(9abe41c8) SHA1(ab350c65258e5d229ab317d45580ae4cbbcd1478) )
	ROM_CONTINUE( 0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n034001b.638", 0x200001, 0x40000, CRC(336540a8) SHA1(7be473063680987560a188e59f477c8ff9b96b01) )
	ROM_CONTINUE( 0x200003, 0x40000 )
ROM_END

ROM_START( gpilotsd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n020001a.038", 0x000001, 0x040000, CRC(fc5837c0) SHA1(1eb46c21b17130238a1453c219e006ea150370ee) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n020001a.03c", 0x080001, 0x040000, CRC(47a641da) SHA1(d369ee64fd70d705355df71766b72c402a236e24) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "020.s1", CRC(a6d83d53) SHA1(9a8c092f89521cc0b27a385aa72e29cbaca926c5) ) // n020001a.378

	NEO_BIOS_AUDIO_64K( "n020001a.478", CRC(fc05fb8b) SHA1(bab6e6af4a60ffebff25951eca4177ece68875a4) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n020001a.178", 0x000000, 0x080000, CRC(8cc44140) SHA1(0a88d8962e057bf0cabd4819d4ba67e093c49b82) )
	ROM_LOAD( "n020001a.17c", 0x080000, 0x080000, CRC(415c61cd) SHA1(638e5fd9b02b4553df42f00188a7ac52a5a7bf84) )
	ROM_LOAD( "020.v12",  0x100000, 0x080000, CRC(4a9e6f03) SHA1(d3ac11f333b03d8a318921bdaefb14598e289a14) ) // n020001b.178

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "020.v21", 0x000000, 0x080000, CRC(7abf113d) SHA1(5b2a0e70f2eaf4638b44702dacd4cb17838fb1d5) ) // n020001a.278

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n020001a.538", 0x000000, 0x40000, CRC(92b8ee5f) SHA1(ff45ca2eed87863f3725d5dadd5f55ac39af033e) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n020001a.638", 0x000001, 0x40000, CRC(05733639) SHA1(a5f2639853ea53ec3ff91fe37fdb9e628a497883) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n020001a.53c", 0x100000, 0x40000, CRC(8c8e42e9) SHA1(9aa2abd11358933d72dc52ae8d0214e3b350c83b) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n020001a.63c", 0x100001, 0x40000, CRC(347fef2b) SHA1(8b4c7ab7d9cfda8e588d8e0f4796ce163b468407) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n020001b.538", 0x200000, 0x40000, CRC(4f12268b) SHA1(fa531734c9dbba62e35cb29eb40d80a219d87c54) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n020001b.638", 0x200001, 0x40000, CRC(2c586176) SHA1(0e28a27d59ae2ec6a9d1ff822244bfa4f960f338) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n020001b.53c", 0x300000, 0x40000, CRC(7c3c9c7e) SHA1(43a15669788384024ac173e1f89e53a2bdd630d2) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n020001b.63c", 0x300001, 0x40000, CRC(9b2eee8b) SHA1(420156256d5b628a62ea612edd526d293d2c7abc) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( joyjoyd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n021001a.038", 0x000001, 0x040000, CRC(ea512c9f) SHA1(094d8c06a1038dd38b74ced3d213a52b340062a6) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "021.s1", CRC(6956d778) SHA1(e3757776d60dc07d8e07c9ca61b223b14732f860) ) // n021001a.378

	NEO_BIOS_AUDIO_64K( "n021001a.478", CRC(058683ec) SHA1(2aff3dc18d078911ed3a09d48664faf5958b4ab5) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "021.v11", 0x000000, 0x080000, CRC(66c1e5c4) SHA1(7e85420021d4c39c36ed75a1cec567c5610ffce0) ) // n021001a.178

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "021.v21", 0x000000, 0x080000, CRC(8ed20a86) SHA1(d15cba5eac19ea56fdd4877541f1bb3eb755ebba) ) // n021001a.278

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n021001a.538", 0x000000, 0x40000, CRC(cb27be65) SHA1(bdadc0da89026af3ed0dc6a18f2449c0cb24ee0c) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n021001a.638", 0x000001, 0x40000, CRC(7e134979) SHA1(e33b30e39283963e8e806ccd12d9559de27c8bbe) )
	ROM_CONTINUE(             0x000003, 0x40000 )
ROM_END

ROM_START( kotmd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n016001a.038", 0x000001, 0x040000, CRC(d239c184) SHA1(feb139ce089385b6b1bc95970c4d7ae4fd8a7c7f) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n016001a.03c", 0x080001, 0x040000, CRC(7291a388) SHA1(16e22a8eef5391fa43d92d702f14a746dedf292b) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "016.s1", CRC(1a2eeeb3) SHA1(8d2b96d395020197bc59294b6b0c8d62b1d8d4dd) ) // n016001a.378

	NEO_BIOS_AUDIO_128K( "n016001a.4f8", CRC(40797389) SHA1(12ca00ba1d2d66d79bc64969661a52205cc98d66) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n016001a.1f8", 0x000000, 0x080000, CRC(c3df83ba) SHA1(2f015ccf99de241861e05e81ad47faf02aec3290) )
	ROM_LOAD( "n016001a.1fc", 0x080000, 0x080000, CRC(22aa6096) SHA1(c98fdc9fa589907cae1f7a2814fa32913d6c8648) )
	ROM_LOAD( "n016001b.1f8", 0x100000, 0x080000, CRC(df9a4854) SHA1(f9612d82ce476f8c973ce60a982ae8007bd051a1) )
	ROM_LOAD( "n016001b.1fc", 0x180000, 0x080000, CRC(71f53a38) SHA1(0fa03a2c719cc413ab163d166f93fcdc89646066) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n016001a.538", 0x000000, 0x40000, CRC(493db90e) SHA1(fb22e4f5437d9402c531779215cf675daa35401f) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n016001a.638", 0x000001, 0x40000, CRC(8bc1c3a0) SHA1(789f990b2b12bff7335a40a0ca6e64824dd6d4e2) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n016001a.53c", 0x100000, 0x40000, CRC(0d211945) SHA1(4edef3bdd73e402ab606ac27013a2b8c1467667c) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n016001a.63c", 0x100001, 0x40000, CRC(cc793bbf) SHA1(b88075e388d68601bb0e56f621a22abaf90ef39c) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n016001b.538", 0x200000, 0x40000, CRC(cabb7b58) SHA1(e7be9c459c17dddc3a812981e14fc2e0a3fb5ec3) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n016001b.638", 0x200001, 0x40000, CRC(fde45b59) SHA1(72ddca41b6cd595246eb8c8bb0c2e614c53e828c) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n016001b.53c", 0x300000, 0x40000, CRC(c7c20718) SHA1(52a2d7f4f8baede451959a351d2badf080b1e20e) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n016001b.63c", 0x300001, 0x40000, CRC(b89b4201) SHA1(74322700b9e8cf30b7d025be3909e93e1bfdaaf9) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( lbowlingd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n019001a.038", 0x000001, 0x040000, CRC(380e358d) SHA1(2f9683ca65abb2d046277a7642877f66a29d08f6) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "019.s1", CRC(5fcdc0ed) SHA1(86415077e7adc3ba6153eeb4fb0c62cf36e903fa) ) // n019001a.378

	NEO_BIOS_AUDIO_64K( "n019001a.478", CRC(535ec016) SHA1(301733768d2b962f58fc372e54f9d7bfd6615c21) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "019.v11", 0x000000, 0x080000, CRC(0fb74872) SHA1(38c555926c77576d63472bc075210c42e9ce13a3) ) // n019001a.178
	ROM_LOAD( "019.v12", 0x080000, 0x080000, CRC(029faa57) SHA1(7bbaa87e38929ab1e32df5f6a2ec0fd5001e7cdb) ) // n019001a.17c

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "019.v21", 0x000000, 0x080000, CRC(2efd5ada) SHA1(8ba70f5f665d566824333075227d9bce1253b8d8) ) // n019001a.278

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n019001a.538", 0x000000, 0x40000, CRC(17df7955) SHA1(992558200cbe7c0f9fc96cb6b1adb63ded28b833) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n019001a.638", 0x000001, 0x40000, CRC(84fd2c90) SHA1(b0ce2ba62d682f847f238eb5196340f466e6bcda) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n019001a.53c", 0x100000, 0x40000, CRC(67bf2d89) SHA1(282a29425eed00a85f88c332112bd9e0a95770cf) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n019001a.63c", 0x100001, 0x40000, CRC(cb4fbeb0) SHA1(a9a985ef66fe39111ccd37a4c1a26707d3bf3045) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n019001b.538", 0x200000, 0x40000, CRC(00d36f90) SHA1(8d47ea266dd2bf3ccbb9fb21ba860d9e9ec22db0) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n019001b.638", 0x200001, 0x40000, CRC(c2ddf431) SHA1(2ffbea4164f3099bdf8162c6ecc782d8badfab25) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n019001b.53c", 0x300000, 0x40000, CRC(4e971be9) SHA1(f137ad0eb9da8c4fffb5893ed694d97647f7e77b) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n019001b.63c", 0x300001, 0x40000, CRC(e67f8c81) SHA1(e0e8b24171a61dfe14649e7cff6f95d0a510cb55) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( lresortd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n024001a.038", 0x000001, 0x040000, CRC(5f0a5a4b) SHA1(69e33ed94f533528038fb157529b44dc940ab231) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "024.s1", CRC(5cef5cc6) SHA1(9ec305007bdb356e9f8f279beae5e2bcb3f2cf7b) ) // n024001a.378

	NEO_BIOS_AUDIO_128K( "n024001a.4f8", CRC(3d40a1c6) SHA1(d98b2b2893274db0cadc9c9718349086afadadc7) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n024001a.1f8", 0x000000, 0x080000, CRC(0722da38) SHA1(66a9b463d5277908b3a01c03de82b3de9118f2cb) )
	ROM_LOAD( "n024001a.1fc", 0x080000, 0x080000, CRC(670ce3ec) SHA1(9004aa85d4a9b0ecf9cf9357b073ed55a98fdb02) )
	ROM_LOAD( "n024001b.1f8", 0x100000, 0x080000, CRC(2e39462b) SHA1(b0a9b1a3377bf0369f3020192505c46ca52927d6) )
	ROM_LOAD( "n024001b.1fc", 0x180000, 0x080000, CRC(7944754f) SHA1(d42a46c5127c6c62041ebffb0007af8a24abd360) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n024001a.538", 0x000000, 0x40000, CRC(9f7995a9) SHA1(e3efdef66f5a6136ebe8fa9e3ff917323ab3fc5e) )
	ROM_CONTINUE( 0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n024001a.638", 0x000001, 0x40000, CRC(68c70bac) SHA1(7a6ddb1beb8cb6f6991d675affeb78226c18180e) )
	ROM_CONTINUE( 0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n024001a.53c", 0x100000, 0x40000, CRC(e122b155) SHA1(c9e759302fcf5aaf989463bf94157e45d76e68ea) )
	ROM_CONTINUE( 0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n024001a.63c", 0x100001, 0x40000, CRC(f18a9b02) SHA1(5cb9cf37de1b97ef680411beeff9ca262e77b067) )
	ROM_CONTINUE( 0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n024001b.538", 0x200000, 0x40000, CRC(e7138cb9) SHA1(d65c9e4f305cec30264355dd46a8ab413221dd82) )
	ROM_CONTINUE( 0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n024001b.638", 0x200001, 0x40000, CRC(08178e27) SHA1(e03137bf8e5bcd3c000113ec49da36f7100727e9) )
	ROM_CONTINUE( 0x200003, 0x40000 )
ROM_END

ROM_START( maglordd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n005001a.038", 0x000001, 0x040000, CRC(e51c3815) SHA1(19f36c8393191caf95a254ca52ce9e0012e6947a) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "005.s1", CRC(1c5369a2) SHA1(db0dba0a7dced6c9ca929c5abda491b05d84199c) ) // n005001a.378

	NEO_BIOS_AUDIO_64K( "n005001a.478", CRC(91ee1f73) SHA1(f060728543333a99216cc2879f7666a1f4235068) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "005.v11", 0x000000, 0x080000, CRC(cc0455fd) SHA1(a8ff4270e7705e263d25ff0b301f503bccea7e59) ) // n005001a.178

	ROM_REGION( 0x100000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "005.v21", 0x000000, 0x080000, CRC(f94ab5b7) SHA1(2c16985102e3585e08622d8c54ac5c60425b9ff8) ) // n005001a.278
	ROM_LOAD( "005.v22", 0x080000, 0x080000, CRC(232cfd04) SHA1(61b66a9decbbd1f500a8c186615e7fd077c6861e) ) // n005001a.27c

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n005001a.538", 0x000000, 0x40000, CRC(86aacd0d) SHA1(ee36e015908a7c087ace6cea0650822681066c94) )
	ROM_CONTINUE( 0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n005001a.638", 0x000001, 0x40000, CRC(b62658b5) SHA1(21a1d1f9ebe8c7a442c0b0a96f12af8047b8dbf3) )
	ROM_CONTINUE( 0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n005001a.53c", 0x100000, 0x40000, CRC(3997403e) SHA1(95e8375c897953055c952fd1fd3ff282fdc68928) )
	ROM_CONTINUE( 0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n005001a.63c", 0x100001, 0x40000, CRC(bd534fe2) SHA1(eebafc4a1daf650a6e7c3a64b2628e160e130b59) )
	ROM_CONTINUE( 0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n005001b.538", 0x200000, 0x40000, CRC(fbd1e9f1) SHA1(4faa14c164000e5581bb47788d2e8e1ee74ca0c6) )
	ROM_CONTINUE( 0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n005001b.638", 0x200001, 0x40000, CRC(a6461283) SHA1(a3eb28e584b0b91a0b5b372c932815cf4047d5bd) )
	ROM_CONTINUE( 0x200003, 0x40000 )
ROM_END

ROM_START( minasand )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n027001a.038", 0x000001, 0x040000, CRC(86805d5a) SHA1(9f9e300f4d4aef1bddb239580e8e5e3087957a50) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "027.s1", CRC(e5824baa) SHA1(8230ff7fe3cabeacecc762d90a084e893db84906) ) // n027001a.378

	NEO_BIOS_AUDIO_64K( "n027001a.478", CRC(19ef88ea) SHA1(8eca1a342d506e97dd116ce8ffe2242895b04c7a) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n027001a.178", 0x000000, 0x080000, CRC(79d65e8e) SHA1(8e5d8608e43564e5ce1d458a9e09b2c8100e3f4f) )
	ROM_LOAD( "n027001a.17c", 0x080000, 0x080000, CRC(0b3854d5) SHA1(27e951b47c0ab96f3c64704f913400020156895a) )

	ROM_REGION( 0x100000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "n027001a.278", 0x000000, 0x080000, CRC(0100e548) SHA1(627d16aba58602d28c865e93894f8d00d4815779) )
	ROM_LOAD( "n027001a.27c", 0x080000, 0x080000, CRC(0c31c5b0) SHA1(372168e5e6845eb5e2450a6f6daec26429b446c0) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n027001a.538", 0x000000, 0x40000, CRC(43f48265) SHA1(05500d56c808123b803be0efa71dd233a55793d1) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n027001a.638", 0x000001, 0x40000, CRC(f774d850) SHA1(5b63b4893b5b86b5c2ecf3e0be6d83d9b92e754c) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n027001a.53c", 0x100000, 0x40000, CRC(cbf9eef8) SHA1(6baf6c5f4fc52fc48d0e43014b11fdfe26e6db70) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n027001a.63c", 0x100001, 0x40000, CRC(14a81e58) SHA1(53216ad674e553829db3cc23d1e827c18d70c04e) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n027001b.538", 0x200000, 0x40000, CRC(3dae0a05) SHA1(0bf63e5676e3caab6f9d4895c9cbeb600bb6a8a1) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n027001b.638", 0x200001, 0x40000, CRC(0fb30b5b) SHA1(89f1176a55040d7ca0246231a9a0b027d2e0c304) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n027001b.53c", 0x300000, 0x40000, CRC(6979368e) SHA1(d1faae6fafbb7de21e7ee56356c30f18b7c4a130) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n027001b.63c", 0x300001, 0x40000, CRC(cfa90d59) SHA1(3185e00a030ace45f543b3a4ab6c101107727d01) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( mutnatd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n014001a.038", 0x000001, 0x040000, CRC(30cbd46b) SHA1(48357c8b704526da7101c06a120b096ec160a7bb) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "014.s1", CRC(99419733) SHA1(b2524af8704941acc72282aa1d62fd4c93e3e822) ) // n014001a.378

	NEO_BIOS_AUDIO_128K( "n014001a.4f8", CRC(2db6862d) SHA1(35cfe136edb09f0b13d312527dd71b4250c04383) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n014001a.1f8", 0x000000, 0x080000, CRC(8db2effe) SHA1(4bdfc36ed3c986ef153e03efbc581536876a3ebb) )
	ROM_LOAD( "n014001a.1fc", 0x080000, 0x080000, CRC(a49fe238) SHA1(378842d7fa93496ee103be3a0996c6943d285274) )
	ROM_LOAD( "n014001b.1f8", 0x100000, 0x080000, CRC(2ba17cb7) SHA1(99fa247c003b74b5da56631d11a63045dd5ef0d5) )
	ROM_LOAD( "n014001b.1fc", 0x180000, 0x080000, CRC(42419a29) SHA1(5185c978edb89a1764ee0b874be980b61280c822) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n014001a.538", 0x000000, 0x40000, CRC(83d59ccf) SHA1(90daecf9594715ac33c4a6294f481914351c702f) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n014001a.638", 0x000001, 0x40000, CRC(9e115a04) SHA1(16f04c7b3c5f6888591e9c2e385efb984e393571) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n014001a.53c", 0x100000, 0x40000, CRC(b2f1409d) SHA1(ab3af0fb4f4ca4afba098a6f8e9926b530a279df) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n014001a.63c", 0x100001, 0x40000, CRC(1bb648c1) SHA1(21afaf1e5ea541d5ac9bb273887baf662c52dfab) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n014001b.538", 0x200000, 0x40000, CRC(eaa2801a) SHA1(fec321bc839e5eeb4bfc88785276ee7af345f6c0) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n014001b.638", 0x200001, 0x40000, CRC(32bf4a2d) SHA1(f68419c9414dfbcc67c3a4b8cbef42b0b5fda0bc) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n014001b.53c", 0x300000, 0x40000, CRC(c718b731) SHA1(37eb725d43ecda891f67b607b5d5f039fc81a8cb) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n014001b.63c", 0x300001, 0x40000, CRC(7d120067) SHA1(d0e4f0f8c1455a51b5d769fa4bcd5f29bd894c13) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( ncombatd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n009001a.038", 0x000001, 0x040000, CRC(89660a31) SHA1(ac37a1060ee82733d8efef8c50f79672fe312097) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "009.s1", CRC(d49afee8) SHA1(77615f12edf08ae8f1353f7a056a8f3a50d3ebdc) ) // n009001a.378

	NEO_BIOS_AUDIO_64K( "n009001a.478", CRC(83821d6e) SHA1(687ad38aa20a113c4f59e7ebc1c911bb8e635ad7) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "009.v11", 0x000000, 0x080000, CRC(cf32a59c) SHA1(af5b7fcd8a4aff1307c0a1d937e5f0460c32de79) ) // n009001a.178
	ROM_LOAD( "009.v12", 0x080000, 0x080000, CRC(7b3588b7) SHA1(a4e6d9d4113ff4ce48b371f65e9187d551821d3b) ) // n009001a.17c
	ROM_LOAD( "009.v13", 0x100000, 0x080000, CRC(505a01b5) SHA1(9426a4f5b31e16f74e72e61951c189a878f211c5) ) // n009001b.178

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "009.v21", 0x000000, 0x080000, CRC(365f9011) SHA1(aebd292214ab280b05ee9e759b7e9a681a099c4a) ) // n009001a.278

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n009001a.538", 0x000000, 0x40000, CRC(0147a4b5) SHA1(0a2f60bb7166bd5a2ad669820b0f26d630e94958) )
	ROM_CONTINUE( 0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n009001a.638", 0x000001, 0x40000, CRC(e3d367f8) SHA1(8129c6845b8969f26c7cfe8761bb2bb07e5dc549) )
	ROM_CONTINUE( 0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n009001a.53c", 0x100000, 0x40000, CRC(4df6123a) SHA1(53970d86a848f498ebd5676c0a9d6fe8e026def8) )
	ROM_CONTINUE( 0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n009001a.63c", 0x100001, 0x40000, CRC(1c1f6101) SHA1(9594d199bafa9317bcf8b7447442171ea9b1056d) )
	ROM_CONTINUE( 0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n009001b.538", 0x200000, 0x40000, CRC(19441c78) SHA1(6355039f445456ffe32a512b635e365c5519d0c7) )
	ROM_CONTINUE( 0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n009001b.638", 0x200001, 0x40000, CRC(f417f9ac) SHA1(438e76b54bb82517a57cb3405a99dda0b3d66dc0) )
	ROM_CONTINUE( 0x200003, 0x40000 )
ROM_END

ROM_START( ncommandd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n050001a.038", 0x000001, 0x040000, CRC(fdaaca42) SHA1(aa32936bbe8ee53e717a3582847af89d1e160ff4) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n050001a.03c", 0x080001, 0x040000, CRC(b34e91fe) SHA1(3fbf40b9473bc6b0633c62fffdebc43d86785c7d) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "050.s1", CRC(db8f9c8e) SHA1(11cb82cf3c4d0fc2da5df0c26410a64808093610) ) // n050001a.378

	NEO_BIOS_AUDIO_64K( "n050001a.4f8", CRC(26e93026) SHA1(ea38754748ee2a9250864cd1836db463a1b29b1e) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n050001a.1f8", 0x000000, 0x080000, CRC(222e71c8) SHA1(5a598414b859ae6fbe4fb1b4bf622b1198232864) )
	ROM_LOAD( "n050001a.1fc", 0x080000, 0x080000, CRC(12acd064) SHA1(c2d7f55df6e49c54c0cab6d5db4cb82f97c6bab9) )
	ROM_LOAD( "050.v2",    0x100000, 0x080000, CRC(80b8a984) SHA1(950cf0e78ceffa4037663f1086fbbc88588f49f2) ) // n050001b.1f8

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n050001a.538", 0x000000, 0x40000, CRC(73acaa79) SHA1(1394c93132337469e283053f34c83658a9df771e) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n050001a.638", 0x000001, 0x40000, CRC(7b24359f) SHA1(99c5f59d479afbbc6ab8ef9dc4f90b9b5d42a199) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n050001a.53c", 0x100000, 0x40000, CRC(ad56623d) SHA1(afeaeed8917f259905a5cb46deb42bf6b0e7fd35) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n050001a.63c", 0x100001, 0x40000, CRC(0913a784) SHA1(5cee03ff0b41c58ad0b663c4bf100ae4a2152ee1) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n050001b.538", 0x200000, 0x40000, CRC(c8d763cd) SHA1(1d489c22bedd324d19cb02bed874e986f2627152) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n050001b.638", 0x200001, 0x40000, CRC(574612ec) SHA1(6c5863f2fc7b63808e8762aa839614919034aaa8) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n050001b.53c", 0x300000, 0x40000, CRC(63829529) SHA1(132f835fc2a6ca073700b1935ce3ebd32ba37f3e) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n050001b.63c", 0x300001, 0x40000, CRC(990d302a) SHA1(e0d07eb287b2ad143c72eeef39a3455d9d802a4a) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( ridherod )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n006001a.038", 0x000001, 0x040000, CRC(dabfac95) SHA1(234750f08954a94b2846f7ab79b67d6db2b67f6e) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_64K( "n006001a.378", CRC(197d1a28) SHA1(3f6ec453ebdead50c9fabd71071817b699a8a82c) )

	NEO_BIOS_AUDIO_64K( "n006001a.478", CRC(f7196558) SHA1(88c9183db5cb24849a8a548cd48d0732ee1e6219) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "006.v11", 0x000000, 0x080000, CRC(cdf74a42) SHA1(a17106cc3f9e5c5d52b4def861c0545a98151da2) ) // n006001a.178
	ROM_LOAD( "006.v12", 0x080000, 0x080000, CRC(e2fd2371) SHA1(cc95297bee7ffbdcb24ac4daeb5307cb39a52067) ) // n006001a.17c

	ROM_REGION( 0x200000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "006.v21", 0x000000, 0x080000, CRC(94092bce) SHA1(1a2906271fe6bc396898a756153629a5862930eb) ) // n006001a.278
	ROM_LOAD( "006.v22", 0x080000, 0x080000, CRC(4e2cd7c3) SHA1(72fb215a4f208a22a764e801186d1643d3d840ca) ) // n006001a.27c
	ROM_LOAD( "006.v23", 0x100000, 0x080000, CRC(069c71ed) SHA1(f450e9f60cd6ef846dbc77993159ec6157fb64e7) ) // n006001b.278
	ROM_LOAD( "006.v24", 0x180000, 0x080000, CRC(89fbb825) SHA1(656a97c6a8832dab3a5e1577d9cd257b561cc356) ) // n006001b.27c

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n006001a.538", 0x000000, 0x40000, CRC(24096241) SHA1(60a3dd2400be7208c7a471a813621a778f083240) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n006001a.638", 0x000001, 0x40000, CRC(df6a5b00) SHA1(ffd55c36847b0caa7b94b102ef3409d89e0d66c7) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n006001a.53c", 0x100000, 0x40000, CRC(7026a3a2) SHA1(55f70d2604832125c06742d75ce8ccf5c047d580) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n006001a.63c", 0x100001, 0x40000, CRC(15220d51) SHA1(72ad9e0381f84a33219255d42223bca01a23927c) )
	ROM_CONTINUE(             0x100003, 0x40000 )
ROM_END

ROM_START( roboarmyd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n032001a.038", 0x000001, 0x040000, CRC(99c7b4fc) SHA1(06a5bd4dd8f6db81eb36d0a8f0612caa1c917325) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "032.s1", CRC(ac0daa1b) SHA1(93bae4697dc403fce19422752a514326ccf66a91) ) // n032001a.378

	NEO_BIOS_AUDIO_128K( "032e.m1", CRC(98edc671) SHA1(04ed65ccaa1197fa55fcefe2caed2772e7040bdb) ) // n032001a.4f8

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "032e.v1", 0x000000, 0x080000, CRC(daff9896) SHA1(2f8a39b98ff2f4a0c8901b1befcc69e0cc5f5aed) ) // n032001a.1f8
	ROM_LOAD( "032e.v2", 0x080000, 0x080000, CRC(8781b1bc) SHA1(4e3cc22ac0acd4033cd4a327269c68b5f56bbe34) ) // n032001a.1fc
	ROM_LOAD( "032e.v3", 0x100000, 0x080000, CRC(b69c1da5) SHA1(7d5ea49338aeef711fc64755abed51fcdd939d48) ) // n032001b.1f8
	ROM_LOAD( "032e.v4", 0x180000, 0x080000, CRC(2c929c17) SHA1(7e053035573de9f601de80d200d09ed4844506fe) ) // n032001b.1fc

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n032001a.538", 0x000000, 0x40000, CRC(e3afaf17) SHA1(b11a45e77f10764f8c845a258d4add74146f1ffe) )
	ROM_CONTINUE( 0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n032001a.638", 0x000001, 0x40000, CRC(3a098b3b) SHA1(93520f664a76de7fac0baeb81daae8943aef0749) )
	ROM_CONTINUE( 0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n032001a.53c", 0x100000, 0x40000, CRC(17098f54) SHA1(69c775685f29e6b6af4f2bed1570bdd7a9c20cec) )
	ROM_CONTINUE( 0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n032001a.63c", 0x100001, 0x40000, CRC(8e3b2b88) SHA1(3ae3c3a5b64a523b294f1166f5506c850edc7f15) )
	ROM_CONTINUE( 0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n032001b.538", 0x200000, 0x40000, CRC(13cbb7c5) SHA1(2f3a92dccd440a5dd9542f423ac74ee3f4255066) )
	ROM_CONTINUE( 0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n032001b.638", 0x200001, 0x40000, CRC(b6f5fc62) SHA1(5d520d2cdd2d99e7d1c9f3c20448464318c8a03c) )
	ROM_CONTINUE( 0x200003, 0x40000 )
ROM_END

ROM_START( sengokud )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n017001a.038", 0x000001, 0x040000, CRC(4483bae1) SHA1(ca5f41be42cd9ce1a2c5007f068514500849a7f4) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n017001a.03c", 0x080001, 0x040000, CRC(d0d55b2a) SHA1(3800154495fbc2f62a539604bf6e5f156316dccd) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "017.s1", CRC(b246204d) SHA1(73dce64c61fb5bb7e836a8e60f081bb77d80d281) ) // n017001a.378

	NEO_BIOS_AUDIO_128K( "n017001a.4f8", CRC(e7bc4a94) SHA1(236d8dddafe5215558f3b0fbb2de3d6c39dd622b) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n017001a.1f8", 0x000000, 0x080000, CRC(205258a7) SHA1(4cd463a78575d7e74c871660588dc0fe17cce07d) )
	ROM_LOAD( "n017001a.1fc", 0x080000, 0x080000, CRC(6fbe52c8) SHA1(487f07968854ba3238ba2c612c8b20196f94cab2) )
	ROM_LOAD( "n017001b.1f8", 0x100000, 0x080000, CRC(6421bdf3) SHA1(823ffcbb9fc8b1219857b8cb6e089e2e21144ab3) )
	ROM_LOAD( "n017001b.1fc", 0x180000, 0x080000, CRC(1f9578fb) SHA1(7ccdb0e960d6e425e773a99208180dcf5ee7856f) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n017001a.538", 0x000000, 0x40000, CRC(e834b925) SHA1(08cfdcf232f3319f62b00cfec5c02b55d7c3405e) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n017001a.638", 0x000001, 0x40000, CRC(96de5eb9) SHA1(a70dfbffb109ddec5b4a2c6f60756d6717fce03b) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n017001a.53c", 0x100000, 0x40000, CRC(66be6d46) SHA1(3cd5bf09f994159caff23ba01700e7531ebc5b57) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n017001a.63c", 0x100001, 0x40000, CRC(25f5fd7b) SHA1(f1b2d58c6b73f3001751bf4c81f3d8664c96091c) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n017001b.538", 0x200000, 0x40000, CRC(443c552c) SHA1(75203f58935eb6a554542bb6ece457f8a2b51adb) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n017001b.638", 0x200001, 0x40000, CRC(afbd5b0b) SHA1(639fecb5afd5fb31ba169149d61830330169d7df) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n017001b.53c", 0x300000, 0x40000, CRC(ecb41adc) SHA1(741ddfdb8cbfacd95c37243dbf098a09ad6d6f0b) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n017001b.63c", 0x300001, 0x40000, CRC(78b25278) SHA1(c1ed3be0e0bc5c6bebaee1bb851cfb9c0b8b243f) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( sengoku2d )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n040001a.038", 0x000001, 0x040000, CRC(d1bf3fa5) SHA1(4a6c82d9294980eca6f9311d62f4d683baca173e) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n040001a.03c", 0x080001, 0x040000, CRC(ee9d0bb4) SHA1(27748b3a1b2e59cda29a85a6a467e1a46be3fe60) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "040.s1", CRC(cd9802a3) SHA1(f685d4638f4f68e7e3f101c0c39128454536721b) ) // n040001a.378

	NEO_BIOS_AUDIO_128K( "n040001a.4f8", CRC(9902dfa2) SHA1(af6284c5298328156726b76b968995ad25fdf4de) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n040001a.1f8", 0x000000, 0x080000, CRC(e6e9d82f) SHA1(a4691ef7719c55fa665dbe8f4420008cf6f23ae2) )
	ROM_LOAD( "n040001a.1fc", 0x080000, 0x080000, CRC(0504e71e) SHA1(856a200e2e4c39c0985d10b1dcd75e89e69b6f5d) )
	ROM_LOAD( "n040001b.1f8", 0x100000, 0x080000, CRC(e6c57d21) SHA1(e1f1403c3340be1ab66f027b2678bee3267b9f3c) )
	ROM_LOAD( "n040001b.1fc", 0x180000, 0x080000, CRC(000d319d) SHA1(88424ceca50e03ed41bad0493461bccfee519ec5) )
	ROM_LOAD( "n040001c.1f8", 0x200000, 0x080000, CRC(6650bc9a) SHA1(43e9da8176b9c282eaaaf8963fd7c7bd83d61953) )
	ROM_LOAD( "n040001c.1fc", 0x280000, 0x080000, CRC(c6358d62) SHA1(ca1d72a8a3ea9a2b5a800aeb091098d723eef963) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n040001a.538", 0x000000, 0x40000, CRC(da18aaed) SHA1(926500715ba30a5fad128ba877ca5f59bd98399b) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n040001a.638", 0x000001, 0x40000, CRC(5b27c829) SHA1(166ff9359b819a068763e868da69cf67976ec8c8) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n040001a.53c", 0x100000, 0x40000, CRC(19796c4f) SHA1(cf15a65c6bc5243978df6c91b3dce120e4b6db4a) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n040001a.63c", 0x100001, 0x40000, CRC(e8b46e26) SHA1(5b47903fd7b9783e6e18bbff33e0d7747305bda9) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n040001b.538", 0x200000, 0x40000, CRC(891b6386) SHA1(9d5e3b2fb6c2247712637f0f7b647042e0485eb6) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n040001b.638", 0x200001, 0x40000, CRC(93d25955) SHA1(039567a2426794bac9a502d7a46ed13bcc804764) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	// These probably not used. 3xxxxx same roms as 2xxxxx
	ROM_LOAD32_BYTE( "n040001c.538", 0x400000, 0x40000, CRC(c5eaabe8) SHA1(724f0b47e7e166b65b5e5fee790850aed15d2885) )
	ROM_CONTINUE(             0x400002, 0x40000 )
	ROM_LOAD32_BYTE( "n040001c.638", 0x400001, 0x40000, CRC(432bd7d0) SHA1(662179ed7c82f9f825b89650761db093ef9f7467) )
	ROM_CONTINUE(             0x400003, 0x40000 )
	ROM_LOAD32_BYTE( "n040001c.53c", 0x500000, 0x40000, CRC(22633905) SHA1(3afcf2bf752afa1593f144a8a9749736a09f6738) )
	ROM_CONTINUE(             0x500002, 0x40000 )
	ROM_LOAD32_BYTE( "n040001c.63c", 0x500001, 0x40000, CRC(ba3f54b2) SHA1(796ac0d021552b2ed1b95f11cad1e5e1530abcc7) )
	ROM_CONTINUE(             0x500003, 0x40000 )
ROM_END

ROM_START( socbrawld )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n031001a.038", 0x000001, 0x040000, CRC(9fa17911) SHA1(b5a86cc8c8b6e44e392deb6e975ee59076c4392a) )
	ROM_CONTINUE (                 0x000000, 0x040000 )

	NEO_SFIX_128K( "031.s1", CRC(4c117174) SHA1(26e52c4f628338a9aa1c159517cdf873f738fb98) ) // n031001a.378

	NEO_BIOS_AUDIO_128K( "n031001a.4f8", CRC(bc45269b) SHA1(19b82e7174a6fe5caaec35c0603944a090a43b65) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n031001a.1f8", 0x000000, 0x080000, CRC(670dc165) SHA1(f75d174cfc0d4c16375c58069b923380ae8c6923) )
	ROM_LOAD( "n031001a.1fc", 0x080000, 0x080000, CRC(abb9537b) SHA1(0f272ef6bfdb1b5b0580fe9d01070e4f60b383ff) )
	ROM_LOAD( "n031001b.1f8", 0x100000, 0x080000, CRC(600be43e) SHA1(5639e239910f0fb07f26e4f9816efd77b04f6152) )
	ROM_LOAD( "n031001b.1fc", 0x180000, 0x080000, CRC(88d30359) SHA1(884cabd8a6ccbdd470aab3b7325fdeade01679f0) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n031001a.538", 0x000000, 0x40000, CRC(945bf77c) SHA1(0f971d5c21c051d2298866b69c96715f583fe521) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n031001a.638", 0x000001, 0x40000, CRC(6708fc58) SHA1(230253fbe761cb1164efb9a3c91ac1f24f57295b) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n031001a.53c", 0x100000, 0x40000, CRC(9a210d0d) SHA1(be9b9587c138679e2fb299455d98e2ac6ffad63b) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n031001a.63c", 0x100001, 0x40000, CRC(9a97c680) SHA1(746a5cb5bf713c806cef24d21347f5b96c86ccab) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n031001b.538", 0x200000, 0x40000, CRC(057dbb51) SHA1(cab14d98cbbfc0e5714082fd2db8c73e9c6cd684) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n031001b.638", 0x200001, 0x40000, CRC(434c17c8) SHA1(629dc40ab09ac0a2f55234bc34c4ba63c0b8912f) )
	ROM_CONTINUE(             0x200003, 0x40000 )
ROM_END

ROM_START( superspyd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n011001a.038", 0x000001, 0x040000, CRC(2e949e32) SHA1(c5a5bb996c5c0224b27813a76223c56860ddb399) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n011001a.03c", 0x080001, 0x040000, CRC(54443d72) SHA1(5cb78d50996c1f9a182e9350d94ba2953463ed4b) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "011.s1", CRC(ec5fdb96) SHA1(8003028025ac7bf531e568add6ba66c02d0b7e84) ) // n011001a.378

	NEO_BIOS_AUDIO_64K( "n011001a.478", CRC(64455806) SHA1(454e95503be8ec5dd2332da1ce08c832a2ab81b8) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n011001a.178", 0x000000, 0x080000, CRC(b993bc83) SHA1(b7689a57120b9eb3d23b6675f8791c117360a267) )
	ROM_LOAD( "n011001a.17c", 0x080000, 0x080000, CRC(d7a059b1) SHA1(b13c1c674f66cb6852f0a206554e4616f5fde236) )
	ROM_LOAD( "011.v12", 0x100000, 0x080000, CRC(9f513d5a) SHA1(37b04962f0b8e2a74abd35c407337a6151dc4e95) ) // n011001b.178

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "011.v21", 0x000000, 0x080000, CRC(426cd040) SHA1(b2b45189837c8287223c2b8bd4df9525b72a3f16) ) // n011001a.278

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n011001a.538", 0x000000, 0x40000, CRC(239f22c4) SHA1(91f985fb9acb36ab5f8877f62c0476a291f3b591) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n011001a.638", 0x000001, 0x40000, CRC(5f2e5184) SHA1(b2704eff6815da611f0f2ad15f2a85d482a111d3) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n011001a.53c", 0x100000, 0x40000, CRC(ce80c326) SHA1(3f1f72d923dde87e87bc74080cc1858f42413ab2) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n011001a.63c", 0x100001, 0x40000, CRC(79b3e0b1) SHA1(1f627f7b8d86292d4f4cdc0f15782d060a91b551) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n011001b.538", 0x200000, 0x40000, CRC(1edcf268) SHA1(a691f76980e7a0da63948a5d75f32afa6c92c9c3) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n011001b.638", 0x200001, 0x40000, CRC(b2afe822) SHA1(56d623e4a468ac88c6bbc54ff6f640a7aa5f93f5) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n011001b.53c", 0x300000, 0x40000, CRC(a41602a0) SHA1(95ee2162de50be72982edcecb437995a43d39a07) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n011001b.63c", 0x300001, 0x40000, CRC(d425f967) SHA1(4085782d440ad265ae45f43c83b1d1fa96d15524) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( tpgolfd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n003001a.038", 0x000001, 0x040000, CRC(542e93d9) SHA1(530d8e344481ae98edd4ca8b86146c44f587228f) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n003001a.03c", 0x080001, 0x040000, CRC(03f1bead) SHA1(b2e40d936636e5d2108fcdf4f440095b3e6da9b5) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "003.s1", CRC(7b3eb9b1) SHA1(39cd8bad9f8bfdeb8ac681b5b79ae5aa81c8dd5f) ) // n003001a.378

	NEO_BIOS_AUDIO_64K( "003cd.m1", CRC(7851d0d9) SHA1(d021cef958cc37ab170b78d7a4b3ae94947e4d13) ) // n003001a.478

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "003.v11", 0x000000, 0x080000, CRC(ff97f1cb) SHA1(defa249d46ae220f7bfa70746f5202bbbcc3e5fe) ) // n003001a.178

	ROM_REGION( 0x100000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "003.v21", 0x000000, 0x080000, CRC(d34960c6) SHA1(36d5877d5e42aab943f4d693159f4f3ad8b0addc) ) // n003001a.278
	ROM_LOAD( "003.v22", 0x080000, 0x080000, CRC(9a5f58d4) SHA1(2b580595e1820430a36f06fd3e0e0b8f7d686889) ) // n003001a.27c

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n003001a.538", 0x000000, 0x40000, CRC(67633f80) SHA1(951e11f5f74434a3ce9b11bf75b822b2ffbf2c8f) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n003001a.638", 0x000001, 0x40000, CRC(ba49936b) SHA1(c5eb478da0dc409bc5853438387a93d9a2ecdd04) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n003001a.53c", 0x100000, 0x40000, CRC(bed644d0) SHA1(687ebf0928983e6e795619124a90696c3de3d55d) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n003001a.63c", 0x100001, 0x40000, CRC(7fc96498) SHA1(f97da62165388d321ef6e31b3121b14e17fa9a5f) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n003001b.538", 0x200000, 0x40000, CRC(977a0ea9) SHA1(a2704d9a4a576058feacd237bb7ba28508df0207) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n003001b.638", 0x200001, 0x40000, CRC(a56853ec) SHA1(242e65c73b63adc0cd527bcdb03ac82fde5be5ef) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n003001b.53c", 0x300000, 0x40000, CRC(bc0ebc0e) SHA1(ed6c4b8b126ea66e75666358c02cbfe2e90985fe) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n003001b.63c", 0x300001, 0x40000, CRC(81347ea7) SHA1(8f7b78c91f449ba8e8d449ad436dd5421b6f12a6) )
	ROM_CONTINUE(             0x300003, 0x40000 )
ROM_END

ROM_START( trallyd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n038001a.038", 0x000001, 0x040000, CRC(400bed38) SHA1(9ccc6a505e98e964db9253b50ae549a8d13beffb) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n038001a.03c", 0x080001, 0x040000, CRC(77196e9a) SHA1(31490ce2b97f67e9571ace32d97217232113fb72) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "038.s1", CRC(fff62ae3) SHA1(6510a762ea41557a8938cbfc0557cd5921306061) ) // n038001a.378

	NEO_BIOS_AUDIO_64K( "n038001a.4f8", CRC(308c4a8d) SHA1(6b1e5790442bcf4e3a9fb896bbd293eb33fb4990) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n038001a.1f8", 0x000000, 0x080000, CRC(1c93fb89) SHA1(a5056e33552e3e6fc3570d41e893a73d78086077) )
	ROM_LOAD( "n038001a.1fc", 0x080000, 0x080000, CRC(39f18253) SHA1(97622e15ebc180dc24d5b9049d6603cbe039dc81) )
	ROM_LOAD( "038.v2",    0x100000, 0x080000, CRC(ddd8d1e6) SHA1(65c819fa2392f264f5a1a0a4967c96775732500b) ) // n038001b.1f8

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n038001a.538", 0x000000, 0x40000, CRC(4d002ecb) SHA1(07330d6cbcd126bd67c702cc351ac4f668108e55) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n038001a.638", 0x000001, 0x40000, CRC(6b2f79de) SHA1(7725b9b66738a6f9fe9456cc6aadd4fa98d50bff) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n038001a.53c", 0x100000, 0x40000, CRC(b0be56db) SHA1(f511e1ef9074eec9bff37f22607cd5b491860ee7) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n038001a.63c", 0x100001, 0x40000, CRC(091f38b4) SHA1(0e579029524f004370d1c93d7b14ad47243bee66) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n038001b.538", 0x200000, 0x40000, CRC(2f213750) SHA1(fe5a8cd26b52928afeece5504ecca7ec452b7027) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n038001b.638", 0x200001, 0x40000, CRC(268be38b) SHA1(98f9dfee915ddf8d858297075c7b7d6731527aa3) )
	ROM_CONTINUE(             0x200003, 0x40000 )
ROM_END

ROM_START( wh1d )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "n053001a.038", 0x000001, 0x040000, CRC(ab39923d) SHA1(be9fc3c89a452e64d02231d531bb298d201ef002) )
	ROM_CONTINUE (                 0x000000, 0x040000 )
	ROM_LOAD16_BYTE ( "n053001a.03c", 0x080001, 0x040000, CRC(5adc98ef) SHA1(0c87725b343f7705f974de71c4bc46afdc75c80b) )
	ROM_CONTINUE (                 0x080000, 0x040000 )

	NEO_SFIX_128K( "053.s1", CRC(8c2c2d6b) SHA1(87fa79611c6f8886dcc8766814829c669c65b40f) ) // n053001a.378

	NEO_BIOS_AUDIO_128K( "053.m1", CRC(1bd9d04b) SHA1(65cd7b002123ed1a3111e3d942608d0082799ff3) ) // n053001a.4f8

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "n053001a.1f8", 0x000000, 0x080000, CRC(77994663) SHA1(7adaddf13177b1d18604611dfae7fc43b35a0766) )
	ROM_LOAD( "n053001a.1fc", 0x080000, 0x080000, CRC(d74ad0da) SHA1(fe71db5808d46f7b56ea7603e500534cd8ab8beb) )
	ROM_LOAD( "n053001b.1f8", 0x100000, 0x080000, CRC(9d5fe808) SHA1(825eb3727d67e1cf8d8e254576de52952a35c25c) )
	ROM_LOAD( "n053001b.1fc", 0x180000, 0x080000, CRC(883fb383) SHA1(ceef987b5e8ce9c0201eb0c66628456b99b41fd2) )
	ROM_LOAD( "n053001c.1f8", 0x200000, 0x080000, CRC(b4ff60d7) SHA1(a1615ec7b309839fd0e690e57d19ab5a857eef1d) )
	ROM_LOAD( "n053001c.1fc", 0x280000, 0x080000, CRC(b358e4f5) SHA1(6b74306beb801f9e35e1a948b2508a38facb2080) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD32_BYTE( "n053001a.538", 0x000000, 0x40000, CRC(ad8fcc5d) SHA1(67683d40fa438032a3e9f5997c7ca5b798f50325) )
	ROM_CONTINUE(             0x000002, 0x40000 )
	ROM_LOAD32_BYTE( "n053001a.638", 0x000001, 0x40000, CRC(3182b4db) SHA1(371f898f5ef28b1efe8129fa6837ee31452e0881) )
	ROM_CONTINUE(             0x000003, 0x40000 )
	ROM_LOAD32_BYTE( "n053001a.53c", 0x100000, 0x40000, CRC(0dca726e) SHA1(9c9ea623102818b0c551a998be8b909c16967896) )
	ROM_CONTINUE(             0x100002, 0x40000 )
	ROM_LOAD32_BYTE( "n053001a.63c", 0x100001, 0x40000, CRC(1cb0a840) SHA1(c52b1dd8b4860d1bcff207f0f7c2278dfa195219) )
	ROM_CONTINUE(             0x100003, 0x40000 )
	ROM_LOAD32_BYTE( "n053001b.538", 0x200000, 0x40000, CRC(bb807a43) SHA1(f0583c2bd3ad69f12d3635edece4480414497395) )
	ROM_CONTINUE(             0x200002, 0x40000 )
	ROM_LOAD32_BYTE( "n053001b.638", 0x200001, 0x40000, CRC(c9f439f8) SHA1(be7ba30e5cfe22341f61ea2571cec551a5793bf3) )
	ROM_CONTINUE(             0x200003, 0x40000 )
	ROM_LOAD32_BYTE( "n053001b.53c", 0x300000, 0x40000, CRC(e913f93c) SHA1(af17419e46aa4f4809fc2f620a6e2d109fe17197) )
	ROM_CONTINUE(             0x300002, 0x40000 )
	ROM_LOAD32_BYTE( "n053001b.63c", 0x300001, 0x40000, CRC(80441c48) SHA1(fdfab6abd4e2212635c47270df27108c1904a15b) )
	ROM_CONTINUE(             0x300003, 0x40000 )
	ROM_LOAD32_BYTE( "n053001c.538", 0x400000, 0x40000, CRC(3c359a14) SHA1(3415bc48511d57bb54f926df1e282ee02787776d) )
	ROM_CONTINUE(             0x400002, 0x40000 )
	ROM_LOAD32_BYTE( "n053001c.638", 0x400001, 0x40000, CRC(7c4b85b4) SHA1(ae7b199f6e59b1b697c36e21ddfc525d6ad77c83) )
	ROM_CONTINUE(             0x400003, 0x40000 )
	ROM_LOAD32_BYTE( "n053001c.53c", 0x500000, 0x40000, CRC(b1327d84) SHA1(02f58cb1a18448f1f3c3752bb802b6f737151b9d) )
	ROM_CONTINUE(             0x500002, 0x40000 )
	ROM_LOAD32_BYTE( "n053001c.63c", 0x500001, 0x40000, CRC(959f29db) SHA1(f1126098840fb602c8b3349111e5954b73a66934) )
	ROM_CONTINUE(             0x500003, 0x40000 )
ROM_END

 /**************
  CD conversion
*****************/

ROM_START( 2020bbcd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "030cd.p1", 0x000000, 0x080000, CRC(e13d8a8a) SHA1(3975bdf141abc4994c9fc1919fb4207883687961) )

	NEO_SFIX_128K( "030.s1", CRC(7015b8fc) SHA1(8c09bc3e6c62e0f7c9557c1e10c901be325bae7f) )

	NEO_BIOS_AUDIO_64K( "030cd.m1", CRC(124d7b4f) SHA1(fd7bceacd0ec17cab7abb28ee8eab92217f9c197) )
	// use this to get full sound
	//NEO_BIOS_AUDIO_128K( "030.m1", CRC(4cf466ec) SHA1(6a003b53c7a4af9d7529e2c10f27ffc4e58dcda5) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "030cd.v1", 0x000000, 0x100000, CRC(d725a649) SHA1(cd1206b7190e543f31eb878f645f3be841c5a4ed) )
	ROM_LOAD( "030.v2", 0x100000, 0x100000, CRC(54994455) SHA1(76eb62b86e8ed51a77f44313d5cc8091b3f58d57) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "030.c1", 0x000000, 0x100000, CRC(4f5e19bd) SHA1(ef7975c4b33a7aea4a25a385f604799f054d3200) )
	ROM_LOAD16_BYTE( "030.c2", 0x000001, 0x100000, CRC(d6314bf0) SHA1(0920cc580d7997fcb0170dd619af2f305d635577) )
	ROM_LOAD16_BYTE( "030.c3", 0x200000, 0x100000, CRC(47fddfee) SHA1(297c505a63448c999a2510c27bf4549102134db8) )
	ROM_LOAD16_BYTE( "030.c4", 0x200001, 0x100000, CRC(780d1c4e) SHA1(2e2cf9de828e3b48642dd2203637103438c62142) )
ROM_END

ROM_START( crswd2bl )
	ROM_REGION( 0x200000, "maincpu", ROMREGION_BE|ROMREGION_16BIT )
	ROM_LOAD16_WORD_SWAP( "054bl.p1", 0x100000, 0x100000, CRC(64836147) SHA1(083cb1626885893e736fc9998036c952cd4d503b) )
	ROM_CONTINUE( 0x000000, 0x100000 )

	NEO_SFIX_128K( "054bl.s1", CRC(22e02ddd) SHA1(ebd834affc763cc5854abf1c6c42f43f3f3755fd) )

	NEO_BIOS_AUDIO_128K( "054bl.m1", CRC(63e28343) SHA1(f46dbc2f1d6033b11047cca31a9a7d715dc69cb2) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "054bl.v1", 0x000000, 0x200000, CRC(22d4b93b) SHA1(0515f2ee5d9a8ce424c80721e06f746ac6a543a8) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "054.c1", 0x000000, 0x400000, CRC(8221b712) SHA1(7e68871f1bfc402ef27c8fa088c680cbd133f71a) )
	ROM_LOAD16_BYTE( "054.c2", 0x000001, 0x400000, CRC(d6c6183d) SHA1(cc546ff063fae2c01c109fabcd5b2d29ec3299db) )
ROM_END

ROM_START( gpilotscd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "020cd.p1", 0x000000, 0x100000, CRC(f139df88) SHA1(8a2ce01f83c3c529b3c823555e19f815e0a558b3) )

	NEO_SFIX_128K( "020.s1", CRC(a6d83d53) SHA1(9a8c092f89521cc0b27a385aa72e29cbaca926c5) )

	NEO_BIOS_AUDIO_64K( "020cd.m1", CRC(08697f52) SHA1(670998421355ccfdc5e778123b9df54df4dcde76) )
	// use this to get full sound
	//NEO_BIOS_AUDIO_128K( "020.m1", CRC(48409377) SHA1(0e212d2c76856a90b2c2fdff675239525972ac43) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "020cd.v11", 0x000000, 0x100000, CRC(1285132c) SHA1(dad570624888550937ea15180c9ceb5fcdb418b8) )
	ROM_LOAD( "020.v12", 0x100000, 0x080000, CRC(4a9e6f03) SHA1(d3ac11f333b03d8a318921bdaefb14598e289a14) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "020.v21", 0x000000, 0x080000, CRC(7abf113d) SHA1(5b2a0e70f2eaf4638b44702dacd4cb17838fb1d5) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "020.c1", 0x000000, 0x100000, CRC(bd6fe78e) SHA1(50b704862cd79d64fa488e621b079f6e413c33bc) )
	ROM_LOAD16_BYTE( "020.c2", 0x000001, 0x100000, CRC(5f4a925c) SHA1(71c5ef8141234daaa7025427a6c65e79766973a5) )
	ROM_LOAD16_BYTE( "020.c3", 0x200000, 0x100000, CRC(d1e42fd0) SHA1(f0d476aebbdc2ce008f5f0783be86d295b24aa44) )
	ROM_LOAD16_BYTE( "020.c4", 0x200001, 0x100000, CRC(edde439b) SHA1(79be7b10ecdab54c2f77062b8f5fda0e299fa982) )
ROM_END

ROM_START( ironcladcd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "220cd.p1", 0x00000, 0xd4000, CRC(cf9257b0) SHA1(2a2742865862d313b5d856e5b500b56b36336ecd) )

	NEO_SFIX_128K( "proto_220.s1", CRC(372fe217) SHA1(493433e682f519bf647e1481c8bdd3a980830ffb) )

	NEO_BIOS_AUDIO_64K( "220cd.m1", CRC(b4d7cab0) SHA1(23342f72595f9d460f2e94fbda437ba1364bb5ed) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "220cd.v1", 0x000000, 0x100000, CRC(f7fd9baa) SHA1(a9362d405705f03a1759c2034df0c48daa15b71d) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "proto_220.c1", 0x000000, 0x400000, CRC(9aa2b7dc) SHA1(6b3dff292c86f949890b1f8201bc5278f38c2668) )
	ROM_LOAD16_BYTE( "proto_220.c2", 0x000001, 0x400000, CRC(8a2ad708) SHA1(9568ac4cc0552e7fd3e50d3cd8d9f0f4fe7df1d4) )
	ROM_LOAD16_BYTE( "proto_220.c3", 0x800000, 0x400000, CRC(d67fb15a) SHA1(842971aeaf3c92e70f7c653bbf29058bc60f5b71) )
	ROM_LOAD16_BYTE( "proto_220.c4", 0x800001, 0x400000, CRC(e73ea38b) SHA1(27138d588e61e86c292f12d16e36c3681075c607) )
ROM_END

ROM_START( joyjoycd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "021cd.p1", 0x000000, 0x080000, CRC(a483fde0) SHA1(c42a04f5fec60678cbe20bc77675e0128aadf31c) )

	NEO_SFIX_128K( "021.s1", CRC(6956d778) SHA1(e3757776d60dc07d8e07c9ca61b223b14732f860) )

	NEO_BIOS_AUDIO_64K( "021cd.m1", CRC(e93556ad) SHA1(616fac84ec2fa80ef8f43fcf993a3186d43a96eb) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "021cd.v1", 0x000000, 0x080000, CRC(241235cd) SHA1(bc4992dde75134c934f6374f370d1831c8160633) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "021.v21", 0x000000, 0x080000, CRC(8ed20a86) SHA1(d15cba5eac19ea56fdd4877541f1bb3eb755ebba) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD16_BYTE( "021.c1", 0x000000, 0x080000, CRC(509250ec) SHA1(d6ddb16d8222088f153a85a905bcb99541a5f2cf) )
	ROM_LOAD16_BYTE( "021.c2", 0x000001, 0x080000, CRC(09ed5258) SHA1(6bf50cd10236e29146b49e714a0e0ebcfe30a682) )
ROM_END

ROM_START( joyjoycd1 )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "021cd.p1", 0x000000, 0x080000, CRC(a483fde0) SHA1(c42a04f5fec60678cbe20bc77675e0128aadf31c) )

	NEO_SFIX_128K( "021.s1", CRC(6956d778) SHA1(e3757776d60dc07d8e07c9ca61b223b14732f860) )

	NEO_BIOS_AUDIO_64K( "021cd1.m1", CRC(72072960) SHA1(83c70714fc458e78f39836b3a86a9b07a553bcdd) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "021cd1.v11", 0x000000, 0x080000, CRC(4fb2fbcc) SHA1(b1defbfd68eb824468c352c91e98d2fc4fba539d) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "021.v21", 0x000000, 0x080000, CRC(8ed20a86) SHA1(d15cba5eac19ea56fdd4877541f1bb3eb755ebba) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD16_BYTE( "021.c1", 0x000000, 0x080000, CRC(509250ec) SHA1(d6ddb16d8222088f153a85a905bcb99541a5f2cf) )
	ROM_LOAD16_BYTE( "021.c2", 0x000001, 0x080000, CRC(09ed5258) SHA1(6bf50cd10236e29146b49e714a0e0ebcfe30a682) )
ROM_END

ROM_START( lbowlingcd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "019cd.p1", 0x000000, 0x040000, CRC(c17fd30f) SHA1(908b045542bb575ac05f208a6595ab49c5ca5c0f) )

	NEO_SFIX_128K( "019.s1", CRC(5fcdc0ed) SHA1(86415077e7adc3ba6153eeb4fb0c62cf36e903fa) )

	//NEO_BIOS_AUDIO_64K( "019cd.m1", CRC(f65cb876) SHA1(6c26f400b2fce5fc8f3d533d275622a274982edc) )   // this has bugs and so there's no sound
	NEO_BIOS_AUDIO_128K( "019.m1", CRC(d568c17d) SHA1(a2e318ed6ad1809c79f3f0853d75e0dd1a2f275c) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	//ROM_LOAD( "019cd.v1", 0x000000, 0xf5400, CRC(37ff1111) SHA1(ff964981cff279e32da3c583a95912d5ffb5ab22) )  // doesn't match to 019.m1
	ROM_LOAD( "019.v11", 0x000000, 0x080000, CRC(0fb74872) SHA1(38c555926c77576d63472bc075210c42e9ce13a3) )
	ROM_LOAD( "019.v12", 0x080000, 0x080000, CRC(029faa57) SHA1(7bbaa87e38929ab1e32df5f6a2ec0fd5001e7cdb) )

	ROM_REGION( 0x080000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "019.v21", 0x000000, 0x080000, CRC(2efd5ada) SHA1(8ba70f5f665d566824333075227d9bce1253b8d8) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD16_BYTE( "019.c1", 0x000000, 0x080000, CRC(4ccdef18) SHA1(5011e30ec235d0b0a5a513a11d4275777e61acdb) )
	ROM_LOAD16_BYTE( "019.c2", 0x000001, 0x080000, CRC(d4dd0802) SHA1(82069752028c118d42384a95befde45844f0f247) )
ROM_END

ROM_START( pbobblencd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "083cd.p1", 0x000000, 0x040000, CRC(b1095646) SHA1(20fa2bc724df4b5234ff0ccf3074e545f28d1bbd) )

	NEO_SFIX_128K( "083.s1", CRC(9caae538) SHA1(cf2d90a7c1a42107c0bb8b9a61397634286dbe0a) )

	NEO_BIOS_AUDIO_64K( "083cd.m1", CRC(c505fcdb) SHA1(2b3e10e1475c7c1425b382be30c765e455c5bbc6) )

	ROM_REGION( 0x180000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "083ch.v3", 0x000000, 0x100000, CRC(30ce579e) SHA1(635f7ab2178981ba38cc0080f4f97e954e552440) )
	ROM_LOAD( "083.v4", 0x100000, 0x080000, CRC(0a548948) SHA1(e1e4afd17811cb60401c14fbcf0465035165f4fb) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD16_BYTE( "083.c5", 0x000000, 0x80000, CRC(e89ad494) SHA1(69c9ea415773af94ac44c48af05d55ada222b138) )
	ROM_LOAD16_BYTE( "083.c6", 0x000001, 0x80000, CRC(4b42d7eb) SHA1(042ae50a528cea21cf07771d3915c57aa16fd5af) )
ROM_END

ROM_START( pspikes2cd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "068cd.p1", 0x000000, 0x100000, CRC(3920534c) SHA1(24e12b41b79145e4f3defaba7f77d1a57ffb8927) )

	//NEO_SFIX_128K( "068-sg1.s1", CRC(18082299) SHA1(efe93fabe6a76a5dc8cf12f255e571480afb40a0) )
	NEO_SFIX_128K( "068cd.s1", CRC(764ac7aa) SHA1(cc40ad276e63084ebf3c3ee224083762a47c3cf8) ) // used in many builds for fr2cd/fr2ch

	NEO_BIOS_AUDIO_64K( "068cd.m1", CRC(cddc55db) SHA1(6a80c26490bbdeaddf608522c69f4cd16ba74533) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "068cd.v1", 0x000000, 0x100000, CRC(850ee5a0) SHA1(600a75da9b0f657df75e2d9300cfa08116a8be85) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "068cd.c1", 0x000000, 0x100000, CRC(d380883b) SHA1(0625cddb4e2fcbd3c764732a197d963299bd7d99) )
	ROM_LOAD16_BYTE( "068cd.c2", 0x000001, 0x100000, CRC(9a5ad954) SHA1(4266760d2b6f2b7ef6e593c679b1639ec377e56b) )
	ROM_LOAD16_BYTE( "068cd.c3", 0x200000, 0x100000, CRC(13d8a7f0) SHA1(5e7c35afe1984c67ed03f33ce22e7546861d63e6) )
	ROM_LOAD16_BYTE( "068cd.c4", 0x200001, 0x100000, CRC(ca5af0be) SHA1(be47412b97413d3d36d4cb1acfc9fa252eb7dd70) )
ROM_END

ROM_START( sengokucd )
	ROM_REGION( 0x120000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "017cd.p1",  0x000000, 0x100000, CRC(89290fa2) SHA1(c546aaf74e823d76e5a9ac592edd098a7cf531ed) )
	ROM_LOAD16_WORD_SWAP( "017.p2", 0x100000, 0x020000, CRC(3024bbb3) SHA1(88892e1292dd60f35a76f9a22e623d4f0f9693cc) )

	NEO_SFIX_128K( "017.s1", CRC(b246204d) SHA1(73dce64c61fb5bb7e836a8e60f081bb77d80d281) )

	NEO_BIOS_AUDIO_128K( "017.m1", CRC(9b4f34c6) SHA1(7f3a51f47fcbaa598f5c76bc66e2c53c8dfd852d) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "017.v1", 0x000000, 0x100000, CRC(23663295) SHA1(9374a5d9f3de8e6a97c11f07d8b4485ac9d55edb) )
	ROM_LOAD( "017.v2", 0x100000, 0x100000, CRC(f61e6765) SHA1(1c9b287996947319eb3d288c3d82932cf01039db) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "017.c1", 0x000000, 0x100000, CRC(b4eb82a1) SHA1(79879e2ea78c07d04c88dc9a1ad59604b7a078be) )
	ROM_LOAD16_BYTE( "017.c2", 0x000001, 0x100000, CRC(d55c550d) SHA1(6110f693aa23710939c04153cf5af26493e4a03f) )
	ROM_LOAD16_BYTE( "017.c3", 0x200000, 0x100000, CRC(ed51ef65) SHA1(e8a8d86e24454948e51a75c883bc6e4091cbf820) )
	ROM_LOAD16_BYTE( "017.c4", 0x200001, 0x100000, CRC(f4f3c9cb) SHA1(8faafa89dbd0345218f71f891419d2e4e7578200) )
ROM_END

ROM_START( ssidekicd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "052cd.p1", 0x000000, 0x080000, CRC(5cdf0a46) SHA1(60b200eb8d7a217d1f4ce9a51d3c9730d5259fac) )

	NEO_SFIX_128K( "052.s1", CRC(97689804) SHA1(fa8dab3b3353d7115a0368f3fc749950c0186fbc) )

	NEO_BIOS_AUDIO_64K( "052cd.m1", CRC(f47f31a4) SHA1(50eaf535aec5f8f983e13c24f547d6d2d1004f39) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "052cd.v1", 0x000000, 0x100000, CRC(a6944870) SHA1(3c46d028998a57fa8bd46327f3497af1233698b0) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "052cd.c1", 0x000000, 0x100000, CRC(bf1b962b) SHA1(9bdec8df91a6713d6ce4dbc1ba5028eec74d4cb0) )
	ROM_LOAD16_BYTE( "052cd.c2", 0x000001, 0x100000, CRC(c3ce856b) SHA1(326c4a17c62ea97acc9a38e3b144dc9bc69158d4) )
	ROM_LOAD16_BYTE( "052cd.c3", 0x200000, 0x100000, CRC(7642df56) SHA1(f65cee51d4d8734982d305a1c5c4ddd4e064ebf7) )
	ROM_LOAD16_BYTE( "052cd.c4", 0x200001, 0x100000, CRC(265222dc) SHA1(d52a757779d74c2e32fd28bbc953ff8053f33a6c) )
ROM_END

ROM_START( strhoopcd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "079cd.p1", 0x000000, 0x100000, CRC(16795f7f) SHA1(977a6c31ca6553e1cfa3402a5e541bab4c2244be) )

	NEO_SFIX_128K( "079cd.s1", CRC(c65a5fe8) SHA1(ec8e8c49994ce9286ea5160c2450912da0746fb0) )

	NEO_BIOS_AUDIO_64K( "079cd.m1", CRC(1a5f08db) SHA1(3121ed568fba4c30794b00d326ddb0c750b7f4ee) )

	ROM_REGION( 0x280000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "079.v1", 0x000000, 0x200000, CRC(718a2400) SHA1(cefc5d0b302bd4a87ab1fa244ade4482c23c6806) )
	ROM_LOAD( "079cd.v2",  0x200000, 0x080000, CRC(b19884f8) SHA1(5fe910f2029da19ddab4dc95c2292d7fbb086741) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "079cd.c1", 0x000000, 0x200000, CRC(c3ebd902) SHA1(daae0ae972ecc0c19b2e6a439e5f2547286f190a) )
	ROM_LOAD16_BYTE( "079cd.c2", 0x000001, 0x200000, CRC(1a471f80) SHA1(725864d734ec9ab2933a46a6dc4d18dbc31fe2c7) )
	ROM_LOAD16_BYTE( "079cd.c3", 0x680000, 0x080000, CRC(4d490ecc) SHA1(8ced8f547799b613edd95acabd6f8cb28c41eab5) )
	ROM_LOAD16_BYTE( "079cd.c4", 0x680001, 0x080000, CRC(e223d27c) SHA1(2e195fea0d5808e90f154412b5e80b430e6341e2) )
ROM_END

ROM_START( superspycd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "011cd.p1",  0x000000, 0x0a0000, CRC(6ef37a8c) SHA1(b65328a4d9af099dabdca931a7487b07122e9433) )

	NEO_SFIX_128K( "011.s1", CRC(ec5fdb96) SHA1(8003028025ac7bf531e568add6ba66c02d0b7e84) )

	NEO_BIOS_AUDIO_64K( "011cd.m1", CRC(543a711a) SHA1(2d4a5b0a9c7d10c3b182c3a887b9ff7f50a2937a) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "011cd.v1", 0x000000, 0x100000, CRC(9d697082) SHA1(92497e97e1755b930bd960d861f4c5289af7d78d) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "011.c1", 0x000000, 0x100000, CRC(cae7be57) SHA1(43b35b349594535689c358d9f324adda55e5281a) )
	ROM_LOAD16_BYTE( "011.c2", 0x000001, 0x100000, CRC(9e29d986) SHA1(b417763bad1acf76116cd56f4203c2d2677e22e5) )
	ROM_LOAD16_BYTE( "011.c3", 0x200000, 0x100000, CRC(14832ff2) SHA1(1179792d773d97d5e45e7d8f009051d362d72e24) )
	ROM_LOAD16_BYTE( "011.c4", 0x200001, 0x100000, CRC(b7f63162) SHA1(077a81b2bb0a8f17c9df6945078608f74432877a) )
ROM_END

ROM_START( tpgolfcd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "003cd.p1",  0x000000, 0x100000, CRC(87f2a8ce) SHA1(ad903d7711ac4af47f1dee64ba7c6bb247029407) )

	NEO_SFIX_128K( "003.s1", CRC(7b3eb9b1) SHA1(39cd8bad9f8bfdeb8ac681b5b79ae5aa81c8dd5f) )

	NEO_BIOS_AUDIO_64K( "003cd.m1", CRC(7851d0d9) SHA1(d021cef958cc37ab170b78d7a4b3ae94947e4d13) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "003.v11", 0x000000, 0x080000, CRC(ff97f1cb) SHA1(defa249d46ae220f7bfa70746f5202bbbcc3e5fe) )

	ROM_REGION( 0x200000, "ymsnd:adpcmb", 0 )
	ROM_LOAD( "003.v21", 0x000000, 0x080000, CRC(d34960c6) SHA1(36d5877d5e42aab943f4d693159f4f3ad8b0addc) )
	ROM_LOAD( "003.v22", 0x080000, 0x080000, CRC(9a5f58d4) SHA1(2b580595e1820430a36f06fd3e0e0b8f7d686889) )
	ROM_LOAD( "003.v23", 0x100000, 0x080000, CRC(30f53e54) SHA1(22461f88a56d272b78dbc23204c0c6816200532b) )
	ROM_LOAD( "003.v24", 0x180000, 0x080000, CRC(5ba0f501) SHA1(ca02937a611a2c50c9e4b54f8fd4eaea09259894) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "003.c1", 0x000000, 0x80000, CRC(0315fbaf) SHA1(583c9253219c1026d81ee5e0cf5568683adc2633) )
	ROM_LOAD16_BYTE( "003.c2", 0x000001, 0x80000, CRC(b4c15d59) SHA1(b0d8ec967f9b8e5216301c10b2d36912abce6515) )
	ROM_LOAD16_BYTE( "003cd.c3",  0x100000, 0x80000, CRC(b09f1612) SHA1(03fbb5db4e377ce9cb4e65ddbc0b114c02e7bae1) )
	ROM_LOAD16_BYTE( "003cd.c4",  0x100001, 0x80000, CRC(150ea7a1) SHA1(13edc30144b56285ef37eb8aa6fb934704de18d8) )
	ROM_LOAD16_BYTE( "003.c5", 0x200000, 0x80000, CRC(9a7146da) SHA1(2fc83d13e3e9565919aab01bf2a1b028f433b547) )
	ROM_LOAD16_BYTE( "003.c6", 0x200001, 0x80000, CRC(1e63411a) SHA1(ee397e2f679042e87b37d95837af62bb95a72af9) )
	ROM_LOAD16_BYTE( "003.c7", 0x300000, 0x80000, CRC(2886710c) SHA1(1533dd935f0a8f92a0a3c47d1d2bc6d035454244) )
	ROM_LOAD16_BYTE( "003.c8", 0x300001, 0x80000, CRC(422af22d) SHA1(f67c844c34545de6ea187f5bfdf440dec8518532) )
ROM_END

ROM_START( trallycd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "038.p1", 0x000000, 0x080000, CRC(1e52a576) SHA1(a1cb56354c3378e955b0cd482c3c41ae15add952) )
	ROM_LOAD16_WORD_SWAP( "038cd.p2",  0x080000, 0x080000, CRC(9facb7fb) SHA1(96b4edbdddbd9ba642d0d046b33349c95559badd) )

	NEO_SFIX_128K( "038cd.s1", CRC(81022312) SHA1(bdb8ae4cd43f196f1b185a48e25980565226bb71) )

	NEO_BIOS_AUDIO_64K( "038cd.m1", CRC(2e1a89d6) SHA1(d0761c57f58e5a63b7c6a03538b3b5b7fe89271b) )

	ROM_REGION( 0x0e0000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "038cd.v1", 0x000000, 0x0e0000, CRC(f7ce806e) SHA1(83967145a6bd616ffe8c19dbf5b0bf63296f2c24) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD16_BYTE( "038cd.c1", 0x000000, 0x100000, CRC(840e6161) SHA1(553431723d0f348f4776b1e41beb2a4b39c2aeec) )
	ROM_LOAD16_BYTE( "038cd.c2", 0x000001, 0x100000, CRC(51979c7a) SHA1(833600da39daeae40ac700931e77898e9c60a45d) )
	ROM_LOAD16_BYTE( "038.c3", 0x200000, 0x080000, CRC(3bb7b9d6) SHA1(bc1eae6181ad5abf79736afc8db4ca34113d43f8) )
	ROM_LOAD16_BYTE( "038.c4", 0x200001, 0x080000, CRC(a4513ecf) SHA1(934aa103c226eac55157b44d7b4dfa35515322c3) )
ROM_END

ROM_START( zintrkcd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "211cd.p1", 0x000000, 0x100000, CRC(9a0bfe0a) SHA1(94299c51572b66fa37e3e496436299573b1faaa8) )

	NEO_SFIX_128K( "211cd.s1", CRC(56d16afa) SHA1(6e1f960a781f5ef1f858c51507fe573bead8ea66) )

	NEO_BIOS_AUDIO_64K( "211cd.m1", CRC(fcae1407) SHA1(5b4bff97a8c5930852eff6aee553eadc18e8f3d9) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "211cd.v1", 0x000000, 0x100000, CRC(781439da) SHA1(a80cdf3be55b5fc2ba1d167f69e222463d06ad88) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "zin-c1.bin", 0x000000, 0x200000, CRC(76aee189) SHA1(ad6929804c5b9a59aa609e6baebc6aa37e858a47) )
	ROM_LOAD16_BYTE( "zin-c2.bin", 0x000001, 0x200000, CRC(844ed4b3) SHA1(fb7cd057bdc6cbe8b78097dd124118bae7402256) )
ROM_END

 /*********
  HomeBrew
*************/

// 498: Abyssal Infants
// Bugs: Various minor control issues and spelling mistakes
ROM_START( abyssal )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "498.p1", 0x000000, 0x080000, CRC(ae12bd96) SHA1(299c66c7038edb9f8bac858172f8ce282cb89edf) )

	NEO_SFIX_128K( "498.s1", CRC(1ebbb83e) SHA1(4a52fe5463db19b0617fa990c9f2b8a006ac813c) )

	NEO_BIOS_AUDIO_128K( "498.m1", CRC(79b190e9) SHA1(e63232fba9fd1cb777059fac5aec41304b411212) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "498.v1", 0x000000, 0x200000, CRC(be46bf92) SHA1(4bf6b27dedba3321d9adf40543edf28e85a9f6ab) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "498.c1", 0x0000000, 0x200000, CRC(b8c84619) SHA1(1d634242281a7bf75979cd16ee5ae98b5b161b65) )
	ROM_LOAD16_BYTE( "498.c2", 0x0000001, 0x200000, CRC(376084b8) SHA1(b42e04c1168dd88a13d8690f0b5b5212457c558e) )
ROM_END

ROM_START( abyssal1 )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "498a.p1", 0x000000, 0x080000, CRC(a8a2a8a6) SHA1(da0ea757e17531be8c8e3b0a1f6cc71b0eb04b92) )

	NEO_SFIX_128K( "498.s1", CRC(1ebbb83e) SHA1(4a52fe5463db19b0617fa990c9f2b8a006ac813c) )

	NEO_BIOS_AUDIO_128K( "498a.m1", CRC(3ddf772b) SHA1(9ac9dba6feac48dcead44020cb17540bba6c0590) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "498a.v1", 0x000000, 0x200000, CRC(1fae3797) SHA1(2e3b410bc52366788b18f70ae5e912a8e2d5e93f) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "498a.c1", 0x0000000, 0x200000, CRC(24dabe27) SHA1(4b7519cbcf028b0be7b0acf9c8827a126a33007d) )
	ROM_LOAD16_BYTE( "498a.c2", 0x0000001, 0x200000, CRC(bbdacc24) SHA1(39025e7f593cc7f464e9f0403feab69ddbd371c8) )
ROM_END

// 497: Cabal
// Bugs: A few minor graphics issues
ROM_START( cabalng )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "497.p1", 0x000000, 0x100000, CRC(49232965) SHA1(f13352d5b853ea832eb751da508c7878fb149c20) )

	NEO_SFIX_128K( "497.s1", CRC(45f0bc5e) SHA1(de2533e4981c7597a768b8839c737a37243d4bdb) )

	NEO_BIOS_AUDIO_64K( "497.m1", CRC(efd97334) SHA1(139ef9da1fba0adcd4b41fbe6a2af0e094f33b05) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "497.v1", 0x000000, 0x100000, CRC(1a5bbc12) SHA1(3b4c74d943bd41189052313d41cd37b81e18ba25) )
	ROM_LOAD( "497.v2", 0x100000, 0x100000, CRC(a2b9c011) SHA1(6019d3b7bf78c509394765f2e8bfd5c91645d5c4) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "497.c1", 0x0000000, 0x100000, CRC(9f5ea8bb) SHA1(dbe5ebe37d720bba20fc68a948298aa96a11dc85) )
	ROM_LOAD16_BYTE( "497.c2", 0x0000001, 0x100000, CRC(edf277f2) SHA1(aa287598a620f03794e143500ff842dfb4b64d9a) )
ROM_END

// 497: Cabal
// Bugs: A few minor graphics issues
ROM_START( cabalng1 )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "497a.p1", 0x000000, 0x100000, CRC(bb193926) SHA1(e87473aaaa8c7af56148e86a410672870fa63d00) )

	NEO_SFIX_128K( "497.s1", CRC(45f0bc5e) SHA1(de2533e4981c7597a768b8839c737a37243d4bdb) )

	NEO_BIOS_AUDIO_64K( "497.m1", CRC(efd97334) SHA1(139ef9da1fba0adcd4b41fbe6a2af0e094f33b05) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "497.v1", 0x000000, 0x100000, CRC(1a5bbc12) SHA1(3b4c74d943bd41189052313d41cd37b81e18ba25) )
	ROM_LOAD( "497.v2", 0x100000, 0x100000, CRC(a2b9c011) SHA1(6019d3b7bf78c509394765f2e8bfd5c91645d5c4) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "497.c1", 0x0000000, 0x100000, CRC(9f5ea8bb) SHA1(dbe5ebe37d720bba20fc68a948298aa96a11dc85) )
	ROM_LOAD16_BYTE( "497.c2", 0x0000001, 0x100000, CRC(edf277f2) SHA1(aa287598a620f03794e143500ff842dfb4b64d9a) )
ROM_END

// 492 : Project Neon Caravan Edition Prealpha 0.4.19 (c) 2019
// Bugs: Insert Coin (first time) causes reboot
// First time: Use video option to rotate 90CCW
// This uses a .neo file: 0x1000 bytes for header, then p rom (word_swap), then remainder is normal
ROM_START( caravan )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "492.p1", 0x000000, 0x80000, CRC(f45cac3a) SHA1(21e283f5fa41d10f0c2bf1f9848bb8f10ea51ad5) )

	NEO_SFIX_128K( "492.s1", CRC(f32de862) SHA1(07215b0a974ce0dff5065698a9ec00b3ba75eeee) )

	NEO_BIOS_AUDIO_64K( "492.m1", CRC(6d24cf93) SHA1(5d408af31ce949a8e75c8706498043790a518589) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "492.v1", 0x000000, 0x100000, CRC(2823ca49) SHA1(09a9c52ad3be25c0e3edf380a219efb6d4c327b7) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD16_BYTE( "492.c1", 0x000000, 0x80000, CRC(87df580b) SHA1(5c5dd1fcca16f4bb98156d2ed52a403930843f53) )
	ROM_LOAD16_BYTE( "492.c2", 0x000001, 0x80000, CRC(7b854cc1) SHA1(df7084e1049c7b156cd17c02000d99dd37d679bb) )
ROM_END

// 410 : Codename: Blut Engel by Blastar (c) 2005
// Bugs: Insert Coin causes reboot
ROM_START( cnbe )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "410.p1", 0x000000, 0x080000, CRC(7ece4186) SHA1(fc4ed3b5ed551744542c2ff1e45a6e97c68eff88) )

	NEO_SFIX_64K( "410.s1", CRC(40a4698f) SHA1(be631408b261906f36c41c58c775c1a4c418a256) )

	NEO_BIOS_AUDIO_128K( "410.m1", CRC(a5821c9c) SHA1(81779f12bbb012bf910c484725779e03b07e44ec) )

	ROM_REGION( 0x80000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "410.v1", 0x000000, 0x080000, CRC(70191764) SHA1(7dff2122c32886a3626c0d7befc7e7c3961c6cee) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "410.c1", 0x000000, 0x100000, CRC(0f4fea6f) SHA1(2eeaa661272817dc205072cd63d8bffbe7d6fbec) )
	ROM_LOAD16_BYTE( "410.c2", 0x000001, 0x100000, CRC(3d5fc36f) SHA1(59c045bc5999ccd6c1413364a6cd337a858f599e) )
ROM_END

// 410 : Codename: Blut Engel by Blastar (c) 2018
// Bugs: Insert Coin causes reboot
// Seems original didn't work correctly on MVS, this fixes it. Makes no difference in emulation.
// This uses a .neo file: 0x1000 bytes for header, then p rom (word_swap), then remainder is normal
ROM_START( cnbe2018 )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "410.neo", 0x000000, 0x001000, CRC(d2c40244) SHA1(a3888dd1ff9168339afa58f7823c4944043678e0) ) // skip header
	ROM_CONTINUE(0x000000, 0x040000)
	ROM_IGNORE(0x0e0000)

	ROM_REGION(0x120000, "asis", 0)
	ROM_LOAD("410.neo", 0x000000, 0x001000, CRC(d2c40244) SHA1(a3888dd1ff9168339afa58f7823c4944043678e0) )
	ROM_CONTINUE(0x000000, 0x120000)

	NEO_SFIX_MT(0x10000)
	ROM_COPY("asis", 0x40000, 0x00000, 0x10000) // srctag, srcoffs, dstoffs, length

	NEO_BIOS_AUDIO_128K( "410.m1", CRC(a5821c9c) SHA1(81779f12bbb012bf910c484725779e03b07e44ec) ) // dummy, gets overwritten
	ROM_COPY("asis", 0x50000, 0x00000, 0x10000)

	ROM_REGION( 0x40000, "ymsnd:adpcma", 0 )
	ROM_COPY("asis", 0x60000, 0x00000, 0x40000)

	ROM_REGION( 0x80000, "sprites", 0 )
	ROM_COPY("asis", 0xa0000, 0x00000, 0x80000)
ROM_END

// 437 : Crouching Pony Hidden Dragon demo by Le Cortex
// If the game doesn't work, read the FAQ.
ROM_START( cphd )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "437.p1", 0x000000, 0x100000, CRC(de032a95) SHA1(5566ddbb17c8cc4016e25de1afb0ea5c281844ae) )
	ROM_LOAD16_WORD_SWAP( "437.p2", 0x100000, 0x800000, CRC(7a3a2e41) SHA1(a1bd9e20f29f283f892ed3d937b3a79a63d9a04b) )

	NEO_SFIX_128K( "437.s1", CRC(1736099a) SHA1(486bb9b5abd43d1739c717f0dd3aff0d6ed37ec0) )

	NEO_BIOS_AUDIO_64K( "437.m1", CRC(535a7397) SHA1(3752017175030b05a91078bdf0709af91dee5fc3) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "437.v1",     0x0000000, 0x1000000, CRC(04eb9c07) SHA1(226f6d6e0365613fb66671775a1f8e5ca62d0549) )
	ROM_IGNORE(0x1000000) // empty

	ROM_REGION( 0x1000000, "ymsnd:adpcma:adpcmb", 0 )
	ROM_LOAD( "437.v2",     0x0000000, 0x1000000, CRC(9c9aec7f) SHA1(dc54b4ea34724da5dc9e5b498a2b16d7f1ffc1b4) )
	ROM_IGNORE(0x1000000) // empty

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "437.c1", 0x0000000, 0x2000000, CRC(f3a4b475) SHA1(07a5e8c3a0a8e29f952e448d8eac772ccef6586e) )
	ROM_LOAD16_BYTE( "437.c2", 0x0000001, 0x2000000, CRC(05ce93a9) SHA1(a29f7ca6d0b3c53a0b2889e716b34fe921da432c) )
	// not used (blank)
	//ROM_LOAD16_BYTE( "437.c3", 0x4000000, 0x2000000, CRC(59450445) SHA1(57b587e1bf2d09335bdac6db18902d43dfe76449) )
	//ROM_LOAD16_BYTE( "437.c4", 0x4000001, 0x2000000, CRC(59450445) SHA1(57b587e1bf2d09335bdac6db18902d43dfe76449) )
ROM_END

// 404 : Columns by Neobitz
// No sound
ROM_START( columnsn )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "404.p1", 0x000000, 0x080000, CRC(c6c9888d) SHA1(5a2ec1071872c817bf82053ca7b7d5d63fab6755) )

	NEO_SFIX_128K( "404.s1", CRC(089a28a8) SHA1(b38b5c42eb909c57c16b016addffcd4e930806ce) )

	NEO_BIOS_AUDIO_64K( "407.m1", CRC(7669de64) SHA1(caa170b561df4f68000beaad41d942c66a4a10ee) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "407.v1", 0x000000, 0x080000, CRC(504bf849) SHA1(13a184ec9e176371808938015111f8918cb4df7d) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD16_BYTE( "404.c1", 0x000000, 0x80000, CRC(9a579cab) SHA1(9efd285c1bdc49a0d1daf2a062d0f906a0f5b542) )
	ROM_LOAD16_BYTE( "404.c2", 0x000001, 0x80000, CRC(91d14043) SHA1(de6a1178fbfa3d75285e4338967f0ce4ed1aff23) )
ROM_END

ROM_START( columnsncd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "404.p1", 0x000000, 0x080000, CRC(c6c9888d) SHA1(5a2ec1071872c817bf82053ca7b7d5d63fab6755) )

	NEO_SFIX_64K( "404a.s1", CRC(16cdb953) SHA1(a699f05fe9fb02a9bb0f03778578a5adcae00b91) )

	NEO_BIOS_AUDIO_64K( "407.m1", CRC(7669de64) SHA1(caa170b561df4f68000beaad41d942c66a4a10ee) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "407.v1", 0x000000, 0x080000, CRC(504bf849) SHA1(13a184ec9e176371808938015111f8918cb4df7d) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD16_BYTE( "404a.c1", 0x000000, 0x80000, CRC(cf503ff1) SHA1(3fb3131fa55d6137381b817dbb07b740096749b7) )
	ROM_LOAD16_BYTE( "404a.c2", 0x000001, 0x80000, CRC(c4d6e319) SHA1(19a5bb2622c01bea2c0eb2206724c7751caca318) )
ROM_END

// 415 : Frog Feast by Rastersoft
ROM_START( ffeast ) /* Frog Feast - Full Version */
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "415.p1", 0x000000, 0x080000, CRC(c26848da) SHA1(33737f8d2366b3a554ceb9ea2fcd85aaed75f344) )

	NEO_SFIX_128K( "415.s1", CRC(88f4cd13) SHA1(7f3b28c903ecf90478f2dcddf790714d7363aa2b) )

	NEO_BIOS_AUDIO_128K( "415.m1", CRC(c825b484) SHA1(7dea872ae39ef83981436aaf3c9b602ac8bec676) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "415.v1", 0x000000, 0x100000, CRC(2639da11) SHA1(4309e46014d623066d427ce3473542c99f678f86) )
	ROM_LOAD( "415.v2", 0x100000, 0x100000, CRC(e5eda58b) SHA1(ae203cfedf4b563da914939e0a4d7f4697070f82) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "415.c1", 0x000000, 0x100000, CRC(7b2f9fb3) SHA1(62deacf16c3b259422f962c9604b4efc2f32d91b) )
	ROM_LOAD16_BYTE( "415.c2", 0x000001, 0x100000, CRC(a7f18a6f) SHA1(1a277c79eaacf09d12a4b7c88421e7a6d6153503) )
ROM_END

// 447 : Hypernoid by M.Priewe.
ROM_START( hypernoid )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "447.p1", 0x000000, 0x100000, CRC(e024fa76) SHA1(6ef393ad80ec80e30929f07c95305d97fca3ad22) )

	NEO_SFIX_128K( "447.s1", CRC(bb82ab71) SHA1(307f420446c2d411a65b59543b61c21d0360536b) )

	NEO_BIOS_AUDIO_512K( "447.m1", CRC(6c8eaacc) SHA1(6bc065be18db6830a4c94b424f9380d38da6f8b7) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "447.v1", 0x000000, 0x400000, CRC(dafa1bdd) SHA1(743a5ad24a3dba04ce8f3e2d95ebd5ca83fd9f98) )
	ROM_LOAD( "447.v2", 0x400000, 0x400000, CRC(85ad8283) SHA1(8abcf48a353dcd4777608b13471608f7290d89a5) )
	ROM_LOAD( "447.v3", 0x800000, 0x400000, CRC(86c27f0c) SHA1(85b740e0224d5ea09b600683dec6fe532a723355) )
	ROM_LOAD( "447.v4", 0xc00000, 0x400000, CRC(a3982244) SHA1(7191909d7264df3dc417dc76cee53291986d84e9) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "447.c1", 0x000000, 0x200000, CRC(41d6140a) SHA1(862b95ca1fe2b75d7ead0de8ac50c1b8a049c774) )
	ROM_LOAD16_BYTE( "447.c2", 0x000001, 0x200000, CRC(36f35df2) SHA1(22715561d5383263e41563fcb060f83a0c544531) )
ROM_END

ROM_START( lhbb )  // Last Hope with Blue Bullets
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "802bb.p1", 0x000000, 0x100000, CRC(a5e6f24b) SHA1(d5a39d146982b4847e9008600f4ea9d38a1226e0) )

	NEO_SFIX_64K( "802.s1", CRC(0c0ff9e6) SHA1(c87d1ea8731ac1e63ab960b8182dd1043bcc10bb) )

	NEO_BIOS_AUDIO_128K( "802.m1", CRC(113c870f) SHA1(854425eb4be0d7fa088a6c3bf6078fdd011707f5) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "802.v1", 0x000000, 0x200000, CRC(b765bafe) SHA1(b2048c44089bf250c8dcfabb27c7981e9ee5002a) )
	ROM_LOAD( "802.v2", 0x200000, 0x200000, CRC(9fd0d559) SHA1(09e70d5e1c6e172a33f48feb3e442515c34a8f3d) )
	ROM_LOAD( "802.v3", 0x400000, 0x200000, CRC(6d5107e2) SHA1(4ba74836e3d0421a28af47d3d8341ac16af1d7d7) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "802.c1", 0x000000, 0x400000, CRC(53ef41b5) SHA1(a8f1fe546403b609e12f0df211c05d7ac479d98d) )
	ROM_LOAD16_BYTE( "802.c2", 0x000001, 0x400000, CRC(f9b15ab3) SHA1(d8ff2f43686bfc8c2f7ead3ef445e51c15dfbf16) )
	ROM_LOAD16_BYTE( "802.c3", 0x800000, 0x400000, CRC(50cc21cf) SHA1(0350aaef480c5fa12e68e540a4c974dbf5870add) )
	ROM_LOAD16_BYTE( "802.c4", 0x800001, 0x400000, CRC(8486ad9e) SHA1(19a2a73c825687e0cb9fd62bde00db91b5409529) )
ROM_END

// 802 : Last Hope CD Beta by NG:DEV.Team
// Bugs: Insert Coin causes reboot; purple boxes instead of graphics; some corrupt graphics
ROM_START( lhcdb )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "802cd.p1", 0x000000, 0x100000, CRC(83e7b181) SHA1(eb13909c0b062d56d20cbdfe75abf6139eae9ee0) )

	NEO_SFIX_128K( "802cd.s1", CRC(298495d6) SHA1(c217aba6c1916d2e5337bb5c17d979b11a53582e) )

	NEO_BIOS_AUDIO_128K( "802cd.m1", CRC(d9f6c153) SHA1(c08f7ca288be1c34f4b33ed13abd805b5cd66d4e) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "802cd.v1", 0x000000, 0x400000, CRC(de563ec3) SHA1(cd0f1a436cdac679792fc78906e718c78369b15a) )
	ROM_LOAD( "802cd.v2", 0x400000, 0x400000, CRC(93478033) SHA1(a03e0fcb7f51c66ec0bc5d164744db00b96973c2) )
	ROM_LOAD( "802cd.v3", 0x800000, 0x3c3500, CRC(f0ad87b8) SHA1(f992e84c6cbbc3cab79747a2ca4d646d18bebcbd) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "802cd.c1", 0x000000, 0x400000, CRC(554e6b73) SHA1(3637a8a4474e33eb75ac4a4ce0815f6a514fe337) )
	ROM_LOAD16_BYTE( "802cd.c2", 0x000001, 0x400000, CRC(7c84b0fc) SHA1(cbd7a7865113e4f21f2b1f990a077fa5c2eae894) )
	ROM_LOAD16_BYTE( "802cd.c3", 0x800000, 0x400000, CRC(28ec7555) SHA1(f094739272e6017a7193fa96cde3c1ed573a66b6) )
	ROM_LOAD16_BYTE( "802cd.c4", 0x800001, 0x400000, CRC(8b7c236b) SHA1(1cb3fe81f433a2180c85be935e340da3c55aafdb) )
ROM_END

ROM_START( lhcdba ) // v3,p1 rom are different, but same bugs as above
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "802cda.p1", 0x000000, 0x100000, CRC(0f7405d7) SHA1(3858564413be0bbbcb1c970de8f66bedc7d1ac6a) )

	NEO_SFIX_128K( "802cd.s1", CRC(298495d6) SHA1(c217aba6c1916d2e5337bb5c17d979b11a53582e) )

	NEO_BIOS_AUDIO_128K( "802cd.m1", CRC(d9f6c153) SHA1(c08f7ca288be1c34f4b33ed13abd805b5cd66d4e) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "802cd.v1", 0x000000, 0x400000, CRC(de563ec3) SHA1(cd0f1a436cdac679792fc78906e718c78369b15a) )
	ROM_LOAD( "802cd.v2", 0x400000, 0x400000, CRC(93478033) SHA1(a03e0fcb7f51c66ec0bc5d164744db00b96973c2) )
	ROM_LOAD( "802cda.v3", 0x800000, 0x400000, CRC(e0fc99ca) SHA1(6de935b54bf5adc4394fe824b001b38eca0291ad) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "802cd.c1", 0x000000, 0x400000, CRC(554e6b73) SHA1(3637a8a4474e33eb75ac4a4ce0815f6a514fe337) )
	ROM_LOAD16_BYTE( "802cd.c2", 0x000001, 0x400000, CRC(7c84b0fc) SHA1(cbd7a7865113e4f21f2b1f990a077fa5c2eae894) )
	ROM_LOAD16_BYTE( "802cd.c3", 0x800000, 0x400000, CRC(28ec7555) SHA1(f094739272e6017a7193fa96cde3c1ed573a66b6) )
	ROM_LOAD16_BYTE( "802cd.c4", 0x800001, 0x400000, CRC(8b7c236b) SHA1(1cb3fe81f433a2180c85be935e340da3c55aafdb) )
ROM_END

// 433 : Looptris by Blastar 2021-12-26
ROM_START( looptris )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "433.p1", 0x000000, 0x080000, CRC(8fcb5104) SHA1(6a0da5c4e72ef57600ecd15cba64e3871f48391e) )

	NEO_SFIX_128K( "433.s1", CRC(70e70448) SHA1(40461af534afcba341d2f14b755d6de353fe7afd) )

	NEO_BIOS_AUDIO_128K( "433.m1", CRC(e7105df8) SHA1(9f4efad6dcc8b9617d59576415019820e973f45c) )

	ROM_REGION( 0x80000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "433.v1", 0x000000, 0x080000, CRC(dfa63cd2) SHA1(bbf4a74a660f12cc037cfa0ac5c664988016ee45) )

	ROM_REGION( 0x100000, "sprites", ROMREGION_ERASEFF )
	ROM_LOAD16_BYTE( "433.c1", 0x000000, 0x080000, CRC(b9413f13) SHA1(5e7175dff9510dad55f8f05e9b307c3c05d92209) )
	ROM_LOAD16_BYTE( "433.c2", 0x000001, 0x080000, CRC(9409dbe8) SHA1(1e9562aa34f6202e8012104ab79916453fec072e) )
ROM_END

// 409 : Jonas Indiana and the Lost Temple of Ra by Blastar (c) 2005
// Bugs: Insert Coin causes reboot; You can climb into the ceiling and get stuck there; can't jump from one rope to another
ROM_START( ltorb )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "409.p1", 0x000000, 0x040000, CRC(353f6b05) SHA1(ae2ebb9a08e936a86cd09aaafda9e90826461bbf) )

	NEO_SFIX_64K( "409.s1", CRC(8224d8b7) SHA1(2e7b176e5dffd8a44fa813b928155801d80b1ee6) )

	NEO_BIOS_AUDIO_64K( "409.m1", CRC(6847fd52) SHA1(6e6d9045299966d41e3f193b3aff032d5b5e135d) )

	ROM_REGION( 0x80000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "409.v1", 0x000000, 0x080000, CRC(0329c2e7) SHA1(44c7f04d4e37fb5a06b0366d291f80c3a67a46f5) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD16_BYTE( "409.c1", 0x000000, 0x080000, CRC(8b607198) SHA1(23dc0b285518f3e80a8feab4d674d625e76e8896) )
	ROM_LOAD16_BYTE( "409.c2", 0x000001, 0x080000, CRC(6b96b59c) SHA1(a62600c337d7f6821ce56bdfd5c484f05c88187f) )
ROM_END

ROM_START( neonopon ) // v.0.2
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "407.p1", 0x000000, 0x080000, CRC(8a792271) SHA1(6f8db18f9ced0706cb2e4b5545da97be871352dd) )

	NEO_SFIX_64K( "407.s1", CRC(93e6fe7d) SHA1(791789c33eeeaa23fe6581db2f0ee3c35c73c052) )

	NEO_BIOS_AUDIO_64K( "407.m1", CRC(7669de64) SHA1(caa170b561df4f68000beaad41d942c66a4a10ee) )

	ROM_REGION( 0x080000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "407.v1", 0x000000, 0x080000, CRC(504bf849) SHA1(13a184ec9e176371808938015111f8918cb4df7d) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "407.c1", 0x000000, 0x100000, CRC(4a718ae3) SHA1(e59515bacd9065c4b2712710a6a9a647e42c31e6) )
	ROM_LOAD16_BYTE( "407.c2", 0x000001, 0x100000, CRC(0e2cbc25) SHA1(3c45eedb2efc6a3a7ec65487f980e117485abc9f) )
ROM_END

// 436 : Neo Pang by CeL
ROM_START( neopang )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "436.p1", 0x000000, 0x080000, CRC(dc5922ee) SHA1(08804fa9894b7e84375300acbdec8ea6829575d0) )

	NEO_SFIX_64K( "435.s1", CRC(d78bd9a0) SHA1(17a237166aede98bee27d5b52654414c8a1b071a) )

	NEO_BIOS_AUDIO_128K( "202.m1", CRC(9c0291ea) SHA1(3fa67c62acba79be6b3a98cc1601e45569fa11ae) )

	ROM_REGION( 0x80000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "202.v1", 0x000000, 0x80000, CRC(debeb8fb) SHA1(49a3d3578c087f1a0050168571ef8d1b08c5dc05) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "436.c1", 0x000000, 0x100000, CRC(62f5405c) SHA1(f9eb8d1838da9953aecf40c3314c608ab655cb8f) )
	ROM_LOAD16_BYTE( "436.c2", 0x000001, 0x100000, CRC(e1183030) SHA1(60262d53ab12314db5e5c00a94463500abe3e8b0) )
ROM_END

// 469 : Neo Pong by Neodev (c) 2002
// MAME bug : On the title screen, there's a vertical blank area that slowly moves from left to right
ROM_START( neopong ) // v1.1
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "469.p1", 0x000000, 0x020000, CRC(9f35e29d) SHA1(261ce9305950debbc2fe088a45ab0fa83d6cf10d) )

	NEO_SFIX_128K( "469.s1", CRC(cd19264f) SHA1(531be2305cd56d332fb7a53ab924214ade34a9e8) )

	NEO_BIOS_AUDIO_128K( "469.m1", CRC(78c851cb) SHA1(a9923c002e4e2171a564af45cff0958c5d57b275) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "469.v1", 0x000000, 0x200000, CRC(6c31223c) SHA1(ede3a2806d7d872a0f737626a23ecce200b534e6) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "469.c1", 0x000000, 0x100000, CRC(f5a57d1a) SHA1(781170ae439f48fcbcee6af4cb3a1367dbb70498) )
	ROM_LOAD16_BYTE( "469.c2", 0x000001, 0x100000, CRC(affde64e) SHA1(25ba8b4f6f961027d97d35f13cebeaee2dbb6f5a) )
ROM_END

ROM_START( neoponga ) // v1.0, has no sound, does not satisfy the watchdog
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "469a.p1", 0x000000, 0x020000, CRC(31b724d7) SHA1(e374613609aeda64b547d8ce38d2078b6ed55ad5) )

	NEO_SFIX_128K( "469.s1", CRC(cd19264f) SHA1(531be2305cd56d332fb7a53ab924214ade34a9e8) )

	NEO_BIOS_AUDIO_128K( "202.m1", CRC(9c0291ea) SHA1(3fa67c62acba79be6b3a98cc1601e45569fa11ae) )

	ROM_REGION( 0x80000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "202.v1", 0x000000, 0x80000, CRC(debeb8fb) SHA1(49a3d3578c087f1a0050168571ef8d1b08c5dc05) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "469a.c1", 0x000000, 0x100000, CRC(d7587282) SHA1(6fbc317dede78265dc4cfd2a6d79968320b8fd50) )
	ROM_LOAD16_BYTE( "469a.c2", 0x000001, 0x100000, CRC(fefc9d06) SHA1(f191bcd3683a184b5a7d6046156e0b2bca231e95) )
ROM_END

// 419 : Neo Thunder demo by Sebastian Mihai
// No sound
ROM_START( neothund )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "419.p1", 0x000000, 0x100000, CRC(f7050757) SHA1(b73009050905ad2b1f06690e0106e59fb5ede86b) )

	NEO_SFIX_128K( "419.s1", CRC(a545b593) SHA1(09077b63595eebb7dddd55e041e7786164df0ead) )

	NEO_BIOS_AUDIO_128K( "202.m1", CRC(9c0291ea) SHA1(3fa67c62acba79be6b3a98cc1601e45569fa11ae) )

	ROM_REGION( 0x80000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "202.v1", 0x000000, 0x80000, CRC(debeb8fb) SHA1(49a3d3578c087f1a0050168571ef8d1b08c5dc05) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "419.c1", 0x000000, 0x100000, CRC(48b9126e) SHA1(38bf1296c3d8762372d4eab785f34507a4f8776c) )
	ROM_LOAD16_BYTE( "419.c2", 0x000001, 0x100000, CRC(214df62e) SHA1(21e4ce2a0ac636081c9e07a294cb44987692039e) )
ROM_END

// 491 : Neotris by Totologic
// Bugs: Pressing 1 will reboot the game and can corrupt the right-hand side of the title
ROM_START( neotrisd1 )
	ROM_REGION( 0x100000, "maincpu", ROMREGION_ERASEFF )
	ROM_LOAD16_WORD_SWAP( "491.p1", 0x000000, 0x080000, CRC(6a253ce9) SHA1(b9a3949dcd7e7dd3cd8b4e739ce2c913c16435b1) )

	NEO_SFIX_128K( "491.s1", CRC(7a30a592) SHA1(3d7fd159fafaf20b12388849e4c54192ce410fe8) )

	NEO_BIOS_AUDIO_64K( "491.m1", CRC(7a38ff47) SHA1(084cdf9dea053126783a4f570a56cc2444529f44) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "491.v1", 0x000000, 0x300000, CRC(95b3b726) SHA1(d0c361a78e509b083243e5f3a4b89bbaa658216e) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "491.c1", 0x000000, 0x100000, CRC(d53e8069) SHA1(55a9bb30fe1ce0abd9ebe54fa806992b2a790f28) )
	ROM_LOAD16_BYTE( "491.c2", 0x000001, 0x100000, CRC(61143d05) SHA1(093e0c819ee7884786c029e4a0da9e779f11db02) )
ROM_END

ROM_START( neotrisd2 )
	ROM_REGION( 0x100000, "maincpu", ROMREGION_ERASEFF )
	ROM_LOAD16_WORD_SWAP( "491a.p1", 0x000000, 0x080000, CRC(33a71f8d) SHA1(f4fe090b30193da3dce895fd9f75e94372d9b8c9) )

	NEO_SFIX_128K( "491a.s1", CRC(6809043a) SHA1(31efdd2bd0713d7a87f2c6dc92e43f312f8d8626) )

	NEO_BIOS_AUDIO_64K( "491a.m1", CRC(2f9f8265) SHA1(4bf718f428f8c0ce8b1d0005ea8b425a7729f622) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "491a.v1", 0x000000, 0x400000, CRC(9855b179) SHA1(e92b8373f4251a4a05da92483dc6c2d8b699f7f1) )
	ROM_LOAD( "491a.v2", 0x400000, 0x400000, CRC(b187368b) SHA1(9d0fa6ed14e87d9c38ed07ba8762c795dd3bb905) )
	ROM_LOAD( "491a.v3", 0x800000, 0x400000, CRC(5506b016) SHA1(181235f7b8792dd931ab00540d611221caaf0578) )
	ROM_LOAD( "491a.v4", 0xc00000, 0x400000, CRC(6bb8a938) SHA1(3d27cd2bdfc624b3ea4dfa79bc8c615eb34d612a) )

	ROM_REGION( 0x1800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "491a.c1", 0x000000, 0x400000, CRC(7f9c1a22) SHA1(633918addc8c2b22f55fb9c8b85edc4fc96c9753) )
	ROM_LOAD16_BYTE( "491a.c2", 0x000001, 0x400000, CRC(4896e921) SHA1(4abf2a36f1117a02bbf14859e3351a1ac5db9c53) )
	ROM_LOAD16_BYTE( "491a.c3", 0x800000, 0x400000, CRC(e8e2fcc3) SHA1(7fff344a476857460129a303ce680822d270a79a) )
	ROM_LOAD16_BYTE( "491a.c4", 0x800001, 0x400000, CRC(ec219a96) SHA1(f150d4956d32f204b51c0adf5db434d2ed258638) )
	ROM_LOAD16_BYTE( "491a.c5", 0x1000000, 0x400000, CRC(b8873b09) SHA1(4aed67ac2fac387dfaf7e0f78e127cdc98078c1d) )
	ROM_LOAD16_BYTE( "491a.c6", 0x1000001, 0x400000, CRC(fb994623) SHA1(198dddc5e7531d6fd2f7405243671d67e80fe26e) )
ROM_END

ROM_START( neotrisd3 )
	ROM_REGION( 0x100000, "maincpu", ROMREGION_ERASEFF )
	ROM_LOAD16_WORD_SWAP( "491b.p1", 0x000000, 0x080000, CRC(4cd619cf) SHA1(081a7819c71171a37f10d1b20f8887ca90df49a8) )

	NEO_SFIX_128K( "491a.s1", CRC(6809043a) SHA1(31efdd2bd0713d7a87f2c6dc92e43f312f8d8626) )

	NEO_BIOS_AUDIO_64K( "491b.m1", CRC(5a63bb9d) SHA1(de024be2535253d6846c380d05717002c0cc032d) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "491b.v1", 0x000000, 0x400000, CRC(fef16eb4) SHA1(64021cf913c4594d27d0602afc28754f0b76091f) )
	ROM_LOAD( "491b.v2", 0x400000, 0x400000, CRC(f0d28e19) SHA1(e47318bf3b5ef1d9e08928eb7f7ca7dfc15ab2e5) )
	ROM_LOAD( "491b.v3", 0x800000, 0x400000, CRC(fc652c8b) SHA1(a76040eef8dd76da3657bc39b6b5c3dded539829) )
	ROM_LOAD( "491b.v4", 0xc00000, 0x400000, CRC(c25764ca) SHA1(ee0f2fa8db2da5c95b94c062bff8ee37ec2b2c7d) )

	ROM_REGION( 0x1800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "491b.c1", 0x000000, 0x400000, CRC(e1c8eca9) SHA1(be1babdc0ae0fd9916e8335c1635148e0498a961) )
	ROM_LOAD16_BYTE( "491b.c2", 0x000001, 0x400000, CRC(11ca6e64) SHA1(166c1f973f4fd7f472c3ddd37e0eb945c36d7454) )
	ROM_LOAD16_BYTE( "491b.c3", 0x800000, 0x400000, CRC(1d9e2046) SHA1(c2415775170455bd44e19e7c7c8e10817da56385) )
	ROM_LOAD16_BYTE( "491b.c4", 0x800001, 0x400000, CRC(9091e795) SHA1(59e7a751633ce8f3db138fc818e50003da4582dc) )
	ROM_LOAD16_BYTE( "491b.c5", 0x1000000, 0x400000, CRC(bf278afe) SHA1(e7f84cb325dd4535accd44d84f61c53cb4bab312) )
	ROM_LOAD16_BYTE( "491b.c6", 0x1000001, 0x400000, CRC(8eb17e24) SHA1(7977475bf19073b8bc38fcb88be9226453c7d6e4) )
ROM_END

// 494 : Bonus Stage by Totologic
ROM_START( bonusstage )
	ROM_REGION( 0x100000, "maincpu", ROMREGION_ERASEFF )
	ROM_LOAD16_WORD_SWAP( "494.p1", 0x000000, 0x080000, CRC(de637e0b) SHA1(08f902bca19c815e7c69a0b9d3e5366eb82b944c) )

	NEO_SFIX_128K( "494.s1", CRC(a12d8990) SHA1(969db205d77cc80a1ebb88be6a265112142533ec) )

	NEO_BIOS_AUDIO_64K( "494.m1", CRC(dee563b2) SHA1(75e0fca36e8c23922ed9b54942ec11170b9b505a) )

	ROM_REGION( 0x400000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "494.v1", 0x000000, 0x400000, CRC(87bdd5fa) SHA1(e7ccc9a56aeaf1f4f79d2265fc5f19a0894dd96b) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD16_BYTE( "494.c1", 0x000000, 0x400000, CRC(bfe4eb8d) SHA1(e03ccfc50cf4813833a23b152bc0e47f453532a4) )
	ROM_LOAD16_BYTE( "494.c2", 0x000001, 0x400000, CRC(41fab784) SHA1(9d86d1362ed3981b9dedbd0bc9707a515260ce25) )
ROM_END

// 496: Neo Black Tiger
// Bugs: after playing for a while, graphics bugs appear, followed by getting stuck in areas, then total screen corruption, and finally it resets.
// Even though you can collect coins, there's no point score.
// The time bonus does nothing.
// You can only die by falling down a hole, whereupon the game restarts.
// Can't exit the stage at the end.
// Various sounds are missing. There's a loud pop every few minutes.
ROM_START( nblktiger )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "496.p1", 0x000000, 0x100000, CRC(18f34200) SHA1(78b3b9ef20ddf780a81e644d996d56dd5c0e6d10) )

	NEO_SFIX_128K( "419.s1", CRC(a545b593) SHA1(09077b63595eebb7dddd55e041e7786164df0ead) )

	NEO_BIOS_AUDIO_64K( "496.m1", CRC(2037dc19) SHA1(c88588d07fc63aeed828a87f0f633c7badafeb3e) )

	ROM_REGION( 0x200000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "496.v1", 0x000000, 0x100000, CRC(3ac066e1) SHA1(cab7f04fbce0db685f5fa0d22923f7b7ca37a804) )
	ROM_LOAD( "496.v2", 0x100000, 0x100000, CRC(c5a12987) SHA1(71236afffdb69aa3ba8ebc345e1e7b1830db437e) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "496.c1", 0x0000000, 0x800000, CRC(aa469494) SHA1(fd98b7445c85174ccb745c74cb9e852b08353324) )
	ROM_LOAD16_BYTE( "496.c2", 0x0000001, 0x800000, CRC(fa07ba1e) SHA1(8c00be2c0c1402789011e2aa272e04e216fdac10) )
ROM_END

// 411 : NGEM2K by Blastar (c) 2006
// No sound
// Bugs: Insert Coin causes reboot
ROM_START( ngem2k )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "411.p1", 0x000000, 0x080000, CRC(f2c42fe3) SHA1(fcd7453019ad21ecf77999a60b6792fc8d72d409) )

	NEO_SFIX_64K( "411.s1", CRC(fb3c02d2) SHA1(961cf3cfd56e9ace059265f0ff4c283289972938) )

	NEO_BIOS_AUDIO_128K( "411.m1", CRC(b1f44a15) SHA1(a1d7b498430b713b15ce886bac2ea473adadfb0c) )

	ROM_REGION( 0x80000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "411.v1", 0x000000, 0x080000, CRC(c32199f0) SHA1(2e17a6736c27d703c64d58fdc1b43edd8bb36d35) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "411.c1", 0x000000, 0x100000, CRC(a8e2ab47) SHA1(69a6ee8f659a63600a48e31b10782fba263e32e2) )
	ROM_LOAD16_BYTE( "411.c2", 0x000001, 0x100000, CRC(a738ea1c) SHA1(3b71f43ff30f4b15b5cd85dd9e95ebc7e84eb5a3) ) // all zeroes
ROM_END

// 418 : Tetris by Crim
ROM_START( ngtetris )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "418.p1", 0x000000, 0x80000, CRC(3465569a) SHA1(51506d549fa048581321fc39403c0a3bf8f77467) )

	NEO_SFIX_128K( "419.s1", CRC(a545b593) SHA1(09077b63595eebb7dddd55e041e7786164df0ead) )

	NEO_BIOS_AUDIO_128K( "418.m1", CRC(6b3703c6) SHA1(6fa41b713f03e0957f410a387aa896e7d924acb2) )

	ROM_REGION( 0x80000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "418.v1", 0x000000, 0x80000, CRC(2be8e290) SHA1(198cff1b1d70f7d05344d6ab38a4354f993dc4b8) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "418.c1", 0x000000, 0x80000, CRC(acc6d1d4) SHA1(1f6ad8578d8edaa22a35ad58dc76de8543a96db9) )
	ROM_LOAD16_BYTE( "418.c2", 0x000001, 0x80000, CRC(7ec06ab5) SHA1(3a8503be7f14d451f5ae964888b385334c12e8c6) )
ROM_END

// 495: New! Super Mario Brothers
// Bugs: Even though you can collect coins, there's no point score.
ROM_START( nsmb )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "495.p1", 0x000000, 0x100000, CRC(9e0fded1) SHA1(333da236947c440e10e69ee70b8e99a818488f1d) )

	NEO_SFIX_128K( "419.s1", CRC(a545b593) SHA1(09077b63595eebb7dddd55e041e7786164df0ead) )

	NEO_BIOS_AUDIO_64K( "495.m1", CRC(3c99e181) SHA1(7f827b65f5c170d95cd3dd14d644ea92e104a268) )

	ROM_REGION( 0x300000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "495.v1", 0x000000, 0x100000, CRC(d1e4fc94) SHA1(03bf016533b08eac16f1e8a368ab6422d4163364) )
	ROM_LOAD( "495.v2", 0x100000, 0x100000, CRC(7d42fab3) SHA1(242288e91790818f130d7ddacbf68f5bf2d993be) )
	ROM_LOAD( "495.v3", 0x200000, 0x100000, CRC(806b797d) SHA1(24b4951991afea6d81a55901320cf6f532713b16) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "495.c1", 0x0000000, 0x800000, CRC(f187934c) SHA1(72c7f23e45febb94fc89c01ffb475ae9c4b8fff3) )
	ROM_LOAD16_BYTE( "495.c2", 0x0000001, 0x800000, CRC(7ecfc8bb) SHA1(2d61e86ccfe9e92dcc400efba63f91fd2e77e251) )
ROM_END

// 443 : Santaball by M.Priewe.
// Press 1 to play a game of Pong.
// If the game misbehaves, read the FAQ.
ROM_START( santabll )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "443.p1", 0x000000, 0x100000, CRC(2af7a77c) SHA1(ff79d4695e8060f5a7b981524303336a0ad99c0c) )

	NEO_SFIX_128K( "443.s1", CRC(ac031928) SHA1(7516593efc70e6effed8f5423e9736d6555b3baf) )

	NEO_BIOS_AUDIO_64K( "443.m1", CRC(37a8d679) SHA1(957de2aa1775502a51b4e2d5cb6268cee00f6c2a) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "443.v1", 0x000000, 0x100000, CRC(d0150804) SHA1(b3d4cdb6d0f426de3801eb04d56f867bec8fe611) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "443.c1", 0x000000, 0x100000, CRC(1e271a9b) SHA1(5cae43aa094d5ee34983bc70aeab06652a6b0e7f) )
	ROM_LOAD16_BYTE( "443.c2", 0x000001, 0x100000, CRC(1c7fd396) SHA1(aa2e2fff1ad1804631f3058b9666b970a368a847) )
ROM_END

// 444 : Sea Fighter by kl3mousse.
// Neogeo logo is corrupt
ROM_START( seafight )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "444.p1", 0x000000, 0x100000, CRC(598d14ef) SHA1(da6dda92ec8cf3a5f46fae2dd4578f945f7a8ec7) )

	NEO_SFIX_128K( "444.s1", CRC(c46cf6b1) SHA1(6785e9dad6dbe339f7d8ab0d3852fb6df036c737) )

	NEO_BIOS_AUDIO_64K( "444.m1", CRC(16adbe82) SHA1(88c8fbe61735c41adffb0598e6311547a739f4d5) )

	ROM_REGION( 0x100000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "444.v1", 0x000000, 0x100000, CRC(becc781e) SHA1(a5a3ed13de539ce55c4f35bb052ee35ffe29fb5d) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "444.c1", 0x000000, 0x100000, CRC(383a9dde) SHA1(6d54c6389f9f992c1654643a537c01fda9b83259) )
	ROM_LOAD16_BYTE( "444.c2", 0x000001, 0x100000, CRC(1f43c1f4) SHA1(aa0cd4eebb02225b939f57cee4347c0a43654d31) )
ROM_END

ROM_START( teotb ) // Beta 3, 2022-03-12
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "323f.p1", 0x000000, 0x100000, CRC(2af068c0) SHA1(82f5885fbfdef47c0e9416cf9bd9accf8e5a739d) )
	ROM_LOAD16_WORD_SWAP( "323f.p2", 0x100000, 0x800000, CRC(3ddc321d) SHA1(496573202a417d40894f69c2044ef408d3a0f01b) )

	NEO_SFIX_128K( "323e.s1", CRC(52895190) SHA1(d11385c51591b685c533a9f27c4fd3aa62927bef) )

	NEO_BIOS_AUDIO_64K( "323f.m1", CRC(5edaa24d) SHA1(90209de31a87da4118600be64869b36067d76c4b) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "323f.v1",   0x000000, 0x800000, CRC(70042574) SHA1(368e85d38a94238b61969ee564f94bef143b808d) )
	ROM_LOAD( "323f.v2",   0x800000, 0x800000, CRC(d84d05b2) SHA1(7ad3914b5e95572d3fc9dadc6ad0e23463983118) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "323f.c1",   0x0000000, 0x1000000, CRC(360e5362) SHA1(a86a5eea49218669c5e00a6b286a7d2d6f02ab3c) )
	ROM_LOAD16_BYTE( "323f.c2",   0x0000001, 0x1000000, CRC(1fdff0ce) SHA1(4ef77f3e01d58612e9b730426adb81d87ccb5572) )
ROM_END

// 422 : Time's UP! by NGF
ROM_START( timesup )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "422.p1", 0x000000, 0x100000, CRC(b4be3ede) SHA1(95a9b87e674cc3af0932f5dab51d1e8e3d84385b) )

	NEO_SFIX_128K( "419.s1", CRC(a545b593) SHA1(09077b63595eebb7dddd55e041e7786164df0ead) )

	NEO_BIOS_AUDIO_128K( "422.m1", CRC(8b83308b) SHA1(b6b48689a0138af35375f741620e2569125a93e8) )

	ROM_REGION( 0x600000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "422.v1", 0x000000, 0x200000, CRC(1b48708b) SHA1(ac4e363a0b5988496272092ea4dc7c2259f9f1e3) )
	ROM_LOAD( "422.v2", 0x200000, 0x200000, CRC(6b17df84) SHA1(b8233110f91ef408f68beda641da01d2896109da) )
	ROM_LOAD( "422.v3", 0x400000, 0x200000, CRC(6c798d46) SHA1(7f91f5dbe58a2bceb8a9ed6394eb6b11a9ae7d97) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "422.c1", 0x000000, 0x200000, CRC(1c83fc38) SHA1(74a6c9116443a673ff49b2fe4d7b8bc79eadec0c) )
	ROM_LOAD16_BYTE( "422.c2", 0x000001, 0x200000, CRC(2b3f48b4) SHA1(5d05d312d06e387fa532f71f5144347a0dd77bb3) )
ROM_END

// 422 : Time's UP! demo by NGF
ROM_START( timesupd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "422d.p1", 0x000000, 0x200000, CRC(be86adb1) SHA1(4b363bab51dfc43b2302956f79a0b1d5202339ac) )

	NEO_SFIX_128K( "419.s1", CRC(a545b593) SHA1(09077b63595eebb7dddd55e041e7786164df0ead) )

	NEO_BIOS_AUDIO_128K( "422d.m1", CRC(fe795d11) SHA1(53ba44f2197aa700229f18dee6513bc0c2619904) )

	ROM_REGION( 0x800000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "422d.v1", 0x000000, 0x400000, CRC(13b8f47b) SHA1(4f0384101f9f6fce8c86a27a11a2b9d43a84a154) )
	ROM_LOAD( "422d.v2", 0x400000, 0x400000, CRC(6fdd663d) SHA1(9667f11b4350285d0722c67052ff4e9a63a3409f) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "422d.c1", 0x000000, 0x200000, CRC(c19a300a) SHA1(3ab4ec4b10583257b92f5a989434db89f8130626) )
	ROM_LOAD16_BYTE( "422d.c2", 0x000001, 0x200000, CRC(fdb3f7ed) SHA1(dd1d69515e58e9fba8cefb1c4cd808dfea0475d9) )
ROM_END

// 316 : Treasure of the Caribbean
ROM_START( totc )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "316.p1", 0x000000, 0x100000, CRC(99604539) SHA1(88d5f4fe56516aa36496cafd2508f6864118f1e2) )

	NEO_SFIX_128K( "248.s1", CRC(0a3fee41) SHA1(0ab2120e462086be942efcf6ffb37f58ea966ca3) )

	NEO_BIOS_AUDIO_128K( "316.m1", CRC(18b23ace) SHA1(d55495f3d8bb5568c8f2322763278a86ba5297b3) )

	ROM_REGION( 0x500000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "316.v1", 0x000000, 0x200000, CRC(15c7f9e6) SHA1(c51328a92dc7c612fd6c2f3841caee4fbd120f36) )
	ROM_LOAD( "316.v2", 0x200000, 0x200000, CRC(1b264559) SHA1(50c28858304e51cdc60f425483a1d1d2bbfb2f8d) )
	ROM_LOAD( "316.v3", 0x400000, 0x100000, CRC(84b62c5d) SHA1(30d7f2e16c6d602cebce5e9b4b8a5b2bde20af58) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "316.c1", 0x000000, 0x200000, CRC(cdd6600f) SHA1(85649c199b32db7553012cb5a058a92bbbb7355a) )
	ROM_LOAD16_BYTE( "316.c2", 0x000001, 0x200000, CRC(f362c271) SHA1(4a2efa043cd2553ff7039cb18a1dba8b41493be7) )
ROM_END

ROM_START( xeno )
	ROM_REGION( 0x200000, "maincpu", ROMREGION_ERASEFF )
	ROM_LOAD16_WORD_SWAP( "810.p1", 0x000000, 0x100000, CRC(637605a6) SHA1(179ebcdeaac3e561fd7acb72022eda8c3c74cb8a) )
	ROM_LOAD16_WORD_SWAP( "810.p2", 0x100000, 0x100000, CRC(84838145) SHA1(c1f48d333dfc85b9371f811dd449a42d8cdecf3f) )

	NEO_SFIX_128K( "810.s1", CRC(7537ea79) SHA1(b7242a6dd7b2ad8ccf7a223c08d626abf013f366) )

	NEO_BIOS_AUDIO_64K( "810.m1", CRC(28c13ed9) SHA1(a3c8cf36906293a24f1ed49376c9d561560d2730) )

	ROM_REGION( 0x1000000, "ymsnd:adpcma", 0 )
	ROM_LOAD( "810.v1", 0x000000, 0x1000000, CRC(60d57867) SHA1(e1f3f759b4af4404f19dd5b75135e6968b6be3c5) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_BYTE( "810.c1", 0x000000, 0x200000, CRC(ae51ef89) SHA1(da82214263a99520364a2b7ab8140bdc68940f6d) )
	ROM_LOAD16_BYTE( "810.c2", 0x000001, 0x200000, CRC(a8610100) SHA1(aded6eaa17a518a8f4af9c3779c41ef8dd32a316) )
ROM_END

/*************************************
 *
 *  Title catalog
 *  (source: http://neogeomuseum.snkplaymore.co.jp/english/catalogue/index.php)
 *
 *************************************

    In 2010, SNK Playmore, the successor of SNK, released a title catalogue which lists the released
    games (MVS/AES/CD) including their release dates in Japan. It is not 100% complete.
    The included title catalogue is the english one.

    Game Title                                                  Genre           Publisher       Date Released (in Japan)
    =================================================================================================================================
    NAM-1975                                                    3D Action       SNK             MVS Cartridge:1990/04/26
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1994/09/09
    MAHJONG KYORETSUDEN                                         Mahjong         SNK             MVS Cartridge:1990/04/26
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1994/09/09
    MAGICIAN LORD                                               Action          ADK             MVS Cartridge:1990/04/26
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1994/10/31
    BASEBALL STARS PROFESSIONAL                                 Sports          SNK             MVS Cartridge:1990/04/26
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1995/04/21
    TOP PLAYER'S GOLF                                           Sports          SNK             MVS Cartridge:1990/05/23
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1994/09/09
    NINJA COMBAT                                                Action          ADK             MVS Cartridge:1990/07/24
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1994/10/31
    RIDING HERO                                                 3D Racing       SNK             MVS Cartridge:1990/07/24
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1995/05/26
    THE SUPER SPY                                               3D Action       SNK             MVS Cartridge:1990/10/08
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1994/09/09
    CYBER-LIP                                                   Action          SNK             MVS Cartridge:1990/11/07
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1995/04/21
    PUZZLED                                                     Puzzle          SNK             MVS Cartridge:1990/11/20
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1994/09/09
    LEAGUE BOWLING                                              Sports          SNK             MVS Cartridge:1990/12/10
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1994/09/09
    GHOST PILOTS                                                Shooter         SNK             MVS Cartridge:1991/01/25
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1995/03/17
    SENGOKU                                                     Action          SNK             MVS Cartridge:1991/02/12
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1995/03/17
    KING OF THE MONSTERS                                        Fighting        SNK             MVS Cartridge:1991/02/25
                                                                                                NEOGEO ROM-cart:1991/07/01
    BLUE'S JOURNEY                                              Action          ADK             MVS Cartridge:1991/03/14
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1994/10/31
    ALPHA MISSION II                                            Shooter         SNK             MVS Cartridge:1991/03/25
                                                                                                NEOGEO ROM-cart:1991/07/01
                                                                                                NEOGEO CD:1994/09/09
    BURNING FIGHT                                               Action          SNK             MVS Cartridge:1991/05/20
                                                                                                NEOGEO ROM-cart:1991/08/09
                                                                                                NEOGEO CD:1994/09/09
    MINNASAN NO OKAGESAMA DESU                                  Table           Monolith        MVS Cartridge:1991/07/25
                                                                                                NEOGEO ROM-cart:1991/07/21
    CROSSED SWORDS                                              Action          ADK             MVS Cartridge:1991/07/25
                                                                                                NEOGEO ROM-cart:1991/10/01
                                                                                                NEOGEO CD:1994/10/31
    LEGEND OF SUCCESS JOE                                       Action          Wave            MVS Cartridge:1991/07
                                                                                                NEOGEO ROM-cart:1991/08/30
    QUIZ DAISUSA SEN: THE LAST COUNT DOWN                       Quiz            SNK             MVS Cartridge:1991/07
                                                                                                NEOGEO ROM-cart:1991/08/30
    SUPER BASEBALL 2020                                         Sports          SNK             MVS Cartridge:1991/09/20
                                                                                                NEOGEO ROM-cart:1991/10/25
                                                                                                NEOGEO CD:1995/02/25
    ROBO ARMY                                                   Action          SNK             MVS Cartridge:1991/10/30
                                                                                                NEOGEO ROM-cart:1991/12/20
                                                                                                NEOGEO CD:1995/04/21
    THRASH RALLY                                                Racing          ADK             MVS Cartridge:1991/11/08
                                                                                                NEOGEO ROM-cart:1991/12/20
                                                                                                NEOGEO CD:1994/10/31
    EIGHT MAN                                                   Action          SNK             NEOGEO ROM-cart:1991/11/20
    FATAL FURY                                                  Fighting        SNK             MVS Cartridge:1991/11/25
                                                                                                NEOGEO ROM-cart:1991/12/20
                                                                                                NEOGEO CD:1994/09/09
    BAKATONO-SAMA MAHJONG MAN'YUKI                              Mahjong         Monolith        MVS Cartridge:1991/11
                                                                                                NEOGEO ROM-cart:1991/12/13
    THRASH RALLY                                                Racing          ADK             NEOGEO ROM-cart:1991/12/20
    FOOTBALL FRENZY                                             Sports          SNK             MVS Cartridge:1992/01/31
                                                                                                NEOGEO ROM-cart:1992/02/21
                                                                                                NEOGEO CD:1994/09/09
    SOCCER BRAWL                                                Sports          SNK             MVS Cartridge:1992/02/14
                                                                                                NEOGEO ROM-cart:1992/03/13
                                                                                                NEOGEO CD:1995/03/31
    MUTATION NATION                                             Action          SNK             MVS Cartridge:1992/03/16
                                                                                                NEOGEO ROM-cart:1992/04/17
                                                                                                NEOGEO CD:1995/02/25
    LAST RESORT                                                 Shooter         SNK             MVS Cartridge:1992/03/23
                                                                                                NEOGEO ROM-cart:1992/04/24
                                                                                                NEOGEO CD:1994/09/09
    QUIZ MEITANTEI NEO & GEO: QUIZ DAISOUSASEN PART 2           Quiz            SNK             MVS Cartridge:1992/03
                                                                                                NEOGEO ROM-cart:1991/04/24
    BASEBALL STARS 2                                            Sports          SNK             MVS Cartridge:1992/04/15
                                                                                                NEOGEO ROM-cart:1992/04/28
                                                                                                NEOGEO CD:1994/09/09
    NINJA COMMANDO                                              Shooter         ADK             MVS Cartridge:1992/04/30
                                                                                                NEOGEO ROM-cart:1992/05/29
                                                                                                NEOGEO CD:1994/10/31
    KING OF THE MONSTERS 2                                      Fighting        SNK             MVS Cartridge:1992/05/25
                                                                                                NEOGEO ROM-cart:1992/06/19
                                                                                                NEOGEO CD:1994/09/09
    ANDRO DUNOS                                                 Shooter         Visco           MVS Cartridge:1992/06/15
                                                                                                NEOGEO ROM-cart:1992/07/17
    WORLD HEROES                                                Fighting        ADK             MVS Cartridge:1992/07/28
                                                                                                NEOGEO ROM-cart:1992/09/11
                                                                                                NEOGEO CD:1995/03/17
    ART OF FIGHTING                                             Fighting        SNK             MVS Cartridge:1992/09/24
                                                                                                NEOGEO ROM-cart:1992/12/11
                                                                                                NEOGEO CD:1994/09/09
    VIEWPOINT                                                   Shooter         Sammy           MVS Cartridge:1992/11/20
                                                                                                NEOGEO ROM-cart:1992/12/11
                                                                                                NEOGEO CD:1995/02/25
    FATAL FURY 2                                                Fighting        SNK             MVS Cartridge:1992/12/10
                                                                                                NEOGEO ROM-cart:1993/03/05
                                                                                                NEOGEO CD:1994/09/09
    SUPER SIDEKICKS                                             Sports          SNK             MVS Cartridge:1992/12/14
                                                                                                NEOGEO ROM-cart:1993/02/19
                                                                                                NEOGEO CD:1995/03/31
    SENGOKU 2                                                   Action          SNK             MVS Cartridge:1993/02/18
                                                                                                NEOGEO ROM-cart:1993/04/09
                                                                                                NEOGEO CD:1995/03/17
    3 COUNT BOUT                                                Fighting        SNK             MVS Cartridge:1993/03/25
                                                                                                NEOGEO ROM-cart:1993/04/23
                                                                                                NEOGEO CD:1995/04/21
    WORLD HEROES 2                                              Fighting        ADK             MVS Cartridge:1993/04/26
                                                                                                NEOGEO ROM-cart:1993/06/04
                                                                                                NEOGEO CD:1995/04/14
    SAMURAI SHODOWN                                             Fighting        SNK             MVS Cartridge:1993/07/07
                                                                                                NEOGEO ROM-cart:1993/08/11
                                                                                                NEOGEO CD:1994/09/09
    FATAL FURY SPECIAL                                          Fighting        SNK             MVS Cartridge:1993/09/16
                                                                                                NEOGEO ROM-cart:1993/12/22
                                                                                                NEOGEO CD:1994/09/09
    SPINMASTER                                                  Sideview Action Data East       MVS Cartridge:1993/12/16
                                                                                                NEOGEO ROM-cart:1994/02/18
    ART OF FIGHTING 2                                           Fighting        SNK             MVS Cartridge:1994/02/03
                                                                                                NEOGEO ROM-cart:1994/03/11
                                                                                                NEOGEO CD:1994/09/09
    WINDJAMMERS                                                 Sports          Data East       MVS Cartridge:1994/02/17
                                                                                                NEOGEO ROM-cart:1994/04/08
                                                                                                NEOGEO CD:1995/01/20
    KARNOV'S REVENGE                                            Fighting        Data East       MVS Cartridge:1994/03/17
                                                                                                NEOGEO ROM-cart:1994/04/28
                                                                                                NEOGEO CD:1994/12/22
    SUPER SIDEKICKS 2                                           Sports          SNK             MVS Cartridge:1994/04/19
                                                                                                NEOGEO ROM-cart:1994/05/27
                                                                                                NEOGEO CD:1994/09/09
    WORLD HEROES 2 JET                                          Fighting        ADK             MVS Cartridge:1994/04/26
                                                                                                NEOGEO ROM-cart:1994/06/10
                                                                                                NEOGEO CD:1994/11/11
    TOP HUNTER                                                  Action          SNK             MVS Cartridge:1994/05/18
                                                                                                NEOGEO ROM-cart:1994/06/24
                                                                                                NEOGEO CD:1994/09/29
    GURURIN                                                     Puzzle          Face            MVS Cartridge:1994/05/25
    FIGHT FEVER                                                 Fighting        VICCOM          MVS Cartridge:1994/06/28
    JANSHIN DENSETSU: QUEST OF JONGMASTER                       Mahjong         Aicom           MVS Cartridge:1994/06/29
                                                                                                NEOGEO CD:1995/03/31
    AERO FIGHTERS 2                                             Topview Shooter Video System    MVS Cartridge:1994/07/18
                                                                                                NEOGEO ROM-cart:1994/08/26
                                                                                                NEOGEO CD:1994/09/29
    AGGRESSORS OF DARK KOMBAT                                   Fighting        ADK             MVS Cartridge:1994/07/26
                                                                                                NEOGEO ROM-cart:1994/08/26
                                                                                                NEOGEO CD:1995/01/13
    THE KING OF FIGHTERS '94                                    Fighting        SNK             MVS Cartridge:1994/08/25
                                                                                                NEOGEO ROM-cart:1994/10/01
                                                                                                NEOGEO CD:1994/11/02
    ZED BLADE                                                   Shooter         NMK             MVS Cartridge:1994/09/13
    POWER SPIKES II                                             Sports          Video System    MVS Cartridge:1994/10/19
                                                                                                NEOGEO CD:1995/03/18
    SAMURAI SHODOWN II                                          Fighting        SNK             MVS Cartridge:1994/10/28
                                                                                                NEOGEO ROM-cart:1994/12/02
                                                                                                NEOGEO CD:1994/12/15
    STREET HOOP                                                 Sports          Data East       MVS Cartridge:1994/12/08
                                                                                                NEOGEO ROM-cart:1994/12/09
                                                                                                NEOGEO CD:1995/01/20
    PUZZLE BOBBLE                                               Puzzle          TAITO           MVS Cartridge:1994/12/21
                                                                                                NEOGEO CD:1995/05/02
    SUPER VOLLEY '94                                            Sports          TAITO           MVS Cartridge:1994
    BOMBERMAN: PANIC BOMBER                                     Puzzle          Eighting        MVS Cartridge:1995/01/18
    GALAXY FIGHT: UNIVERSAL WARRIORS                            Fighting        Sunsoft         MVS Cartridge:1995/01/24
                                                                                                NEOGEO ROM-cart:1995/02/25
                                                                                                NEOGEO CD:1995/04/21
    QUIZ KING OF FIGHTERS                                       Quiz            Saurus          MVS Cartridge:1995/02/01
                                                                                                NEOGEO ROM-cart:1995/03/10
                                                                                                NEOGEO CD:1995/04/07
    DOUBLE DRAGON                                               Fighting        Technos         MVS Cartridge:1995/03/03
                                                                                                NEOGEO ROM-cart:1995/03/31
                                                                                                NEOGEO CD:1995/06/02
    SUPER SIDEKICKS 3                                           Sports          SNK             MVS Cartridge:1995/03/07
                                                                                                NEOGEO ROM-cart:1995/04/07
                                                                                                NEOGEO CD:1995/06/23
    FATAL FURY 3                                                Fighting        SNK             MVS Cartridge:1995/03/27
                                                                                                NEOGEO ROM-cart:1995/04/21
                                                                                                NEOGEO CD:1995/04/28
    SAVAGE REIGN                                                Fighting        SNK             MVS Cartridge:1995/04/25
                                                                                                NEOGEO ROM-cart:1995/03/10
                                                                                                NEOGEO CD:1995/06/16
    CROSSED SWORDS II                                           Action          ADK             NEOGEO CD:1995/05/02
    WORLD HEROES PERFECT                                        Fighting        ADK             MVS Cartridge:1995/05/25
                                                                                                NEOGEO ROM-cart:1995/06/30
                                                                                                NEOGEO CD:1995/07/21
    FAR EAST OF EDEN: KABUKI KLASH                              Fighting        Hudson Soft     MVS Cartridge:1995/06/20
                                                                                                NEOGEO ROM-cart:1995/07/28
                                                                                                NEOGEO CD:1995/11/24
    THE KING OF FIGHTERS '95                                    Fighting        SNK             MVS Cartridge:1995/07/25
                                                                                                NEOGEO ROM-cart:1995/09/01
                                                                                                NEOGEO CD:1995/09/29
    IDOL MAHJONG FINAL ROMANCE 2                                Mahjong         Video System    NEOGEO CD:1995/08/25
    PULSTAR                                                     Sidevi. Shooter Aicom           MVS Cartridge:1995/08/28
                                                                                                NEOGEO ROM-cart:1995/09/29
                                                                                                NEOGEO CD:1995/10/27
    VOLTAGE FIGHTER GOWCAIZER                                   Fighting        Technos         MVS Cartridge:1995/09/18
                                                                                                NEOGEO ROM-cart:1995/10/20
                                                                                                NEOGEO CD:1995/11/24
    STAKES WINNER                                               Action          Saurus          MVS Cartridge:1995/09/27
                                                                                                NEOGEO ROM-cart:1995/10/27
                                                                                                NEOGEO CD:1996/03/22
    SHOGI NO TATSUJIN - MASTER OF SYOUGI                        Japanese chess  ADK             MVS Cartridge:1995/09/28
                                                                                                NEOGEO ROM-cart:1995/10/13
                                                                                                NEOGEO CD:1995/10/20
    AERO FIGHTERS 3                                             Topview Action  Video System    MVS Cartridge:1995/10/12
                                                                                                NEOGEO ROM-cart:1995/11/17
                                                                                                NEOGEO CD:1995/12/08
    ADK WORLD                                                   Variety         ADK             NEOGEO CD:1995/11/10
    SAMURAI SHODOWN III                                         Fighting        SNK             MVS Cartridge:1995/11/15
                                                                                                NEOGEO ROM-cart:1995/12/01
                                                                                                NEOGEO CD:1995/12/29
    CHIBI MARUKO-CHAN DELUXE QUIZ                               Variety         Takara          MVS Cartridge:1995/11/27
                                                                                                NEOGEO ROM-cart:1996/01/26
    PUZZLE DE PON!                                              Puzzle          Visco           MVS Cartridge:1995/11/28
    REAL BOUT FATAL FURY                                        Fighting        SNK             MVS Cartridge:1995/12/21
                                                                                                NEOGEO ROM-cart:1996/01/26
                                                                                                NEOGEO CD:1996/02/23
    NEO-GEO CD SPECIAL                                          Variety         SNK             NEOGEO CD:1995/12/22
    NEO TURF MASTERS                                            Sports          Nazca           MVS Cartridge:1996/01/29
                                                                                                NEOGEO ROM-cart:1996/03/01
                                                                                                NEOGEO CD:1996/05/03
    ART OF FIGHTING 3                                           Fighting        SNK             MVS Cartridge:1996/03/12
                                                                                                NEOGEO ROM-cart:1996/04/26
                                                                                                NEOGEO CD:1996/06/14
    MAGICAL DROP II                                             Puzzle          Data East       MVS Cartridge:1996/03/21
                                                                                                NEOGEO ROM-cart:1996/04/19
                                                                                                NEOGEO CD:1996/05/24
    OSHIDASHI JIN TRICK                                         Puzzle          ADK             NEOGEO CD:1996/03/22
    NEO DRIFT OUT                                               Racing          Visco           MVS Cartridge:1996/03/28
                                                                                                NEOGEO CD:1996/07/26
    METAL SLUG                                                  Action          Nazca           MVS Cartridge:1996/04/19
                                                                                                NEOGEO ROM-cart:1996/05/24
                                                                                                NEOGEO CD:1996/07/05
    OVER TOP                                                    Racing          ADK             MVS Cartridge:1996/04/26
                                                                                                NEOGEO ROM-cart:1996/06/07
                                                                                                NEOGEO CD:1996/07/26
    NINJA MASTER'S                                              Fighting        ADK             MVS Cartridge:1996/05/27
                                                                                                NEOGEO ROM-cart:1996/06/28
                                                                                                NEOGEO CD:1996/09/27
    RAGNAGARD                                                   Fighting        Saurus          MVS Cartridge:1996/06/13
                                                                                                NEOGEO ROM-cart:1996/07/26
                                                                                                NEOGEO CD:1996/08/23
    FUTSAL                                                      Sports          Saurus          NEOGEO CD:1996/07/19
    THE KING OF FIGHTERS '96                                    Fighting        SNK             MVS Cartridge:1996/07/30
                                                                                                NEOGEO ROM-cart:1996/09/27
                                                                                                NEOGEO CD:1996/10/25
    KIZUNA ENCOUNTER SUPER TAG BATTLE                           Fighting        SNK             MVS Cartridge:1996/09/20
                                                                                                NEOGEO ROM-cart:1996/11/08
    CHOUTETSU BURIKINGA                                         Shooter         Saurus          NEOGEO CD:1996/09/20
    STAKES WINNER 2                                             Real Jockey Act Saurus          MVS Cartridge:1996/09/24
                                                                                                NEOGEO ROM-cart:1996/12/13
    THE ULTIMATE 11                                             Sports          SNK             MVS Cartridge:1996/10/16
                                                                                                NEOGEO ROM-cart:1996/12/20
    SAMURAI SHODOWN IV                                          Fighting        SNK             MVS Cartridge:1996/10/25
                                                                                                NEOGEO ROM-cart:1996/11/29
                                                                                                NEOGEO CD:1996/12/27
    WAKU WAKU 7                                                 Fighting        Sunsoft         MVS Cartridge:1996/11/21
                                                                                                NEOGEO ROM-cart:1996/12/27
    TWINKLE STAR SPRITES                                        Shooter         ADK             MVS Cartridge:1996/11/25
                                                                                                NEOGEO ROM-cart:1997/01/31
                                                                                                NEOGEO CD:1997/02/21
    BREAKERS                                                    Fighting        Visco           MVS Cartridge:1996/12/17
                                                                                                NEOGEO ROM-cart:1997/03/21
                                                                                                NEOGEO CD:1997/04/25
    MONEY IDOL EXCHANGER                                        Puzzle          Face            MVS Cartridge:1997/01/15
    Real Bout FATAL FURY SPECIAL                                Fighting        SNK             MVS Cartridge:1997/01/28
                                                                                                NEOGEO ROM-cart:1997/02/28
                                                                                                NEOGEO CD:1997/03/03
    THE KING OF FIGHTERS '96 NEOGEO COLLECTION                  Variety         SNK             NEOGEO CD:1997/02/14
    MAGICAL DROP III                                            Puzzle          Data East       MVS Cartridge:1997/02/25
                                                                                                NEOGEO ROM-cart:1997/04/25
    NEO BOMBERMAN                                               Action          Hudson Soft     MVS Cartridge:1997/05/01
    NEO MR.DO!                                                  Action          Visco           MVS Cartridge:1997/06/26
    SHINSETSU SAMURAI SHODOWN BUSHIDO RETSUDEN                  Role-playing    SNK             NEOGEO CD:1997/06/27
    THE KING OF FIGHTERS '97                                    Fighting        SNK             MVS Cartridge:1997/07/28
                                                                                                NEOGEO ROM-cart:1997/09/25
                                                                                                NEOGEO CD:1997/10/30
    UCCHAN NANCHAN NO HONO NO CHALLENGER ULTRA DENRYU IRAIRABOU Action          Saurus          MVS Cartridge:1997/08/25
    SHOCK TROOPERS                                              Shooter         Saurus          MVS Cartridge:1997/11/11
    THE LAST BLADE                                              Fighting        SNK             MVS Cartridge:1997/12/05
                                                                                                NEOGEO ROM-cart:1998/01/29
                                                                                                NEOGEO CD:1998/03/26
    BLAZING STAR                                                Shooter         Yumekobo        MVS Cartridge:1998/01/19
                                                                                                NEOGEO ROM-cart:1998/02/26
    METAL SLUG 2                                                Action          SNK             MVS Cartridge:1998/02/23
                                                                                                NEOGEO ROM-cart:1998/04/02
                                                                                                NEOGEO CD:1998/06/25
    REAL BOUT FATAL FURY 2                                      Fighting        SNK             MVS Cartridge:1998/03/20
                                                                                                NEOGEO ROM-cart:1998/04/29
                                                                                                NEOGEO CD:1998/07/23
    NEOGEO CUP '98                                              Sports          SNK             MVS Cartridge:1998/05/28
                                                                                                NEOGEO ROM-cart:1998/07/30
    BREAKERS REVENGE                                            Fighting        Visco           MVS Cartridge:1998/07/03
                                                                                                NEOGEO ROM-cart:
    THE KING OF FIGHTERS '98                                    Fighting        SNK             MVS Cartridge:1998/07/23
                                                                                                NEOGEO ROM-cart:1998/09/23
                                                                                                NEOGEO CD:1998/12/23
    SHOCK TROOPERS 2nd Squad                                    Action Shooter  Saurus          MVS Cartridge:1998/11/06
                                                                                                NEOGEO ROM-cart:1999/06/24
    THE LAST BLADE 2                                            Fighting        SNK             MVS Cartridge:1998/11/25
                                                                                                NEOGEO ROM-cart:1999/01/28
                                                                                                NEOGEO CD:1999/02/27
    FLIP SHOT                                                   Action          Visco           MVS Cartridge:1998/12/08
    METAL SLUG X                                                Action          SNK             MVS Cartridge:1999/03/19
                                                                                                NEOGEO ROM-cart:1999/05/27
    CAPTAIN TOMADAY                                             Shooter         Visco           MVS Cartridge:1999/05/27
    THE KING OF FIGHTERS '99                                    Fighting        SNK             MVS Cartridge:1999/07/22
                                                                                                NEOGEO ROM-cart:1999/09/23
                                                                                                NEOGEO CD:1999/12/02
    PREHISTORIC ISLE 2                                          Shooter         Yumekobo        MVS Cartridge:1999/09/27
    GAROU: MARK OF THE WOLVES                                   Fighting        SNK             MVS Cartridge:1999/11/26
                                                                                                NEOGEO ROM-cart:2000/02/25
    STRIKERS 1945 PLUS                                          Shooter         Psikyo          MVS Cartridge:1999/12/24
    METAL SLUG 3                                                Action Shooter  SNK             MVS Cartridge:2000/03/23
                                                                                                NEOGEO ROM-cart:2000/06/01
    THE KING OF FIGHTERS 2000                                   Fighting        SNK             MVS Cartridge:2000/07/26
                                                                                                NEOGEO ROM-cart:2000/12/21
    NIGHTMARE IN THE DARK                                       Horror Action   Gavaking        MVS Cartridge:2001
    ZUPAPA!                                                     Comical Action  Video System    MVS Cartridge:2001
    SENGOKU 3                                                   Action          SNK PLAYMORE    MVS Cartridge:2001/07/18
                                                                                                NEOGEO ROM-cart:2001/10/25
    THE KING OF FIGHTERS 2001                                   Fighting        SNK PLAYMORE    MVS Cartridge:2001/11/15
                                                                                                NEOGEO ROM-cart:2002/03/14
    METAL SLUG 4                                                Action Shooter  SNK PLAYMORE    MVS Cartridge:2002/03/27
                                                                                                NEOGEO ROM-cart:2002/06/13
    RAGE OF THE DRAGONS                                         Fighting        Evoga           MVS Cartridge:2002/06/06
                                                                                                NEOGEO ROM-cart:2002/09/26
    THE KING OF FIGHTERS 2002                                   Fighting        SNK PLAYMORE    MVS Cartridge:2002/10/10
                                                                                                NEOGEO ROM-cart:2002/12/19
    POWER INSTINCT MATRIMELEE                                   Fighting        ATLUS/NOISE FA. MVS Cartridge:2003/03/20
                                                                                                NEOGEO ROM-cart:2003/05/29
    SNK VS. CAPCOM: SVC CHAOS                                   Fighting        SNK PLAYMORE    MV-0:2003/07/24
                                                                                                NEOGEO ROM-cart:2003/11/13
    SAMURAI SHODOWN V                                           Fighting        SNK P/Yuki Ent  MVS Cartridge:2003/10/10
                                                                                                NEOGEO ROM-cart:2003/12/11
    METAL SLUG 5                                                Action Shooter  SNK PLAYMORE    MV-0:2003/11/14
                                                                                                NEOGEO ROM-cart:2004/02/19
    THE KING OF FIGHTERS 2003                                   Fighting        SNK PLAYMORE    MV-0:2003/12/12
                                                                                                NEOGEO ROM-cart:2004/03/18
    POCHI & NYAA                                                Puzzle          Aiky            MVS Cartridge:2003/12/24
    SAMURAI SHODOWN V SPECIAL                                   Fighting        SNK P/Yuki Ent  MVS Cartridge:2004/04/22
                                                                                                NEOGEO ROM-cart:2004/07/15
****************************************************************************/

/*    YEAR  NAME        PARENT    MACHINE          INPUT   INIT            MONITOR */
/* SNK */
GAME( 1990, nam1975,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "NAM-1975 (NGM-001)(NGH-001)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, bstars,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Baseball Stars Professional (NGM-002)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, bstarsh,    bstars,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Baseball Stars Professional (NGH-002)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, tpgolf,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Top Player's Golf (NGM-003)(NGH-003)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, mahretsu,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Mahjong Kyo Retsuden (NGM-004)(NGH-004)", MACHINE_SUPPORTS_SAVE ) // does not support mahjong panel in MVS mode
GAME( 1990, ridhero,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Riding Hero (NGM-006)(NGH-006)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, ridheroh,   ridhero,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Riding Hero (set 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, alpham2,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Alpha Mission II / ASO II - Last Guardian (NGM-007)(NGH-007)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, alpham2p,   alpham2,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Alpha Mission II / ASO II - Last Guardian (prototype)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, cyberlip,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Cyber-Lip (NGM-010)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, superspy,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The Super Spy (NGM-011)(NGH-011)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, mutnat,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Mutation Nation (NGM-014)(NGH-014)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, kotm,       neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "King of the Monsters (set 1)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, kotmh,      kotm,     neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "King of the Monsters (set 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, sengoku,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Sengoku / Sengoku Denshou (NGM-017)(NGH-017)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, sengokuh,   sengoku,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Sengoku / Sengoku Denshou (NGH-017)(US)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, burningf,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Burning Fight (NGM-018)(NGH-018)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, burningfh,  burningf, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Burning Fight (NGH-018)(US)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, burningfp,  burningf, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Burning Fight (prototype)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, lbowling,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "League Bowling (NGM-019)(NGH-019)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, gpilots,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Ghost Pilots (NGM-020)(NGH-020)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, gpilotsh,   gpilots,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Ghost Pilots (NGH-020)(US)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, joyjoy,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Puzzled / Joy Joy Kid (NGM-021)(NGH-021)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, quizdais,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Quiz Daisousa Sen - The Last Count Down (NGM-023)(NGH-023)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, quizdaisk,  quizdais, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Quiz Daisousa Sen - The Last Count Down (Korean release)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, lresort,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Last Resort", MACHINE_SUPPORTS_SAVE )
GAME( 1992, lresortp,   lresort,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Last Resort (prototype)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, eightman,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK / Pallas", "Eight Man (NGM-025)(NGH-025)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, legendos,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Legend of Success Joe / Ashita no Joe Densetsu", MACHINE_SUPPORTS_SAVE )
GAME( 1991, 2020bb,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK / Pallas", "2020 Super Baseball (set 1)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, 2020bba,    2020bb,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK / Pallas", "2020 Super Baseball (set 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, 2020bbh,    2020bb,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK / Pallas", "2020 Super Baseball (set 3)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, socbrawl,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Soccer Brawl (NGM-031)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, socbrawlh,  socbrawl, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Soccer Brawl (NGH-031)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, fatfury1,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Fatal Fury - King of Fighters / Garou Densetsu - shukumei no tatakai (NGM-033)(NGH-033)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, roboarmy,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Robo Army", MACHINE_SUPPORTS_SAVE )
GAME( 1992, fbfrenzy,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Football Frenzy (NGM-034)(NGH-034)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, kotm2,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "King of the Monsters 2 - The Next Thing (NGM-039)(NGH-039)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, kotm2p,     kotm2,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "King of the Monsters 2 - The Next Thing (prototype)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, sengoku2,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Sengoku 2 / Sengoku Denshou 2", MACHINE_SUPPORTS_SAVE )
GAME( 1992, bstars2,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Baseball Stars 2", MACHINE_SUPPORTS_SAVE )
GAME( 1992, quizdai2,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Quiz Meitantei Neo & Geo - Quiz Daisousa Sen part 2 (NGM-042)(NGH-042)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, 3countb,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "3 Count Bout / Fire Suplex (NGM-043)(NGH-043)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, aof,        neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Art of Fighting / Ryuuko no Ken (NGM-044)(NGH-044)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, samsho,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Samurai Shodown / Samurai Spirits (NGM-045)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, samshoh,    samsho,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Samurai Shodown / Samurai Spirits (NGH-045)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, samshoa,    samsho,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Samurai Shodown / Samurai Spirits (NGM-045, alternate board)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, tophuntr,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Top Hunter - Roddy & Cathy (NGM-046)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, tophuntrh,  tophuntr, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Top Hunter - Roddy & Cathy (NGH-046)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, fatfury2,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_fatfury2, ROT0, "SNK", "Fatal Fury 2 / Garou Densetsu 2 - arata-naru tatakai (NGM-047)(NGH-047)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, ssideki,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_fatfury2, ROT0, "SNK", "Super Sidekicks / Tokuten Ou", MACHINE_SUPPORTS_SAVE )
GAME( 1994, kof94,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The King of Fighters '94 (NGM-055)(NGH-055)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, aof2,       neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Art of Fighting 2 / Ryuuko no Ken 2 (NGM-056)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, aof2a,      aof2,     neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Art of Fighting 2 / Ryuuko no Ken 2 (NGH-056)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, fatfursp,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Fatal Fury Special / Garou Densetsu Special (set 1)(NGM-058)(NGH-058)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, fatfurspa,  fatfursp, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Fatal Fury Special / Garou Densetsu Special (set 2)(NGM-058)(NGH-058)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, savagere,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Savage Reign / Fu'un Mokushiroku - kakutou sousei", MACHINE_SUPPORTS_SAVE )
GAME( 1994, ssideki2,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Super Sidekicks 2 - The World Championship / Tokuten Ou 2 - real fight football (NGM-061)(NGH-061)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, samsho2,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Samurai Shodown II / Shin Samurai Spirits - Haohmaru jigokuhen (NGM-063)(NGH-063)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, samsho2k,   samsho2,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Saulabi Spirits / Jin Saulabi Tu Hon (Korean release of Samurai Shodown II)", MACHINE_SUPPORTS_SAVE ) // official or hack?
GAME( 1995, fatfury3,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Fatal Fury 3 - Road to the Final Victory / Garou Densetsu 3 - haruka-naru tatakai (NGM-069)(NGH-069)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, ssideki3,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Super Sidekicks 3 - The Next Glory / Tokuten Ou 3 - eikou e no michi", MACHINE_SUPPORTS_SAVE )
GAME( 1995, kof95,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The King of Fighters '95 (NGM-084)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, kof95a,     kof95,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The King of Fighters '95 (NGM-084), alternate board", MACHINE_SUPPORTS_SAVE )
GAME( 1995, kof95h,     kof95,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The King of Fighters '95 (NGH-084)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, samsho3,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Samurai Shodown III / Samurai Spirits - Zankurou Musouken (NGM-087)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, samsho3h,   samsho3,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Samurai Shodown III / Samurai Spirits - Zankurou Musouken (NGH-087)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, fswords,    samsho3,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Fighters Swords (Korean release of Samurai Shodown III)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, rbff1,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Real Bout Fatal Fury / Real Bout Garou Densetsu (NGM-095)(NGH-095)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, rbff1a,     rbff1,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Real Bout Fatal Fury / Real Bout Garou Densetsu (bug fix revision)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, aof3,       neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Art of Fighting 3 - The Path of the Warrior / Art of Fighting - Ryuuko no Ken Gaiden", MACHINE_SUPPORTS_SAVE )
GAME( 1996, aof3k,      aof3,     neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Art of Fighting 3 - The Path of the Warrior (Korean release)", MACHINE_SUPPORTS_SAVE ) // no Japanese title / mode
GAME( 1996, kof96,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The King of Fighters '96 (NGM-214)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, kof96h,     kof96,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The King of Fighters '96 (NGH-214)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ssideki4,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The Ultimate 11 - The SNK Football Championship / Tokuten Ou - Honoo no Libero", MACHINE_SUPPORTS_SAVE )
GAME( 1996, kizuna,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Kizuna Encounter - Super Tag Battle / Fu'un Super Tag Battle", MACHINE_SUPPORTS_SAVE )
GAME( 1996, kizuna4p,   kizuna,   neogeo_kiz4p,    kizuna4p, neogeo_state, init_neogeo,   ROT0, "SNK", "Kizuna Encounter - Super Tag Battle 4 Way Battle Version / Fu'un Super Tag Battle Special Version", MACHINE_SUPPORTS_SAVE )
GAME( 1996, samsho4,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Samurai Shodown IV - Amakusa's Revenge / Samurai Spirits - Amakusa Kourin (NGM-222)(NGH-222)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, samsho4k,   samsho4,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Pae Wang Jeon Seol / Legend of a Warrior (Korean censored Samurai Shodown IV)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, rbffspec,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Real Bout Fatal Fury Special / Real Bout Garou Densetsu Special", MACHINE_SUPPORTS_SAVE )
GAME( 1996, rbffspeck,  rbffspec, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Real Bout Fatal Fury Special / Real Bout Garou Densetsu Special (Korean release)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, kof97,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The King of Fighters '97 (NGM-2320)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, kof97h,     kof97,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The King of Fighters '97 (NGH-2320)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, kof97k,     kof97,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The King of Fighters '97 (Korean release)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, kof97pls,   kof97,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "bootleg", "The King of Fighters '97 Plus (bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, kof97oro,   kof97,    neogeo_noslot,   neogeo, neogeo_state,   init_kof97oro, ROT0, "bootleg", "The King of Fighters '97 Oroshi Plus 2003 (bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, kog,        kof97,    neogeo_kog,      neogeo, neogeo_state,   init_kog,      ROT0, "bootleg", "King of Gladiator (The King of Fighters '97 bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, lastblad,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The Last Blade / Bakumatsu Roman - Gekka no Kenshi (NGM-2340)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, lastbladh,  lastblad, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The Last Blade / Bakumatsu Roman - Gekka no Kenshi (NGH-2340)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, lastsold,   lastblad, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The Last Soldier (Korean release of The Last Blade)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, irrmaze,    neogeo,   neogeo_imaze,    irrmaze,neogeo_state,   init_neogeo,   ROT0, "SNK / Saurus", "The Irritating Maze / Ultra Denryu Iraira Bou", MACHINE_SUPPORTS_SAVE )
GAME( 1998, rbff2,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Real Bout Fatal Fury 2 - The Newcomers / Real Bout Garou Densetsu 2 - the newcomers (NGM-2400)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, rbff2h,     rbff2,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Real Bout Fatal Fury 2 - The Newcomers / Real Bout Garou Densetsu 2 - the newcomers (NGH-2400)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, rbff2k,     rbff2,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Real Bout Fatal Fury 2 - The Newcomers (Korean release)", MACHINE_SUPPORTS_SAVE ) // no Japanese title / mode
GAME( 1998, mslug2,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Metal Slug 2 - Super Vehicle-001/II (NGM-2410)(NGH-2410)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, kof98,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_kof98,    ROT0, "SNK", "The King of Fighters '98 - The Slugfest / King of Fighters '98 - dream match never ends (NGM-2420)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, kof98a,     kof98,    neogeo_noslot,   neogeo, neogeo_state,   init_kof98,    ROT0, "SNK", "The King of Fighters '98 - The Slugfest / King of Fighters '98 - dream match never ends (NGM-2420, alternate board)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, kof98k,     kof98,    neogeo_noslot,   neogeo, neogeo_state,   init_kof98,    ROT0, "SNK", "The King of Fighters '98 - The Slugfest / King of Fighters '98 - dream match never ends (Korean board)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, kof98ka,    kof98,    neogeo_noslot,   neogeo, neogeo_state,   init_kof98,    ROT0, "SNK", "The King of Fighters '98 - The Slugfest / King of Fighters '98 - dream match never ends (Korean board 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, kof98h,     kof98,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The King of Fighters '98 - The Slugfest / King of Fighters '98 - dream match never ends (NGH-2420)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, lastbld2,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The Last Blade 2 / Bakumatsu Roman - Dai Ni Maku Gekka no Kenshi (NGM-2430)(NGH-2430)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, neocup98,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Neo-Geo Cup '98 - The Road to the Victory", MACHINE_SUPPORTS_SAVE )
GAME( 1999, mslugx,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_mslugx,   ROT0, "SNK", "Metal Slug X - Super Vehicle-001 (NGM-2500)(NGH-2500)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, kof99,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_kof99,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (NGM-2510)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted Code & GFX */
GAME( 1999, kof99h,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (NGH-2510)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted Code & GFX, crashes going into attract demo */
GAME( 1999, kof99e,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (earlier)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted Code & GFX */
GAME( 1999, kof99k,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (Korean release)" , MACHINE_SUPPORTS_SAVE )   /* Encrypted GFX */
GAME( 1999, kof99p,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (prototype)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, garou,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_garou,    ROT0, "SNK", "Garou - Mark of the Wolves (NGM-2530)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted Code & GFX */
GAME( 1999, garouh,     garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garouh,   ROT0, "SNK", "Garou - Mark of the Wolves (NGM-2530)(NGH-2530)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted Code & GFX */
GAME( 1999, garoup,     garou,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Garou - Mark of the Wolves (prototype)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, garoubl,    garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garoubl,  ROT0, "bootleg", "Garou - Mark of the Wolves (bootleg)", MACHINE_SUPPORTS_SAVE ) /* Bootleg of garoup */
GAME( 2000, mslug3,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_mslug3,   ROT0, "SNK", "Metal Slug 3 (NGM-2560)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted Code & GFX */
GAME( 2000, mslug3a,    mslug3,   neogeo_noslot,   neogeo, neogeo_state,   init_mslug3a,  ROT0, "SNK", "Metal Slug 3 (NGM-2560, earlier)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted Code & GFX - revision Mar/17/2000 1:36 (from SMA rom) */
GAME( 2000, mslug3h,    mslug3,   neogeo_noslot,   neogeo, neogeo_state,   init_mslug3h,  ROT0, "SNK", "Metal Slug 3 (NGH-2560)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2000, mslug3b6,   mslug3,   neogeo_noslot,   neogeo, neogeo_state,   init_mslug3b6, ROT0, "bootleg", "Metal Slug 6 (Metal Slug 3 bootleg)", MACHINE_SUPPORTS_SAVE ) /* real Metal Slug 6 is an Atomiswave HW game, see naomi.c ;-) */
GAME( 2000, kof2000,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_kof2000,  ROT0, "SNK", "The King of Fighters 2000 (NGM-2570) (NGH-2570)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted Code & GFX */
GAME( 2000, kof2000n,   kof2000,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2000,  ROT0, "SNK", "The King of Fighters 2000 (not encrypted)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2001, zupapa,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_zupapa,   ROT0, "SNK", "Zupapa!" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2001, sengoku3,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_sengoku3, ROT0, "Noise Factory / SNK", "Sengoku 3 / Sengoku Densho 2001" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2001, kof2001,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_kof2001,  ROT0, "Eolith / SNK", "The King of Fighters 2001 (NGM-262?)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2001, kof2001h,   kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2001,  ROT0, "Eolith / SNK", "The King of Fighters 2001 (NGH-2621)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2003, cthd2003,   kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_cthd2003, ROT0, "bootleg", "Crouching Tiger Hidden Dragon 2003 (The King of Fighters 2001 bootleg)", MACHINE_SUPPORTS_SAVE ) /* Protected Hack / Bootleg of kof2001 */
GAME( 2003, ct2k3sp,    kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_ct2k3sp,  ROT0, "bootleg", "Crouching Tiger Hidden Dragon 2003 Super Plus (The King of Fighters 2001 bootleg)", MACHINE_SUPPORTS_SAVE ) /* Protected Hack / Bootleg of kof2001 */
GAME( 2003, ct2k3sa,    kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_ct2k3sa,  ROT0, "bootleg", "Crouching Tiger Hidden Dragon 2003 Super Plus alternate (The King of Fighters 2001 bootleg)", MACHINE_SUPPORTS_SAVE ) /* Hack / Bootleg of kof2001 */
GAME( 2002, kof2002,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_kof2002,  ROT0, "Eolith / Playmore", "The King of Fighters 2002 (NGM-2650)(NGH-2650)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2002, kof2002b,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2002b, ROT0, "bootleg", "The King of Fighters 2002 (bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, kf2k2pls,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2002,  ROT0, "bootleg", "The King of Fighters 2002 Plus (bootleg set 1)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2002, kf2k2pla,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2002,  ROT0, "bootleg", "The King of Fighters 2002 Plus (bootleg set 2)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2002, kf2k2mp,    kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kf2k2mp,  ROT0, "bootleg", "The King of Fighters 2002 Magic Plus (bootleg)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2002, kf2k2mp2,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kf2k2mp2, ROT0, "bootleg", "The King of Fighters 2002 Magic Plus II (bootleg)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2002, kof10th,    kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kof10th,  ROT0, "bootleg", "The King of Fighters 10th Anniversary (The King of Fighters 2002 bootleg)", MACHINE_SUPPORTS_SAVE ) // fake SNK copyright
GAME( 2005, kf10thep,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kf10thep, ROT0, "bootleg", "The King of Fighters 10th Anniversary Extra Plus (The King of Fighters 2002 bootleg)", MACHINE_SUPPORTS_SAVE ) // fake SNK copyright
GAME( 2004, kf2k5uni,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kf2k5uni, ROT0, "bootleg", "The King of Fighters 10th Anniversary 2005 Unique (The King of Fighters 2002 bootleg)", MACHINE_SUPPORTS_SAVE ) // fake SNK copyright
GAME( 2004, kof2k4se,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_kof2k4se, ROT0, "bootleg", "The King of Fighters Special Edition 2004 (The King of Fighters 2002 bootleg)", MACHINE_SUPPORTS_SAVE ) /* Hack / Bootleg of kof2002 */
GAME( 2003, mslug5,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_mslug5,   ROT0, "SNK Playmore", "Metal Slug 5 (NGM-2680)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5h,    mslug5,   neogeo_noslot,   neogeo, neogeo_state,   init_mslug5,   ROT0, "SNK Playmore", "Metal Slug 5 (NGH-2680)", MACHINE_SUPPORTS_SAVE ) /* Also found in later MVS carts */
GAME( 2003, ms5pcb,     mslug5,   neogeo_noslot,   dualbios, neogeo_state, init_ms5pcb,   ROT0, "SNK Playmore", "Metal Slug 5 (JAMMA PCB)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, ms5plus,    mslug5,   neogeo_noslot,   neogeo, neogeo_state,   init_ms5plus,  ROT0, "bootleg", "Metal Slug 5 Plus (bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, mslug5b,    mslug5,   neogeo_noslot,   neogeo, neogeo_state,   init_mslug5b,  ROT0, "bootleg", "Metal Slug 5 (bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, svcpcb,     0,        neogeo_noslot,   dualbios, neogeo_state, init_svcpcb,   ROT0, "SNK Playmore", "SNK vs. Capcom - SVC Chaos (JAMMA PCB, set 1)", MACHINE_SUPPORTS_SAVE ) // not a clone of neogeo because it's NOT a neogeo cart.
GAME( 2003, svcpcba,    svcpcb,   neogeo_noslot,   dualbios, neogeo_state, init_svcpcb,   ROT0, "SNK Playmore", "SNK vs. Capcom - SVC Chaos (JAMMA PCB, set 2)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted Code */
GAME( 2003, svc,        neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_svc,      ROT0, "SNK Playmore", "SNK vs. Capcom - SVC Chaos (NGM-2690)(NGH-2690)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, svcboot,    svc,      neogeo_noslot,   neogeo, neogeo_state,   init_svcboot,  ROT0, "bootleg", "SNK vs. Capcom - SVC Chaos (bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, svcplus,    svc,      neogeo_noslot,   neogeo, neogeo_state,   init_svcplus,  ROT0, "bootleg", "SNK vs. Capcom - SVC Chaos Plus (bootleg set 1)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, svcplusa,   svc,      neogeo_noslot,   neogeo, neogeo_state,   init_svcplusa, ROT0, "bootleg", "SNK vs. Capcom - SVC Chaos Plus (bootleg set 2)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, svcsplus,   svc,      neogeo_noslot,   neogeo, neogeo_state,   init_svcsplus, ROT0, "bootleg", "SNK vs. Capcom - SVC Chaos Super Plus (bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, samsho5,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_samsho5,  ROT0, "Yuki Enterprise / SNK Playmore", "Samurai Shodown V / Samurai Spirits Zero (NGM-2700)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, samsho5h,   samsho5,  neogeo_noslot,   neogeo, neogeo_state,   init_samsho5,  ROT0, "Yuki Enterprise / SNK Playmore", "Samurai Shodown V / Samurai Spirits Zero (NGH-2700)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, samsho5b,   samsho5,  neogeo_noslot,   neogeo, neogeo_state,   init_samsho5b, ROT0, "bootleg", "Samurai Shodown V / Samurai Spirits Zero (bootleg)", MACHINE_SUPPORTS_SAVE ) // different program scrambling
GAME( 2003, kf2k3pcb,   0,        neogeo_noslot,   neogeo, neogeo_state,   init_kf2k3pcb, ROT0, "SNK Playmore", "The King of Fighters 2003 (Japan, JAMMA PCB)", MACHINE_SUPPORTS_SAVE ) // not a clone of neogeo because it's NOT a neogeo cart.
GAME( 2003, kof2003,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_kof2003,  ROT0, "SNK Playmore", "The King of Fighters 2003 (NGM-2710)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kof2003h,   kof2003,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2003h, ROT0, "SNK Playmore", "The King of Fighters 2003 (NGH-2710)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, kf2k3bl,    kof2003,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2003b, ROT0, "bootleg", "The King of Fighters 2003 (bootleg set 1)", MACHINE_SUPPORTS_SAVE ) // zooming is wrong because its a bootleg of the pcb version on a cart (unless it was a bootleg pcb with the new bios?)
GAME( 2003, kf2k3bla,   kof2003,  neogeo_noslot,   neogeo, neogeo_state,   init_kf2k3pl,  ROT0, "bootleg", "The King of Fighters 2003 (bootleg set 2)", MACHINE_SUPPORTS_SAVE ) // zooming is wrong because its a bootleg of the pcb version on a cart
GAME( 2003, kf2k3pl,    kof2003,  neogeo_noslot,   neogeo, neogeo_state,   init_kf2k3pl,  ROT0, "bootleg", "The King of Fighters 2004 Plus / Hero (The King of Fighters 2003 bootleg)", MACHINE_SUPPORTS_SAVE ) // zooming is wrong because its a bootleg of the pcb version on a cart
GAME( 2003, kf2k3upl,   kof2003,  neogeo_noslot,   neogeo, neogeo_state,   init_kf2k3upl, ROT0, "bootleg", "The King of Fighters 2004 Ultra Plus (The King of Fighters 2003 bootleg)", MACHINE_SUPPORTS_SAVE ) // zooming is wrong because its a bootleg of the pcb version on a cart
GAME( 2004, samsh5sp,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_samsh5sp, ROT0, "Yuki Enterprise / SNK Playmore", "Samurai Shodown V Special / Samurai Spirits Zero Special (NGM-2720)", MACHINE_SUPPORTS_SAVE )
GAME( 2004, samsh5sph,  samsh5sp, neogeo_noslot,   neogeo, neogeo_state,   init_samsh5sp, ROT0, "Yuki Enterprise / SNK Playmore", "Samurai Shodown V Special / Samurai Spirits Zero Special (NGH-2720) (2nd release, less censored)", MACHINE_SUPPORTS_SAVE )
GAME( 2004, samsh5spho, samsh5sp, neogeo_noslot,   neogeo, neogeo_state,   init_samsh5sp, ROT0, "Yuki Enterprise / SNK Playmore", "Samurai Shodown V Special / Samurai Spirits Zero Special (NGH-2720) (1st release, censored)", MACHINE_SUPPORTS_SAVE )

/* Alpha Denshi Co. / ADK (changed name in 1993) */
GAME( 1990, maglord,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Alpha Denshi Co.", "Magician Lord (NGM-005)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, maglordh,   maglord,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Alpha Denshi Co.", "Magician Lord (NGH-005)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, ncombat,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Alpha Denshi Co.", "Ninja Combat (NGM-009)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, ncombath,   ncombat,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Alpha Denshi Co.", "Ninja Combat (NGH-009)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, bjourney,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Alpha Denshi Co.", "Blue's Journey / Raguy (ALM-001)(ALH-001)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, crsword,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Alpha Denshi Co.", "Crossed Swords (ALM-002)(ALH-002)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, trally,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Alpha Denshi Co.", "Thrash Rally (ALM-003)(ALH-003)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, ncommand,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Alpha Denshi Co.", "Ninja Commando", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wh1,        neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Alpha Denshi Co.", "World Heroes (ALM-005)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wh1h,       wh1,      neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Alpha Denshi Co.", "World Heroes (ALH-005)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wh1ha,      wh1,      neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Alpha Denshi Co.", "World Heroes (set 3)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, wh2,        neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "ADK",              "World Heroes 2 (ALM-006)(ALH-006)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, wh2j,       neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "ADK / SNK",        "World Heroes 2 Jet (ADM-007)(ADH-007)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, aodk,       neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "ADK / SNK",        "Aggressors of Dark Kombat / Tsuukai GANGAN Koushinkyoku (ADM-008)(ADH-008)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, whp,        neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "ADK / SNK",        "World Heroes Perfect", MACHINE_SUPPORTS_SAVE )
GAME( 1995, mosyougi,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "ADK / SNK",        "Syougi No Tatsujin - Master of Syougi", MACHINE_SUPPORTS_SAVE )
GAME( 1996, overtop,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "ADK",              "Over Top", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ninjamas,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "ADK / SNK",        "Ninja Master's - haoh-ninpo-cho", MACHINE_SUPPORTS_SAVE )
GAME( 1996, twinspri,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "ADK / SNK",        "Twinkle Star Sprites", MACHINE_SUPPORTS_SAVE )
GAME( 1996, zintrckb,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "bootleg",             "Zintrick / Oshidashi Zentrix (bootleg of CD version)", MACHINE_SUPPORTS_SAVE )

/* Aicom (was a part of Sammy) / Yumekobo (changed name in 1996) */
GAME( 1992, viewpoin,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Sammy / Aicom", "Viewpoint", MACHINE_SUPPORTS_SAVE )
GAME( 1994, janshin,    neogeo,   neogeo_mj,       mjneogeo, neogeo_state, init_neogeo,   ROT0, "Aicom", "Jyanshin Densetsu - Quest of Jongmaster", MACHINE_SUPPORTS_SAVE )
GAME( 1995, pulstar,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Aicom", "Pulstar", MACHINE_SUPPORTS_SAVE )
GAME( 1998, blazstar,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Yumekobo", "Blazing Star", MACHINE_SUPPORTS_SAVE )
GAME( 1999, preisle2,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_preisle2, ROT0, "Yumekobo", "Prehistoric Isle 2" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */

/* Data East Corporation */
GAME( 1993, spinmast,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Data East Corporation", "Spin Master / Miracle Adventure", MACHINE_SUPPORTS_SAVE )
GAME( 1994, wjammers,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Data East Corporation", "Windjammers / Flying Power Disc", MACHINE_SUPPORTS_SAVE )
GAME( 1994, karnovr,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Data East Corporation", "Karnov's Revenge / Fighter's History Dynamite", MACHINE_SUPPORTS_SAVE )
GAME( 1994, strhoop,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Data East Corporation", "Street Hoop / Street Slam / Dunk Dream (DEM-004)(DEH-004)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ghostlop,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Data East Corporation", "Ghostlop (prototype)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, magdrop2,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Data East Corporation", "Magical Drop II", MACHINE_SUPPORTS_SAVE )
GAME( 1997, magdrop3,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Data East Corporation", "Magical Drop III", MACHINE_SUPPORTS_SAVE )

/* Eleven */
GAME( 2000, nitd,       neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_nitd,     ROT0, "Eleven / Gavaking", "Nightmare in the Dark" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2001, nitdbl,     nitd,     neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "bootleg", "Nightmare in the Dark (bootleg)" , MACHINE_SUPPORTS_SAVE )

/* Face */
GAME( 1994, gururin,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Face", "Gururin", MACHINE_SUPPORTS_SAVE )
GAME( 1997, miexchng,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Face", "Money Puzzle Exchanger / Money Idol Exchanger", MACHINE_SUPPORTS_SAVE )
GAME( 1997, dragonsh,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Face", "Dragon's Heaven (development board)", MACHINE_IS_INCOMPLETE | MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE ) // same ID code as Voltage Fighter Gowkaizer, developed by ex-Technos staff

/* Hudson Soft */
GAME( 1994, panicbom,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Eighting / Hudson", "Panic Bomber", MACHINE_SUPPORTS_SAVE )
GAME( 1995, kabukikl,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Hudson", "Far East of Eden - Kabuki Klash / Tengai Makyou - Shin Den", MACHINE_SUPPORTS_SAVE )
GAME( 1997, neobombe,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Hudson", "Neo Bomberman", MACHINE_SUPPORTS_SAVE )

/* Monolith Corp. */
GAME( 1990, minasan,    neogeo,   neogeo_mj,       mjneogeo, neogeo_state, init_neogeo,   ROT0, "Monolith Corp.", "Minasanno Okagesamadesu! Daisugorokutaikai (MOM-001)(MOH-001)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, bakatono,   neogeo,   neogeo_mj,       mjneogeo, neogeo_state, init_neogeo,   ROT0, "Monolith Corp.", "Bakatonosama Mahjong Manyuuki (MOM-002)(MOH-002)", MACHINE_SUPPORTS_SAVE )

/* Nazca (later acquired by SNK) */
GAME( 1996, turfmast,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Nazca", "Neo Turf Masters / Big Tournament Golf", MACHINE_SUPPORTS_SAVE )
GAME( 1996, mslug,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Nazca", "Metal Slug - Super Vehicle-001", MACHINE_SUPPORTS_SAVE )

/* NMK */
GAME( 1994, zedblade,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "NMK", "Zed Blade / Operation Ragnarok", MACHINE_SUPPORTS_SAVE )

/* Psikyo */
GAME( 1999, s1945p,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_s1945p,   ROT0, "Psikyo", "Strikers 1945 Plus" , MACHINE_SUPPORTS_SAVE )   /* Encrypted GFX */

/* Saurus */
GAME( 1995, quizkof,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Saurus", "Quiz King of Fighters (SAM-080)(SAH-080)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, quizkofk,   quizkof,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Saurus", "Quiz King of Fighters (Korean release)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, stakwin,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Saurus", "Stakes Winner / Stakes Winner - GI kinzen seiha e no michi", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ragnagrd,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Saurus", "Ragnagard / Shin-Oh-Ken", MACHINE_SUPPORTS_SAVE )
GAME( 1996, pgoal,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Saurus", "Pleasure Goal / Futsal - 5 on 5 Mini Soccer (NGM-219)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ironclad,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Saurus", "Choutetsu Brikin'ger - Iron clad (prototype)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ironclado,  ironclad, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "bootleg", "Choutetsu Brikin'ger - Iron clad (prototype, bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, stakwin2,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Saurus", "Stakes Winner 2", MACHINE_SUPPORTS_SAVE )
GAME( 1997, shocktro,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Saurus", "Shock Troopers (set 1)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, shocktroa,  shocktro, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Saurus", "Shock Troopers (set 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, shocktr2,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Saurus", "Shock Troopers - 2nd Squad", MACHINE_SUPPORTS_SAVE )
GAME( 1998, lans2004,   shocktr2, neogeo_noslot,   neogeo, neogeo_state,   init_lans2004, ROT0, "bootleg", "Lansquenet 2004 (Shock Troopers - 2nd Squad bootleg)", MACHINE_SUPPORTS_SAVE )

/* Sunsoft */
GAME( 1995, galaxyfg,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Sunsoft", "Galaxy Fight - Universal Warriors", MACHINE_SUPPORTS_SAVE )
GAME( 1996, wakuwak7,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Sunsoft", "Waku Waku 7", MACHINE_SUPPORTS_SAVE )

/* Taito */
GAME( 1994, pbobblen,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Taito", "Puzzle Bobble / Bust-A-Move (Neo-Geo) (NGM-083)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, pbobblenb,  pbobblen, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "bootleg", "Puzzle Bobble / Bust-A-Move (Neo-Geo) (bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, pbobbl2n,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Taito (SNK license)", "Puzzle Bobble 2 / Bust-A-Move Again (Neo-Geo)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, pnyaa,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_pnyaa,    ROT0, "Aiky / Taito", "Pochi and Nyaa", MACHINE_SUPPORTS_SAVE )

/* Takara */
GAME( 1995, marukodq,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Takara", "Chibi Marukochan Deluxe Quiz", MACHINE_SUPPORTS_SAVE )

/* Technos Japan */
GAME( 1995, doubledr,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Technos Japan", "Double Dragon (Neo-Geo)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, gowcaizr,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Technos Japan", "Voltage Fighter - Gowcaizer / Choujin Gakuen Gowcaizer", MACHINE_SUPPORTS_SAVE )
GAME( 1996, sdodgeb,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Technos Japan", "Super Dodge Ball / Kunio no Nekketsu Toukyuu Densetsu", MACHINE_SUPPORTS_SAVE )

/* Tecmo */
GAME( 1996, tws96,      neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Tecmo", "Tecmo World Soccer '96", MACHINE_SUPPORTS_SAVE )

/* Viccom */
GAME( 1994, fightfev,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Viccom", "Fight Fever (set 1)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, fightfeva,  fightfev, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Viccom", "Fight Fever (set 2)", MACHINE_SUPPORTS_SAVE )

/* Video System Co. */
GAME( 1994, pspikes2,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Video System Co.", "Power Spikes II (NGM-068)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, sonicwi2,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Video System Co.", "Aero Fighters 2 / Sonic Wings 2", MACHINE_SUPPORTS_SAVE )
GAME( 1995, sonicwi3,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Video System Co.", "Aero Fighters 3 / Sonic Wings 3", MACHINE_SUPPORTS_SAVE )
GAME( 1997, popbounc,   neogeo,   neogeo_dial,     neogeo, neogeo_state,   init_neogeo,   ROT0, "Video System Co.", "Pop 'n Bounce / Gapporin", MACHINE_SUPPORTS_SAVE )

/* Visco */
GAME( 1992, androdun,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Visco", "Andro Dunos (NGM-049)(NGH-049)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, puzzledp,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Taito (Visco license)", "Puzzle De Pon!", MACHINE_SUPPORTS_SAVE )
GAME( 1996, neomrdo,    neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Visco", "Neo Mr. Do!", MACHINE_SUPPORTS_SAVE )
GAME( 1995, goalx3,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Visco", "Goal! Goal! Goal!", MACHINE_SUPPORTS_SAVE )
GAME( 1996, neodrift,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Visco", "Neo Drift Out - New Technology", MACHINE_SUPPORTS_SAVE )
GAME( 1996, breakers,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Visco", "Breakers", MACHINE_SUPPORTS_SAVE )
GAME( 1997, puzzldpr,   puzzledp, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Taito (Visco license)", "Puzzle De Pon! R!", MACHINE_SUPPORTS_SAVE )
GAME( 1998, breakrev,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Visco", "Breakers Revenge", MACHINE_SUPPORTS_SAVE )
GAME( 1998, flipshot,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Visco", "Battle Flip Shot", MACHINE_SUPPORTS_SAVE )
GAME( 1999, ctomaday,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Visco", "Captain Tomaday", MACHINE_SUPPORTS_SAVE )
GAME( 1999, ganryu,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_ganryu,   ROT0, "Visco", "Ganryu / Musashi Ganryuki" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2000, bangbead,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_bangbead, ROT0, "Visco", "Bang Bead", MACHINE_SUPPORTS_SAVE )
GAME( 2000, b2b,        neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Visco", "Bang Bang Busters (2010 NCI release)" , MACHINE_SUPPORTS_SAVE )

/* Mega Enterprise */
GAME( 2002, mslug4,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_mslug4,   ROT0, "Mega / Playmore", "Metal Slug 4 (NGM-2630)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, mslug4h,    mslug4,   neogeo_noslot,   neogeo, neogeo_state,   init_mslug4,   ROT0, "Mega / Playmore", "Metal Slug 4 (NGH-2630)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, ms4plus,    mslug4,   neogeo_noslot,   neogeo, neogeo_state,   init_ms4plus,  ROT0, "bootleg", "Metal Slug 4 Plus (bootleg)", MACHINE_SUPPORTS_SAVE )

/* Evoga */
GAME( 2002, rotd,       neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_rotd,     ROT0, "Evoga / Playmore", "Rage of the Dragons (NGM-264?)", MACHINE_SUPPORTS_SAVE )

/* Atlus */
GAME( 2002, matrim,     neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_matrim,   ROT0, "Noise Factory / Atlus", "Matrimelee / Shin Gouketsuji Ichizoku Toukon (NGM-2660) (NGH-2660)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, matrimbl,   matrim,   neogeo_noslot,   neogeo, neogeo_state,   init_matrimbl, ROT0, "bootleg", "Matrimelee / Shin Gouketsuji Ichizoku Toukon (bootleg)", MACHINE_SUPPORTS_SAVE )

/***** Unlicensed commercial releases *****/

/* BrezzaSoft */
GAME( 2001, jockeygp,   neogeo,   neogeo_noslot,   jockeygp, neogeo_state, init_jockeygp, ROT0, "Sun Amusement / BrezzaSoft", "Jockey Grand Prix (set 1)", MACHINE_SUPPORTS_SAVE )
GAME( 2001, jockeygpa,  jockeygp, neogeo_noslot,   jockeygp, neogeo_state, init_jockeygp, ROT0, "Sun Amusement / BrezzaSoft", "Jockey Grand Prix (set 2)", MACHINE_SUPPORTS_SAVE )
GAME( 2001, vliner,     neogeo,   neogeo_noctrl,   vliner, neogeo_state,   init_vliner,   ROT0, "Dyna / BrezzaSoft", "V-Liner (set 1)", MACHINE_SUPPORTS_SAVE )
GAME( 2001, vlinero,    vliner,   neogeo_noctrl,   vliner, neogeo_state,   init_vliner,   ROT0, "Dyna / BrezzaSoft", "V-Liner (set 2)", MACHINE_SUPPORTS_SAVE )

/* Kyle Hodgetts */
GAME( 2000, diggerma,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Kyle Hodgetts", "Digger Man (prototype)", MACHINE_SUPPORTS_SAVE )

/* Vektorlogic */
GAME( 2004, sbp,        neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_sbp,      ROT0, "Vektorlogic", "Super Bubble Pop", MACHINE_NOT_WORKING )

/* NG:DEV.TEAM */
GAME( 2005, lasthope,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "NG:DEV.TEAM", "Last Hope (bootleg AES to MVS conversion, no coin support)", MACHINE_SUPPORTS_SAVE ) // wasn't actually released on MVS but bootleg carts have been sold, this doesn't accept coins, runs like a console game

/* Update */
GAME( 2003, samsho5a,   samsho5,  neogeo_noslot,   neogeo, neogeo_state,   init_samsho5,  ROT0, "Yuki Enterprise / SNK Playmore", "Samurai Shodown V / Samurai Spirits Zero (NGM-2700, set 2)", MACHINE_SUPPORTS_SAVE )
GAME( 2001, sengoku3a,  sengoku3, neogeo_noslot,   neogeo, neogeo_state,   init_sengoku3, ROT0, "Noise Factory / SNK", "Sengoku 3 / Sengoku Densho 2001 (set 2)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */
GAME( 2001, vlinernw,   neogeo,   neogeo_noctrl,   vliner, neogeo_state,   init_vliner,   ROT0, "Dyna / BrezzaSoft", "V-Liner (v0.7a)", MACHINE_SUPPORTS_SAVE )
GAME( 2001, vliner7e,   vliner,   neogeo_noctrl,   vliner, neogeo_state,   init_vliner,   ROT0, "Dyna / BrezzaSoft", "V-Liner (v0.7e)", MACHINE_SUPPORTS_SAVE )
GAME( 2001, vliner6e,   vliner,   neogeo_noctrl,   vliner, neogeo_state,   init_vliner,   ROT0, "Dyna / BrezzaSoft", "V-Liner (v0.6e)", MACHINE_SUPPORTS_SAVE )
GAME( 2001, vliner54,   vliner,   neogeo_noctrl,   vliner, neogeo_state,   init_vliner,   ROT0, "Dyna / BrezzaSoft", "V-Liner (v0.54)", MACHINE_SUPPORTS_SAVE )
GAME( 2001, vliner53,   vliner,   neogeo_noctrl,   vliner, neogeo_state,   init_vliner,   ROT0, "Dyna / BrezzaSoft", "V-Liner (v0.53)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, wh2h,       wh2,      neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "ADK",              "World Heroes 2 (ALH-006)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, rbff1k,     rbff1,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Real Bout Fatal Fury / Real Bout Garou Densetsu (Korean release)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, rbff1ka,    rbff1,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Real Bout Fatal Fury / Real Bout Garou Densetsu (Korean release, bug fix revision)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, roboarma,   roboarmy, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Robo Army (NGM-032 ~ NGH-032)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, rotdh,      rotd,     neogeo_noslot,   neogeo, neogeo_state,   init_rotd,     ROT0, "Evoga / Playmore", "Rage of the Dragons (NGH-2640?)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, kof99ka,    kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (Korean release, non-encrypted program)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted Code & GFX */
GAME( 1992, kotm2a,     kotm2,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "King of the Monsters 2 - The Next Thing (older)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, bjourneyh,  bjourney, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Alpha Denshi Co.", "Blue's Journey / Raguy (ALH-001)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, burningfpa, burningf, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Burning Fight (prototype, ver 23.3, 910326)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, burningfpb, burningf, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Burning Fight (prototype, newer, V07)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, garouha,    garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garou,    ROT0, "SNK", "Garou - Mark of the Wolves (NGH-2530)" , MACHINE_SUPPORTS_SAVE ) /* Encrypted Code & GFX */
GAME( 1991, gpilotsp,   gpilots,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Ghost Pilots (prototype)", MACHINE_SUPPORTS_SAVE )
GAME( 2003, pnyaanv,    pnyaa,    neogeo_noslot,   neogeo, neogeo_state,   init_pnyaa,    ROT0, "Aiky / Taito", "Pochi and Nyaa (Ver 2.02)", MACHINE_SUPPORTS_SAVE ) // this version does not show the web address on the title screen
GAME( 1992, viewpoinp,  viewpoin, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Sammy / Aicom", "Viewpoint (prototype)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, stakwindev, neogeo,   no_watchdog,     neogeo, neogeo_state,   init_neogeo,   ROT0, "Saurus", "Stakes Winner (early development board)", MACHINE_SUPPORTS_SAVE | MACHINE_NOT_WORKING | MACHINE_IS_INCOMPLETE )
GAME( 1995, froman2b,   neogeo,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "bootleg", "Idol Mahjong Final Romance 2 (Neo-Geo, bootleg of CD version)", MACHINE_SUPPORTS_SAVE )

/* Earlier */
GAME( 1991, 2020bbe,     2020bb,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK / Pallas", "2020 Super Baseball (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, 3countbe,    3countb,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "3 Count Bout / Fire Suplex (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, aof3e,       aof3,     neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Art of Fighting 3 - The Path of the Warrior / Art of Fighting - Ryuuko no Ken Gaiden (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, blazstre,    blazstar, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Yumekobo", "Blazing Star (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, goalx3e,     goalx3,   neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Visco", "Goal! Goal! Goal! (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, kabukikle,   kabukikl, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Hudson", "Far East of Eden - Kabuki Klash / Tengai Makyou - Shin Den (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, kof95e,      kof95,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The King of Fighters '95 (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, kotm2e,      kotm2,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "King of the Monsters 2 - The Next Thing (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, magdrp3e,    magdrop3, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Data East Corporation", "Magical Drop III (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, msluge,      mslug,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Nazca", "Metal Slug - Super Vehicle-001 (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, neobombee,   neobombe, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Hudson", "Neo Bomberman (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, neodrifte,   neodrift, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Visco", "Neo Drift Out - New Technology (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ninjamse,    ninjamas, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "ADK / SNK",        "Ninja Master's - haoh-ninpo-cho (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, pulstare,    pulstar,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Aicom", "Pulstar (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ragnagrde,   ragnagrd, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Saurus", "Ragnagard / Shin-Oh-Ken (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, rbffspece,   rbffspec, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Real Bout Fatal Fury Special / Real Bout Garou Densetsu Special (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, roboarme,    roboarmy, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Robo Army (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, samsho3e,    samsho3,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Samurai Shodown III / Samurai Spirits - Zankurou Musouken (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, samsho4e,    samsho4,  neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "Samurai Shodown IV - Amakusa's Revenge / Samurai Spirits - Amakusa Kourin (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, shocktre,    shocktro, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Saurus", "Shock Troopers (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, sonicw3e,    sonicwi3, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Video System Co.", "Aero Fighters 3 / Sonic Wings 3 (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ssidek4e,    ssideki4, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "SNK", "The Ultimate 11 - The SNK Football Championship / Tokuten Ou - Honoo no Libero (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, turfmste,    turfmast, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Nazca", "Neo Turf Masters / Big Tournament Golf (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, twinspre,    twinspri, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "ADK / SNK",        "Twinkle Star Sprites (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, tws96e,      tws96,    neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Tecmo", "Tecmo World Soccer '96 (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, wakuwk7e,    wakuwak7, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Sunsoft", "Waku Waku 7 (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, whpe,        whp,      neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "ADK / SNK",        "World Heroes Perfect (Earlier)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, wjammere,    wjammers, neogeo_noslot,   neogeo, neogeo_state,   init_neogeo,   ROT0, "Data East Corporation", "Windjammers / Flying Power Disc (Earlier)", MACHINE_SUPPORTS_SAVE )

/* Multi Game Doctor 2 */
GAME( 1993, 3countbd,  3countb,  neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "3 Count Bout (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, 2020bbd,   2020bb,   neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK / Pallas", "2020 Super Baseball (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, alpham2d,  alpham2,  neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Alpha Mission II (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, androdund, androdun, neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "Visco", "Andro Dunos (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, aofd,      aof,      neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Art of Fighting (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, bakatonod, bakatono, neogeo_mj,       neogeo,   neogeo_state, init_neogeo,   ROT0, "Monolith Corp.", "Bakatonosama Mahjong Manyuki (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, bstarsd,   bstars,   neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Baseball Stars Professional (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, burningfd, burningf, neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Burning Fight (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, crswordd,  crsword,  neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "Alpha Denshi Co.", "Crossed Swords (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, cyberlipd, cyberlip, neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Cyber-Lip (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, eightmand, eightman, neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK / Pallas", "Eight Man (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, fatfury1d, fatfury1, neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Fatal Fury (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, fbfrenzyd, fbfrenzy, neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Football Frenzy (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, gpilotsd,  gpilots,  neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Ghost Pilots (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, joyjoyd,   joyjoy,   neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Puzzled (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, kotmd,     kotm,     neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "King of the Monsters (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, lbowlingd, lbowling, neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "League Bowling (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, lresortd,  lresort,  neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Last Resort (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, maglordd,  maglord,  neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "Alpha Denshi Co.", "Magician Lord (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, minasand,  minasan,  neogeo_mj,       neogeo,   neogeo_state, init_neogeo,   ROT0, "Monolith Corp.", "Minnasanno Okagesamadesu (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, mutnatd,   mutnat,   neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Mutation Nation (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, ncombatd,  ncombat,  neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "Alpha Denshi Co.", "Ninja Combat (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, ncommandd, ncommand, neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "Alpha Denshi Co", "Ninja Commando (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, ridherod,  ridhero,  neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Riding Hero (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, roboarmyd, roboarmy, neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Robo Army (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, sengokud,  sengoku,  neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Sengoku (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, sengoku2d, sengoku2, neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Sengoku 2 (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, socbrawld, socbrawl, neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Soccer Brawl (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, superspyd, superspy, neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "The Super Spy (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, tpgolfd,   tpgolf,   neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "SNK", "Top Player's Golf (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, trallyd,   trally,   neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "Alpha Denshi Co.", "Thrash Rally (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wh1d,      wh1,      neogeo_noslot,   neogeo,   neogeo_state, init_neogeo,   ROT0, "Alpha Denshi Co.", "World Heroes (Multi Game Doctor 2)", MACHINE_SUPPORTS_SAVE )

/* CD conversion */
GAME( 1991, 2020bbcd,          2020bb,   neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "2020 Super Baseball (CD conversion)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, crswd2bl,          neogeo,   neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "Crossed Swords 2 (CD conversion)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, gpilotscd,         gpilots,  neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "Ghost Pilots (CD conversion)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ironcladcd,        ironclad, neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "Ironclad (CD conversion)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2007, joyjoycd,          joyjoy,   neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "Puzzled (CD conversion)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, joyjoycd1,         joyjoy,   neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "Puzzled (CD conversion)(Set 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, lbowlingcd,        lbowling, neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "League Bowling (CD to MVS Conversion)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, pbobblencd,        pbobblen, neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "Puzzle Bobble (CD conversion)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, pspikes2cd,        pspikes2, neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "Power Spikes II (CD conversion)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2007, sengokucd,         sengoku,  neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "Sengoku (CD conversion)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, ssidekicd,         ssideki,  neogeo_noslot, neogeo, neogeo_state,     init_fatfury2,  ROT0, "CD_conv",        "Super Sidekicks (CD conversion)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, strhoopcd,         strhoop,  neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "Street Hoop (CD conversion)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, superspycd,        superspy, neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "The Super Spy (CD conversion)", MACHINE_SUPPORTS_SAVE )
GAME( 2007, tpgolfcd,          tpgolf,   neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "Top Player's Golf (CD conversion)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, trallycd,          trally,   neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "Thrash Rally (CD conversion)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
GAME( 1996, zintrkcd,          zintrckb, neogeo_noslot, neogeo, neogeo_state,     init_neogeo,    ROT0, "CD_conv",        "ZinTricK (CD conversion)", MACHINE_SUPPORTS_SAVE )

/* HomeBrew */
GAME( 2021, abyssal,      neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Kako Eimon", "Abyssal Infants", MACHINE_SUPPORTS_SAVE )
GAME( 2021, abyssal1,     abyssal,  neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Kako Eimon", "Abyssal Infants (newer version)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, cabalng,      neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "iq132", "Cabal (Neo-Geo port)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, cabalng1,     cabalng,  neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "iq132", "Cabal (Neo-Geo port, sprite fix)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, caravan,      neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Fullset", "Project Neon Caravan Edition (Prealpha 0.4.19)", MACHINE_SUPPORTS_SAVE )
GAME( 2006, cnbe,         neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Blastar", "Codename: Blut Engel (2006-01-19)(Homebrew)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, cnbe2018,     cnbe,     neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Blastar", "Codename: Blut Engel (2018-09-05)(Homebrew)", MACHINE_SUPPORTS_SAVE )
GAME( 2013, cphd,         neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Le Cortex", "Crouching Pony Hidden Dragon Demo", MACHINE_SUPPORTS_SAVE )
GAME( 1990, columnsn,     neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Jeff Kurtz", "Columns (NeoGeo)(Homebrew)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, columnsncd,   columnsn, neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Jeff Kurtz", "Columns (CD conversion)", MACHINE_SUPPORTS_SAVE )
GAME( 2006, ffeast,       neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Rastersoft", "Frog Feast (NeoGeo)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, hypernoid,    neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "M.Priewe", "Hypernoid (2021-11-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, lhbb,         lasthope, neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Elrayzeur", "Last Hope (Blue Bullets)", MACHINE_SUPPORTS_SAVE )
GAME( 2007, lhcdb,        lasthope, neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "NG:Dev.Team", "Last Hope CD Beta", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
GAME( 2007, lhcdba,       lasthope, neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "NG:Dev.Team", "Last Hope (Neo CD conversion)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
GAME( 2021, looptris,     neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Blastar", "Looptris (2021-12-26)", MACHINE_SUPPORTS_SAVE )
GAME( 2005, ltorb,        neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Blastar", "Jonas Indiana and The Lost Temple of RA (beta - 20050717)", MACHINE_SUPPORTS_SAVE )
GAME( 2002, neonopon,     neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Blastar", "Neo No Panepon V.0.2", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
GAME( 2010, neopang,      neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "CeL", "Neo Pang", MACHINE_SUPPORTS_SAVE )
GAME( 2002, neopong,      neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Neodev", "Neo Pong (v1.1)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
GAME( 2002, neoponga,     neopong,  no_watchdog,     neogeo,  neogeo_state, init_neogeo,   ROT0, "Neodev", "Neo Pong (v1.0)", MACHINE_SUPPORTS_SAVE )
GAME( 2012, neothund,     neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Sebastian Mihai", "Neo Thunder", MACHINE_SUPPORTS_SAVE )
GAME( 2019, neotrisd1,    neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Totologic", "Neotris Demo 1", MACHINE_SUPPORTS_SAVE )
GAME( 2020, neotrisd2,    neotrisd1,neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Totologic", "Neotris Demo 2", MACHINE_SUPPORTS_SAVE )
GAME( 2020, neotrisd3,    neotrisd1,neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Totologic", "Neotris Demo 3", MACHINE_SUPPORTS_SAVE )
GAME( 2020, bonusstage,   neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Totologic", "Bonus Stage", MACHINE_SUPPORTS_SAVE )
GAME( 2020, nblktiger,    neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "OzzyOuzo", "Neo Black Tiger", MACHINE_IS_INCOMPLETE | MACHINE_SUPPORTS_SAVE )
GAME( 2006, ngem2k,       neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Blastar", "NGEM2K (Beta 2006-01-18)", MACHINE_SUPPORTS_SAVE )
GAME( 2008, ngtetris,     neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Crim/Stephen", "NeoGeo 2-Player Tetris", MACHINE_SUPPORTS_SAVE )
GAME( 2020, nsmb,         neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "OzzyOuzo", "New! Super Mario Bros.", MACHINE_SUPPORTS_SAVE )
GAME( 2012, santabll,     neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "M.Priewe", "Santaball", MACHINE_SUPPORTS_SAVE )
GAME( 2018, seafight,     neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "kl3mousse", "Sea Fighter 0.01.009", MACHINE_SUPPORTS_SAVE )
GAME( 2022, teotb,        neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "OzzyOuzo", "The Eye of Typhoon (Tsunami Edition, beta 3, 2022-03-12)", MACHINE_SUPPORTS_SAVE )
GAME( 2012, timesup,      neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "NGF Dev. Inc", "Time's Up!", MACHINE_SUPPORTS_SAVE )
GAME( 2012, timesupd,     neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "NGF Dev. Inc", "Time's Up! (Demo)", MACHINE_SUPPORTS_SAVE )
GAME( 2011, totc,         neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "FACE Corporation / N.C.I - Le Cortex", "Treasure of the Caribbean", MACHINE_SUPPORTS_SAVE )
GAME( 2019, xeno,         neogeo,   neogeo_noslot,   neogeo,  neogeo_state, init_neogeo,   ROT0, "Bitmap Bureau", "Xeno Crisis v1.0.0", MACHINE_SUPPORTS_SAVE )

// Last Hope Pink Bullets (c)2008 - MVS/AES
// Fast Striker (c)2010 - MVS/AES
// Fast Striker 1.5 (c)2010 - MVS/AES
// GunLord (c)2012 - MVS/AES
// Neo XYX (c)2013 - MVS/AES
// Razion (c)2014 - MVS/AES?
// Kraut Buster (c)2016 - MVS/AES

/* N.C.I - LE CORTEX */
// Treasure of the Caribbean (c)2011 - AES only (no credits system if ran on an MVS, Freeplay)

/* NEOBITZ */
// Knight's Chance (c)2014 - MVS/AES
