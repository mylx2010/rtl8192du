/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef __WLAN_BSSDEF_H__
#define __WLAN_BSSDEF_H__


#define MAX_IE_SZ	768

#define NDIS_802_11_LENGTH_SSID         32
#define NDIS_802_11_LENGTH_RATES        8
#define NDIS_802_11_LENGTH_RATES_EX     16

// typedef long			NDIS_802_11_RSSI;           // in dBm
// typedef unsigned char   NDIS_802_11_RATES[NDIS_802_11_LENGTH_RATES];        // Set of 8 data rates
typedef unsigned char   NDIS_802_11_RATES_EX[NDIS_802_11_LENGTH_RATES_EX];  // Set of 16 data rates


// typedef  u32  NDIS_802_11_KEY_INDEX;
typedef unsigned long long NDIS_802_11_KEY_RSC;


struct ndis_802_11_ssid {
	u32  SsidLength;
	u8  Ssid[32];
};

enum NDIS_802_11_NETWORK_TYPE {
	NDIS802_11FH,
	NDIS802_11DS,
	NDIS802_11OFDM5,
	NDIS802_11OFDM24,
	NDIS802_11NetworkTypeMax    // not a real type - upper bound
};

typedef struct _NDIS_802_11_CONFIGURATION_FH
{
    u32           Length;             // Length of structure
    u32           HopPattern;         // As defined by 802.11, MSB set
    u32           HopSet;             // to one if non-802.11
    u32           DwellTime;          // units are Kusec
} NDIS_802_11_CONFIGURATION_FH, *PNDIS_802_11_CONFIGURATION_FH;


/*
	FW will only save the channel number in DSConfig.
	ODI Handler will convert the channel number to freq. number.
*/
typedef struct _NDIS_802_11_CONFIGURATION
{
    u32           Length;             // Length of structure
    u32           BeaconPeriod;       // units are Kusec
    u32           ATIMWindow;         // units are Kusec
    u32           DSConfig;           // Frequency, units are kHz
    NDIS_802_11_CONFIGURATION_FH    FHConfig;
} NDIS_802_11_CONFIGURATION, *PNDIS_802_11_CONFIGURATION;



enum NDIS_802_11_NETWORK_INFRASTRUCTURE {
	NDIS802_11IBSS,
	NDIS802_11INFRA,
	NDIS802_11AUTOUNK,
	NDIS802_11INFRA_MAX,     // Not a real value, defined as upper bound
	NDIS802_11APMODE
};

typedef struct _NDIS_802_11_FIXED_IEs
{
  u8  Timestamp[8];
  u16  BeaconInterval;
  u16  Capabilities;
} NDIS_802_11_FIXED_IEs, *PNDIS_802_11_FIXED_IEs;

typedef struct _NDIS_802_11_VARIABLE_IEs
{
  u8  ElementID;
  u8  Length;
  u8  data[1];
} NDIS_802_11_VARIABLE_IEs, *PNDIS_802_11_VARIABLE_IEs;

/*
Length is the 4 bytes multiples of the sume of
	ETH_ALEN + 2 + sizeof (struct ndis_802_11_ssid) + sizeof (u32)
+   sizeof (long) + sizeof (NDIS_802_11_NETWORK_TYPE) + sizeof (NDIS_802_11_CONFIGURATION)
+   sizeof (NDIS_802_11_LENGTH_RATES * sizeof(unsigned char)) + IELength

Except the IELength, all other fields are fixed length. Therefore, we can define a marco to present the
partial sum.
*/

enum NDIS_802_11_AUTHENTICATION_MODE {
	NDIS802_11AUTHMODEOPEN,
	NDIS802_11AUTHMODESHARED,
	NDIS802_11AUTHMODESWITCH,
	NDIS802_11AUTHMODEWPA,
	NDIS802_11AUTHMODEWPAPSK,
	NDIS802_11AUTHMODEWPANONE,
	NDIS802_11AUTHMODEMAX               // Not a real mode, defined as upper bound
};

enum NDIS_802_11_ENCRYPTION_STATUS {
	NDIS802_11WEP_ENABLED,
	NDIS802_11ENCRYPTION1ENABLED = NDIS802_11WEP_ENABLED,
	NDIS802_11WEPDISABLED,
	NDIS802_11ENCRYPTION_DISABLED = NDIS802_11WEPDISABLED,
	NDIS802_11WEPKEYABSENT,
	NDIS802_11ENCRYPTION1KEYABSENT = NDIS802_11WEPKEYABSENT,
	NDIS802_11WEPNOTSUPPORTED,
	NDIS802_11ENCRYPTIONNOTSUPPORTED = NDIS802_11WEPNOTSUPPORTED,
	NDIS802_11ENCRYPTION2ENABLED,
	NDIS802_11ENCRYPTION2KEYABSENT,
	NDIS802_11ENCRYPTION3ENABLED,
	NDIS802_11ENCRYPTION3KEYABSENT
};

#define NDIS_802_11_AI_REQFI_CAPABILITIES      1
#define NDIS_802_11_AI_REQFI_LISTENINTERVAL    2
#define NDIS_802_11_AI_REQFI_CURRENTAPADDRESS  4

#define NDIS_802_11_AI_RESFI_CAPABILITIES      1
#define NDIS_802_11_AI_RESFI_STATUSCODE        2
#define NDIS_802_11_AI_RESFI_ASSOCIATIONID     4

typedef struct _NDIS_802_11_AI_REQFI
{
    u16 Capabilities;
    u16 ListenInterval;
    unsigned char CurrentAPAddress[ETH_ALEN];
} NDIS_802_11_AI_REQFI, *PNDIS_802_11_AI_REQFI;

typedef struct _NDIS_802_11_AI_RESFI
{
    u16 Capabilities;
    u16 StatusCode;
    u16 AssociationId;
} NDIS_802_11_AI_RESFI, *PNDIS_802_11_AI_RESFI;

typedef struct _NDIS_802_11_ASSOCIATION_INFORMATION
{
    u32                   Length;
    u16                  AvailableRequestFixedIEs;
    NDIS_802_11_AI_REQFI    RequestFixedIEs;
    u32                   RequestIELength;
    u32                   OffsetRequestIEs;
    u16                  AvailableResponseFixedIEs;
    NDIS_802_11_AI_RESFI    ResponseFixedIEs;
    u32                   ResponseIELength;
    u32                   OffsetResponseIEs;
} NDIS_802_11_ASSOCIATION_INFORMATION, *PNDIS_802_11_ASSOCIATION_INFORMATION;

// Key mapping keys require a BSSID
typedef struct _NDIS_802_11_KEY
{
    u32           Length;             // Length of this structure
    u32           KeyIndex;
    u32           KeyLength;          // length of key in bytes
    unsigned char BSSID[ETH_ALEN];
    NDIS_802_11_KEY_RSC KeyRSC;
    u8           KeyMaterial[32];     // variable length depending on above field
} NDIS_802_11_KEY, *PNDIS_802_11_KEY;

typedef struct _NDIS_802_11_REMOVE_KEY
{
    u32                   Length;        // Length of this structure
    u32                   KeyIndex;
    unsigned char  BSSID[ETH_ALEN];
} NDIS_802_11_REMOVE_KEY, *PNDIS_802_11_REMOVE_KEY;

typedef struct _NDIS_802_11_WEP
{
    u32     Length;        // Length of this structure
    u32     KeyIndex;      // 0 is the per-client key, 1-N are the global keys
    u32     KeyLength;     // length of key in bytes
    u8     KeyMaterial[16];// variable length depending on above field
} NDIS_802_11_WEP, *PNDIS_802_11_WEP;

typedef struct _NDIS_802_11_AUTHENTICATION_REQUEST
{
    u32 Length;            // Length of structure
    unsigned char  Bssid[ETH_ALEN];
    u32 Flags;
} NDIS_802_11_AUTHENTICATION_REQUEST, *PNDIS_802_11_AUTHENTICATION_REQUEST;

enum NDIS_802_11_STATUS_TYPE {
	Ndis802_11StatusType_Authentication,
	Ndis802_11StatusType_MediaStreamMode,
	Ndis802_11StatusType_PMKID_CandidateList,
	Ndis802_11StatusTypeMax    // not a real type, defined as an upper bound
};

typedef struct _NDIS_802_11_STATUS_INDICATION {
	enum NDIS_802_11_STATUS_TYPE StatusType;
} NDIS_802_11_STATUS_INDICATION, *PNDIS_802_11_STATUS_INDICATION;

// mask for authentication/integrity fields
#define NDIS_802_11_AUTH_REQUEST_AUTH_FIELDS        0x0f
#define NDIS_802_11_AUTH_REQUEST_REAUTH			0x01
#define NDIS_802_11_AUTH_REQUEST_KEYUPDATE		0x02
#define NDIS_802_11_AUTH_REQUEST_PAIRWISE_ERROR		0x06
#define NDIS_802_11_AUTH_REQUEST_GROUP_ERROR		0x0E

// MIC check time, 60 seconds.
#define MIC_CHECK_TIME	60000000

typedef struct _NDIS_802_11_AUTHENTICATION_EVENT
{
    NDIS_802_11_STATUS_INDICATION       Status;
    NDIS_802_11_AUTHENTICATION_REQUEST  Request[1];
} NDIS_802_11_AUTHENTICATION_EVENT, *PNDIS_802_11_AUTHENTICATION_EVENT;

typedef struct _NDIS_802_11_TEST
{
    u32 Length;
    u32 Type;
    union
    {
        NDIS_802_11_AUTHENTICATION_EVENT AuthenticationEvent;
        long RssiTrigger;
    }tt;
} NDIS_802_11_TEST, *PNDIS_802_11_TEST;

#ifndef Ndis802_11APMode
#define Ndis802_11APMode (Ndis802_11InfrastructureMax+1)
#endif

typedef struct _WLAN_PHY_INFO
{
	u8	SignalStrength;//(in percentage)
	u8	SignalQuality;//(in percentage)
	u8	Optimum_antenna;  //for Antenna diversity
	u8	Reserved_0;
}WLAN_PHY_INFO,*PWLAN_PHY_INFO;

typedef struct _WLAN_BSSID_EX
{
	u32  Length;
	unsigned char MacAddress[ETH_ALEN];
	u8  Reserved[2];//[0]: IS beacon frame
	struct ndis_802_11_ssid  Ssid;
	u32  Privacy;
	long  Rssi;//(in dBM,raw data ,get from PHY)
	enum NDIS_802_11_NETWORK_TYPE  NetworkTypeInUse;
	NDIS_802_11_CONFIGURATION  Configuration;
	enum NDIS_802_11_NETWORK_INFRASTRUCTURE  InfrastructureMode;
	NDIS_802_11_RATES_EX  SupportedRates;
	WLAN_PHY_INFO	PhyInfo;
	u32  IELength;
	u8  IEs[MAX_IE_SZ];	//(timestamp, beacon interval, and capability information)
} __attribute__((packed)) WLAN_BSSID_EX, *PWLAN_BSSID_EX;

__inline  static uint get_WLAN_BSSID_EX_sz(WLAN_BSSID_EX *bss)
{
	return (sizeof(WLAN_BSSID_EX) - MAX_IE_SZ + bss->IELength);
}

struct	wlan_network {
	struct list_head list;
	int	network_type;	//refer to ieee80211.h for WIRELESS_11A/B/G
	int	fixed;			// set to fixed when not to be removed as site-surveying
	unsigned long	last_scanned; //timestamp for the network
	int	aid;			//will only be valid when a BSS is joinned.
	int	join_res;
	WLAN_BSSID_EX	network; //must be the last item
};

enum VRTL_CARRIER_SENSE
{
    DISABLE_VCS,
    ENABLE_VCS,
    AUTO_VCS
};

enum VCS_TYPE
{
    NONE_VCS,
    RTS_CTS,
    CTS_TO_SELF
};




#define PWR_CAM 0
#define PWR_MINPS 1
#define PWR_MAXPS 2
#define PWR_UAPSD 3
#define PWR_VOIP 4


enum UAPSD_MAX_SP
{
	NO_LIMIT,
       TWO_MSDU,
       FOUR_MSDU,
       SIX_MSDU
};


//john
#define NUM_PRE_AUTH_KEY 16
#define NUM_PMKID_CACHE NUM_PRE_AUTH_KEY

/*
*	WPA2
*/

typedef struct _PMKID_CANDIDATE {
    unsigned char  BSSID[ETH_ALEN];
    u32 Flags;
} PMKID_CANDIDATE, *PPMKID_CANDIDATE;

typedef struct _NDIS_802_11_PMKID_CANDIDATE_LIST
{
    u32 Version;       // Version of the structure
    u32 NumCandidates; // No. of pmkid candidates
    PMKID_CANDIDATE CandidateList[1];
} NDIS_802_11_PMKID_CANDIDATE_LIST, *PNDIS_802_11_PMKID_CANDIDATE_LIST;


typedef struct _NDIS_802_11_AUTHENTICATION_ENCRYPTION
{
	enum NDIS_802_11_AUTHENTICATION_MODE AuthModeSupported;
	enum NDIS_802_11_ENCRYPTION_STATUS EncryptStatusSupported;

} NDIS_802_11_AUTHENTICATION_ENCRYPTION, *PNDIS_802_11_AUTHENTICATION_ENCRYPTION;

typedef struct _NDIS_802_11_CAPABILITY
{
	u32  Length;
	u32  Version;
	u32  NoOfPMKIDs;
	u32  NoOfAuthEncryptPairsSupported;
	NDIS_802_11_AUTHENTICATION_ENCRYPTION AuthenticationEncryptionSupported[1];

} NDIS_802_11_CAPABILITY, *PNDIS_802_11_CAPABILITY;


#endif //#ifndef WLAN_BSSDEF_H_
