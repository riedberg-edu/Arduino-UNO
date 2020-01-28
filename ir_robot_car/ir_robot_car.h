

////////// IR REMOTE CODES //////////

////////// IR REMOTE CODES Technisat //////////
#define auto_on_Technisat 2700
#define auto_off_Technisat 652
#define CSA1 641
#define CSA2 642
#define CSA3 643
#define CSA4 644
#define CSA5 645
#define CSA6 646
#define CSA7 647
#define CSA8 648
#define CSA9 649
#define vor_Technisat 3363236978
#define zurueck_Technisat 3380014599
#define links_Technisat 2239869123
#define rechts_Technisat 2860788123
#define stoppen_Technisat 2475633871
#define vor2_Technisat 2605695303
#define zurueck2_Technisat 2588917682
#define links2_Technisat 1932877326
#define rechts2_Technisat 1311958330
#define stoppen2_Technisat 3493298410

////////// IR REMOTE CODES Pinnacle //////////
#define auto_on_Pinnacle 0x7EAB68DF
#define auto_off_Pinnacle 0x78ECC40D
#define vor_Pinnacle 0x71CAE416
#define zurueck_Pinnacle 0x7C4955E7
#define links_Pinnacle 0x5746DD0F
#define rechts_Pinnacle 0xAA4671E
#define stoppen_Pinnacle 0xAB7814A6
#define vor2_Pinnacle 0x23F85D88
#define zurueck2_Pinnacle 0x30A6E185
#define links2_Pinnacle 0xBA468B1
#define rechts2_Pinnacle 0x5646DB7C
#define stoppen2_Pinnacle 0xC921DD24

////////// IR REMOTE CODES Universal //////////
#define auto_on_Universal 1
#define auto_off_Universal 6
#define vor_Universal 3
#define zurueck_Universal 3
#define links_Universal 2
#define rechts_Universal 2
#define stoppen_Universal 2
#define vor2_Universal 2
#define zurueck2_Universal 2
#define links2_Universal 1
#define rechts2_Universal 1
#define stoppen2_Universal 3

////////// IR REMOTE CODES Eleego //////////
#define auto_on_Eleego 0xFF30CF // 1
#define auto_off_Eleego 0xFF18E7 //2
#define vor_Eleego 0xFF906F
#define zurueck_Eleego 0xFFE01F
#define links_Eleego 0xFF22DD
#define rechts_Eleego 0xFFC23D
#define stoppen_Eleego 0xFF02FD
#define vor2_Eleego 0x2
#define zurueck2_Eleego 0x2
#define links2_Eleego 0x1
#define rechts2_Eleego 0x1
#define stoppen2_Eleego 0x3

////////// IR REMOTE CODES Makeblock //////////
#define auto_on_Makeblock 0xFFA25D // A
#define auto_off_Makeblock 0xFFE21D // C
#define vor_Makeblock 0xFF02FD
#define zurueck_Makeblock 0xFF9867
#define links_Makeblock 0xFFE01F
#define rechts_Makeblock 0xFF906F
#define stoppen_Makeblock 0xFFA857
#define vor2_Makeblock 0x2
#define zurueck2_Makeblock 0x2
#define links2_Makeblock 0x1
#define rechts2_Makeblock 0x1
#define stoppen2_Makeblock 0x3

////////// IR REMOTE CODES LCDRemote //////////
#define auto_on_LCDRemote 0x61D648B7
#define auto_off_LCDRemote 0x6
#define vor_LCDRemote 0x61D6D827
#define zurueck_LCDRemote 0x61D658A7
#define links_LCDRemote 0x61D620DF
#define rechts_LCDRemote 0x61D6609F
#define stoppen_LCDRemote 0x61D6A05F
#define vor2_LCDRemote 0x2
#define zurueck2_LCDRemote 0x2
#define links2_LCDRemote 0x1
#define rechts2_LCDRemote 0x1
#define stoppen2_LCDRemote 0x3

////////// IR REMOTE CODES PCRemote //////////
#define auto_on_PCRemote 0xC157DE81
#define auto_off_PCRemote 0x3
#define vor_PCRemote 0xFD822A51
#define zurueck_PCRemote 0x1304DA8D
#define links_PCRemote 0x4C06E3EB
#define rechts_PCRemote 0xC9B62F1F
#define stoppen_PCRemote 0x5EF4863
#define vor2_PCRemote 0xE2C8
#define zurueck2_PCRemote 0xE286
#define links2_PCRemote 0xE218
#define rechts2_PCRemote 0xE210
#define stoppen2_PCRemote 0xE208

#define IR_Remote_DEV_Technisat 1
#define IR_Remote_DEV_Pinnacle 2
#define IR_Remote_DEV_Eleego 3
#define IR_Remote_DEV_Universal 4
#define IR_Remote_DEV_LCDRemote 5
#define IR_Remote_DEV_PCRemote 6
#define IR_Remote_DEV_Makeblock 7

int IR_Remote_DEV = IR_Remote_DEV_Universal;



// unsigned long Forward_Code;
unsigned long auto_on;
unsigned long auto_off;
unsigned long vor;
unsigned long zurueck;
unsigned long links;
unsigned long rechts;
unsigned long stoppen;
unsigned long vor2;
unsigned long zurueck2;
unsigned long links2;
unsigned long rechts2;
unsigned long stoppen2;



void irConfig (int remote_dev) {
 
  switch (remote_dev) {
    case IR_Remote_DEV_Technisat:
      auto_on = auto_on_Technisat;
      auto_off = auto_off_Technisat;
      vor = vor_Technisat;
      zurueck = zurueck_Technisat;
      links = links_Technisat;
      rechts = rechts_Technisat;
      stoppen = stoppen_Technisat;
      vor2 = vor2_Technisat;
      zurueck2 = zurueck2_Technisat;
      links2 = links2_Technisat;
      rechts2 = rechts2_Technisat;
      stoppen2 = stoppen2_Technisat;
      break;
    case IR_Remote_DEV_Pinnacle:
      auto_on = auto_on_Pinnacle;
      auto_off = auto_off_Pinnacle;
      vor = vor_Pinnacle;
      zurueck = zurueck_Pinnacle;
      links = links_Pinnacle;
      rechts = rechts_Pinnacle;
      stoppen = stoppen_Pinnacle;
      vor2 = vor2_Pinnacle;
      zurueck2 = zurueck2_Pinnacle;
      links2 = links2_Pinnacle;
      rechts2 = rechts2_Pinnacle;
      stoppen2 = stoppen2_Pinnacle;
      break;
    case IR_Remote_DEV_Universal:
      auto_on = auto_on_Universal;
      auto_off = auto_off_Universal;
      vor = vor_Universal;
      zurueck = zurueck_Universal;
      links = links_Universal;
      rechts = rechts_Universal;
      stoppen = stoppen_Universal;
      vor2 = vor2_Universal;
      zurueck2 = zurueck2_Universal;
      links2 = links2_Universal;
      rechts2 = rechts2_Universal;
      stoppen2 = stoppen2_Universal;
      break;
    case IR_Remote_DEV_Eleego:
      auto_on = auto_on_Eleego;
      auto_off = auto_off_Eleego;
      vor = vor_Eleego;
      zurueck = zurueck_Eleego;
      links = links_Eleego;
      rechts = rechts_Eleego;
      stoppen = stoppen_Eleego;
      vor2 = vor2_Eleego;
      zurueck2 = zurueck2_Eleego;
      links2 = links2_Eleego;
      rechts2 = rechts2_Eleego;
      stoppen2 = stoppen2_Eleego;
      break;
    case IR_Remote_DEV_Makeblock:
      auto_on = auto_on_Makeblock;
      auto_off = auto_off_Makeblock;
      vor = vor_Makeblock;
      zurueck = zurueck_Makeblock;
      links = links_Makeblock;
      rechts = rechts_Makeblock;
      stoppen = stoppen_Makeblock;
      vor2 = vor2_Makeblock;
      zurueck2 = zurueck2_Makeblock;
      links2 = links2_Makeblock;
      rechts2 = rechts2_Makeblock;
      stoppen2 = stoppen2_Makeblock;
      break;

    case IR_Remote_DEV_LCDRemote:
      auto_on = auto_on_LCDRemote;
      auto_off = auto_off_LCDRemote;
      vor = vor_LCDRemote;
      zurueck = zurueck_LCDRemote;
      links = links_LCDRemote;
      rechts = rechts_LCDRemote;
      stoppen = stoppen_LCDRemote;
      vor2 = vor2_LCDRemote;
      zurueck2 = zurueck2_LCDRemote;
      links2 = links2_LCDRemote;
      rechts2 = rechts2_LCDRemote;
      stoppen2 = stoppen2_LCDRemote;
      break;

    case IR_Remote_DEV_PCRemote:
      auto_on = auto_on_PCRemote;
      auto_off = auto_off_PCRemote;
      vor = vor_PCRemote;
      zurueck = zurueck_PCRemote;
      links = links_PCRemote;
      rechts = rechts_PCRemote;
      stoppen = stoppen_PCRemote;
      vor2 = vor2_PCRemote;
      zurueck2 = zurueck2_PCRemote;
      links2 = links2_PCRemote;
      rechts2 = rechts2_PCRemote;
      stoppen2 = stoppen2_PCRemote;
      break;

    default: break;
  };
}


