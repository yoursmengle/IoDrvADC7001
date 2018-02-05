/**
 * <interfacename>CmpX509Cert</interfacename>
 * <description> 
 *	<p>This interface provides functionality to handle and verify X.509 Certificates</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */
SET_INTERFACE_NAME(`CmpX509Cert')
REF_ITF(`CmpCryptoItf.m4')
REF_ITF(`SysSocketItf.m4')

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Enables or disables CRL checking while verifying a certificat. (DEFAULT: Disabled)</description>
 */
#define X509CERTKEY_INT_VERIFY_USE_CRL					"VerifyUseCRL"
#ifndef X509CERTVALUE_INT_VERIFY_USE_CRL
	#define X509CERTVALUE_INT_VERIFY_USE_CRL			0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Configures the minim allowed key size (in bits) for newly created asymmetric key. Refer to NIST or BSI suggestions.</description>
 */
#define X509CERTKEY_INT_MIN_ASYMMETRIC_KEY_SIZE			"MinAsymmetricKeySize"
#ifndef X509CERTVALUE_INT_MIN_ASYMMETRIC_KEY_SIZE
	#define X509CERTVALUE_INT_MIN_ASYMMETRIC_KEY_SIZE	2048
#endif

/**
 * <category>Static defines</category>
 * <description>This define is used for the PlcShell command "cert-genselfsigned" to specify the number of days until the certificate will expire (if no argument is specified)</description>
 */
#ifndef X509CERT_STANDARD_DAYS_FOR_CERT
	#define X509CERT_STANDARD_DAYS_FOR_CERT				365
#endif

/**
 * <category>Static defines</category>
 * <description>This define is used for the number of days until the certificate will expire for selfsigned certificates</description>
 */
#ifndef X509CERT_STANDARD_DAYS_FOR_SELFIGNEDCERT
	#define X509CERT_STANDARD_DAYS_FOR_SELFIGNEDCERT	1
#endif

#define X509CERT_MILLISECONDS_PER_DAY					(24 * 60 * 60 * 1000)

/**
 * <category>SecuritySettings</category>
 * <description>Security settings of the X.509 certificate management to create diffie hellman parameters. Can be selected in CmpSecurityManager.
 *	NOTE:
 *		Security modes must be ordered in an descending sorting, that the setting with the highest security level is found at the beginning of the list!
 * </description>
 */
#define RTS_SECURITY_SETTINGS_CMPX509CERT		{ \
													{1, CMPSECMAN_FLAGS_DEFAULT, "DHPARAMS_ONSTARTUP", "Create Diffie Hellman parameters on startup"},\
													{0, 0, "DHPARAMS_ONREQUEST", "Create Diffie Hellman parameters only on request"}\
												}

#define RTS_CMPX509CERT_SECURITY_ID_DHPARAM		RTS_SECURITY_ID_SELFSIGNEDCERT

/**
 * <category>Static defines</category>
 * <description>This define is used to specify the default length of the diffie hellman parameters</description>
 */
#ifndef RTS_X509_DIFFIEHELLMAN_DEFAULT_LEN
	#define RTS_X509_DIFFIEHELLMAN_DEFAULT_LEN		2048
#endif

/**
 * <category>Online services</category>
 */ 
#define SRV_X509_IMPORT_CERT        0x01
#define SRV_X509_EXPORT_CERT        0x02
#define SRV_X509_DELETE_CERT        0x03
#define SRV_X509_MOVE_CERT          0x04
#define SRV_X509_LIST_CERTS         0x05
#define SRV_X509_LIST_USECASES      0x06
#define SRV_X509_CREATE_SELFSIGNED  0x07
#define SRV_X509_CREATE_REQUEST     0x08
#define SRV_X509_GET_STATUS         0x09

/**
 * <category>Online service tags</category>
 */
#define TAG_X509_TRUSTLEVEL		    0x01
#define TAG_X509_BACKEND            0x02
#define TAG_X509_USECASE            0x03
#define TAG_X509_THUMBPRINT         0x04
#define TAG_X509_CERT               0x05
#define TAG_X509_CSR                0x06
#define TAG_X509_DEST_TRUSTLEVEL    0x07
#define TAG_X509_DEST_BACKEND       0x08
#define TAG_X509_KEY_LENGTH         0x09
#define TAG_X509_USECASE_NAME       0x0A
#define TAG_X509_USECASE_DESC       0x0B
#define TAG_X509_SUBJECT_ID         0x0C
#define TAG_X509_SUBJECT_VALUE      0x0D
#define TAG_X509_ALT_NAME_EMAIL     0x0E
#define TAG_X509_ALT_NAME_DNSNAME   0x0F
#define TAG_X509_ALT_NAME_URI       0x10
#define TAG_X509_ALT_NAME_IPADDRESS 0x12
#define TAG_X509_ALT_NAME_REGISTEREDID 0x13
#define TAG_X509_KEYUSAGE           0x14
#define TAG_X509_EXT_KEYUSAGE       0x15
#define TAG_X509_USECASE_COMPONENT  0x16
#define TAG_X509_DELETE_PKEY        0x17
#define TAG_X509_DAYS_VALID         0x18
#define TAG_X509_GEN_SELF_SIGNED    0x19
#define TAG_X509_GEN_CSR            0x1A
#define TAG_X509_STATUS_HANDLE      0x1B
#define TAG_X509_OPERATION          0x1C
/* Leave tags 0x22 - 0x24 empty. Use for user management. */
#define TAG_X509_RESULT             TAG_ERROR

/* Complex tags */
#define TAG_X509_USECASE_DETAILS    0x81
/* Leave TAG 0x082 empty. Is used for user management. */
 
 
/**
 * <category>Online services</category>
 * <Description>
 *	Import certificate service. This service imports the given certificate into the corresponding store of the PLC.
 *  Since this service changes the security configuration of the PLC administrator rights are needed to execute this service.
 * </Description>
 * <service name="SRV_X509_IMPORT_CERT">
 *	<Request>
 *		<tag name="TAG_X509_TRUSTLEVEL" required="required">[RTS_UI32]: Trust level where to import the certificate. See the RTSCERTTRUSTLEVEL_* defines for details.</tag>
 *		<tag name="TAG_X509_BACKEND" required="optional">[Type not yet defined]: Identifier of the backend where to store the certificate. Not used by now.</tag>
 *		<tag name="TAG_X509_CERT" required="required">Certificate in ANS.1 encoding to import.</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_X509_RESULT" required="required">[RTS_UI16]: Result code of online operation</tag>
 *	</Response>
 * </service>
 */
 
/**
 * <category>Online services</category>
 * <Description>
 *	Export certificate service. This service exports a selected certificate from the PLC for use in other applications.
 * </Description>
 * <service name="SRV_X509_EXPORT_CERT">
 *	<Request>
 *		<tag name="TAG_X509_TRUSTLEVEL" required="required">[RTS_UI32]: Trust level of the certificate to export. See the RTSCERTTRUSTLEVEL_* defines for details.</tag>
 *		<tag name="TAG_X509_BACKEND" required="optional">[Type not yet defined]: Identifier of the backend of the certificate. Not used by now.</tag>
 *		<tag name="TAG_X509_THUMBPRINT" required="required">Thumbprint of certificate calculated by the runtime system.</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_X509_RESULT" required="required">[RTS_UI16]: Result code of online operation</tag>
 *		<tag name="TAG_X509_CERT" required="optional">Exported certificate in ASN.1 encoding if the certificate was available.</tag>
 *	</Response>
 * </service>
 */
 
/**
 * <category>Online services</category>
 * <Description>
 *	Delete certificate service. This service deletes a certificate from the PLC.
 *  Since this service changes the security configuration of the PLC administrator rights are needed to execute this service.
 * </Description>
 * <service name="SRV_X509_DELETE_CERT">
 *	<Request>
 *		<tag name="TAG_X509_TRUSTLEVEL" required="required">[RTS_UI32]: Trust level of the certificate to delete. See the RTSCERTTRUSTLEVEL_* defines for details.</tag>
 *		<tag name="TAG_X509_BACKEND" required="optional">[Type not yet defined]: Identifier of the backend of the certificate. Not used by now.</tag>
 *		<tag name="TAG_X509_THUMBPRINT" required="required">Thumbprint of certificate calculated by the runtime system.</tag>
 *		<tag name="TAG_X509_DELETE_PKEY" required="optional">[RTS_UI32]: Flag if the private key should be deleted too. This is only used for trust level 'OWN'.</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_X509_RESULT" required="required">[RTS_UI16]: Result code of online operation</tag>
 *	</Response>
 * </service>
 */
 
/**
 * <category>Online services</category>
 * <Description>
 *	Move certificate service. This service moves certificates from one place to another.
 *  Since this service changes the security configuration of the PLC administrator rights are needed to execute this service.
 * </Description>
 * <service name="SRV_X509_MOVE_CERT">
 *	<Request>
 *		<tag name="TAG_X509_TRUSTLEVEL" required="required">[RTS_UI32]: Trust level of the certificate to move. See the RTSCERTTRUSTLEVEL_* defines for details.</tag>
 *		<tag name="TAG_X509_BACKEND" required="optional">[Type not yet defined]: Identifier of the backend of the certificate. Not used by now.</tag>
 *		<tag name="TAG_X509_THUMBPRINT" required="required">Thumbprint of certificate calculated by the runtime system.</tag>
 *		<tag name="TAG_X509_DEST_TRUSTLEVEL" required="required">[RTS_UI32]: Trust level where to move the certificate to. See the RTSCERTTRUSTLEVEL_* defines for details.</tag>
 *		<tag name="TAG_X509_DEST_BACKEND" required="optional">[Type not yet defined]:Backend where to move the certificate to. Not used by now.</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_X509_RESULT" required="required">[RTS_UI16]: Result code of online operation</tag>
 *	</Response>
 * </service>
 */
 
/**
 * <category>Online services</category>
 * <Description>
 *	List certificate service. This service lists all certificates from one place. Maybe not all certificates can be transmitted in one single online service.
 *  In this case the service return ERR_ENTRIES_REMAINING to indicate that more certificates are available. To get the next junk of certificates put the thumbprint of the
 *  last certificate of the last service as a starting point for the next certificates. The thumbprint tag in the response contains the thumbprint of the certificate 
 *  contained in the previous tag. These tags must always occur as a pair.
 * </Description>
 * <service name="SRV_X509_LIST_CERTS">
 *	<Request>
 *		<tag name="TAG_X509_TRUSTLEVEL" required="required">[RTS_UI32]: Trust level of the certificate to list. See the RTSCERTTRUSTLEVEL_* defines for details.</tag>
 *		<tag name="TAG_X509_BACKEND" required="optional">[Type not yet defined]: Identifier of the backend of the certificate. Not used by now.</tag>
 *		<tag name="TAG_X509_THUMBPRINT" required="optional">Thumbprint of certificate calculated by the runtime system of the last received certificate.</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_X509_RESULT" required="required">[RTS_UI16]: Result code of online operation</tag>
 *		<tag name="TAG_X509_CERT" required="required">Certificate in ASN.1 format. This tag may occur multiple times.</tag>
 *		<tag name="TAG_X509_THUMBPRINT" required="required">Thumbprint of certificate calculated by the runtime system.</tag>
 *	</Response>
 * </service>
 */
 
/**
 * <category>Online services</category>
 * <Description>
 *	List certificate use service. This service return a list of all registered servers or clients that need their own certificates. This can be used to generate the needed
 *  self signed certificates or to generate the corresponding certificate requests. If a certificate is available for a dedicated use case the thumbprint of this certificate
 *  will be put the the service response. This allows to display the corresponding certificate.
 *  If the complete list of use cases can't be transmitted in one single service it will be split up. In this case the service return ERR_ENTRIES_REMAINING to indicate that more use 
 *  cases are available. The get the next junk of use cases is identified by the last usecases index.
 * </Description>
 * <service name="SRV_X509_LIST_USECASES">
 *	<Request>
 *      <tag name="TAG_X509_USECASE" required="optional">[RTS_UI32]: If the last service returned ERR_ENTRIES_REMAINING this is the ID of the last received use case.</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_X509_RESULT" required="required">[RTS_UI16]: Result code of online operation</tag>
 *      <tag name="TAG_X509_USECASE_DETAILS" required="required">
 *		    <tag name="TAG_X509_USECASE" required="required">[RTS_UI32]: ID of the use case.</tag>
 *          <tag name="TAG_X509_USECASE_COMPONENT" required="required">[String]: Component which registered the use case.</tag>
 *          <tag name="TAG_X509_USECASE_NAME" required="optional">[String]: Name of the usecase. Provided by the component.</tag>
 *          <tag name="TAG_X509_USECASE_DESC" required="optional">[String]: Description of the use case. Provided by the component.</tag>
 *          <tag name="TAG_X509_SUBJECT_ID" required="optional">[String]: OID of the current subject field. Always exists with the following TAG_X509_SUBJECT_VALUE field. Sequenz is likley to be repeated</tag>
 *          <tag name="TAG_X509_SUBJECT_VALUE" required="optional">[String]: Value of the current subject field.</tag>
 *          <tag name="TAG_X509_ALT_NAME_EMAIL" required="optional">[String]: Alternative name containing an email address.</tag>
 *          <tag name="TAG_X509_ALT_NAME_DNSNAME" required="optional">[String]: Alternative name containing the DNS name.</tag>
 *          <tag name="TAG_X509_ALT_NAME_URI" required="optional">[String]: Alternative name containing the URI</tag>
 *          <tag name="TAG_X509_ALT_NAME_IPADDRESS" required="optional">[String]: Alternative name containing the IP-Address.</tag>
 *          <tag name="TAG_X509_ALT_NAME_REGISTEREDID" required="optional">[String]: Alternative name containing an OID in textual representation.</tag>
 *          <tag name="TAG_X509_KEYUSAGE" required="optional">[RTS_UI32]: Key usage of the certificate. See: RTS_KEY_USAGE_DIGITAL_* macros.</tag>
 *          <tag name="TAG_X509_EXT_KEYUSAGE" required="optional">[String]: Extended key usage identified by its textual representation. Can occur multiple times.</tag>
 *          <tag name="TAG_X509_THUMBPRINT" required="optional">Thumbprint of the certificate available for this use case. Left out if no certificate is available.</tag>
 *          <tag name="TAG_X509_GEN_SELF_SIGNED" required="optional">[Empty tag]: A self signed certificate is beeing generated at the moment.</tag>
 *          <tag name="TAG_X509_GEN_CSR" required="optional">[Empty tag]: A certificate request is beeing generated at the moment.</tag>
 *      </tag>
 *	</Response>
 * </service>
 */
 
/**
 * <category>Online services</category>
 * <Description>
 *	Generate self signed certificate service. This service is used to generate a self signed certificate for a registered use case. 
 *  This service will also generate the private key used by the new certificate.
 *  Since this service changes the security configuration of the PLC administrator rights are needed to execute this service.
 * Repeat this service 
 * </Description>
 * <service name="SRV_X509_CREATE_SELFSIGNED">
 *	<Request>
 *		<tag name="TAG_X509_USECASE" required="required">[RTS_UI32]: Usecase ID which the certificate is generated for.</tag>
 *		<tag name="TAG_X509_BACKEND" required="optional">[Type not yet defined]: Backend where to store the certificate. Not used by now.</tag>
 *      <tag name="TAG_X509_KEY_LENGTH" required="optional">[RTS_UI32]: The length of the asymmetric key pair in bits. If left out the default (see MinAsymmetricKeySize) will be used.</tag>
 *      <tag name="TAG_X509_DAYS_VALID" required="optional">[RTS_UI32]: Number of days the self signed certificate is valid.</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_X509_RESULT" required="required">[RTS_UI16]: Result code of online operation</tag>
 *		<tag name="TAG_X509_STATUS_HANDLE" required="required">[RTS_UI16]: Result code of online operation</tag>
 *	</Response>
 * </service>
 */
 
/**
 * <category>Online services</category>
 * <Description>
 *	Generate certificate signing request service. This service is used to generate a certificate signing request (CSR) for a registered use case.
 *  The private key is stored on the PLC. If the certificate has been generated by a CA this certificate has to be imported to the own store.
 * </Description>
 * <service name="SRV_X509_CREATE_REQUEST">
 *	<Request>
 *		<tag name="TAG_X509_USECASE" required="required">[RTS_UI32]: Usecase ID which the CSR is generated for.</tag>
 *		<tag name="TAG_X509_BACKEND" required="optional">[Type not yet defined]: Backend where to store the private key. Not used by now.</tag>
 *      <tag name="TAG_X509_KEY_LENGTH" required="optional">[RTS_UI32]: The length of the asymmetric key pair in bits. If left out the default (see MinAsymmetricKeySize) will be used.</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_X509_RESULT" required="required">[RTS_UI16]: Result code of online operation</tag>
 *		<tag name="TAG_X509_CSR" required="optional">The generated CSR in ASN.1 encoding.</tag>
 *	</Response>
 * </service>
 */
 
/**
 * <category>Online services</category>
 * <Description>
 *	Get the status of long lasting operation. Actually this is used for generating self signed certificates.
 * </Description>
 * <service name="SRV_X509_GET_STATUS">
 *	<Request>
 *      <tag name="TAG_X509_OPERATION" required="required">[RTS_UI32]: Identifier of the operation. Use the service wating for as ID.</tag>
 *		<tag name="TAG_X509_STATUS_HANDLE" required="required">[RTS_UI32]: Usecase ID which the CSR is generated for.</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_X509_RESULT" required="required">[RTS_UI16]: Result code of online operation. 
 *              ERR_OK: Operation finished. 
 *              ERR_INVALID_HANDLE: TAG_X509_STATUS_HANDLE was invalid. 
 *              ERR_PENDING: Operations still running. 
 *              ERR_FAILED: Operations failed.
 *      </tag>
 *	</Response>
 * </service>
 */
 
/**
 * <category>Static defines</category>
 * <description>Predefined objects in the runtime</description>
 */
#define USERDB_OBJECT_X509				        "Device.X509"
#define USERDB_OBJECT_X509_IMPORT_CERT          "Device.X509.ImportCertificate"
#define USERDB_OBJECT_X509_EXPORT_CERT          "Device.X509.ExportCertificate"
#define USERDB_OBJECT_X509_DELETE_CERT          "Device.X509.DeleteCertificate"
#define USERDB_OBJECT_X509_MOVE_CERT            "Device.X509.MoveCertificate"
#define USERDB_OBJECT_X509_LIST_CERTS           "Device.X509.ListCertificates"
#define USERDB_OBJECT_X509_LIST_USE_CASES       "Device.X509.ListUseCases"
#define USERDB_OBJECT_X509_CREATE_SELFSIGNED    "Device.X509.CreateSelfSignedCertificate"
#define USERDB_OBJECT_X509_CREATE_CSR           "Device.X509.CreateCertificateSigningRequest"
#define USERDB_OBJECT_X509_GET_STAUTS           "Device.X509.GetStatus"
#define USERDB_OBJECT_X509_UNKNOWN              "Device.X509.Unknown"







/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Enum: RtsCertEncoding</description>
 */
#define RTSCERTENCODING_ASN1    RTS_IEC_INT_C(0x0)	
#define RTSCERTENCODING_BASE64    RTS_IEC_INT_C(0x1)	
/* Typed enum definition */
#define RTSCERTENCODING    RTS_IEC_INT

/**
 * The truste level has two main meanings:
 * 1. In opend certificates it indicates if the certificate is trusted or not
 * 2. If adding or searching certificates in the store it indicates where to add / search the certificate.
 */
#define RTSCERTTRUSTLEVEL_UNTRUSTED    RTS_IEC_INT_C(0x1)	
#define RTSCERTTRUSTLEVEL_TRUSTED    RTS_IEC_INT_C(0x2)	
#define RTSCERTTRUSTLEVEL_OWN    RTS_IEC_INT_C(0x3)	
#define RTSCERTTRUSTLEVEL_QUARANTINE    RTS_IEC_INT_C(0x4)	
#define RTSCERTTRUSTLEVEL_UNKNOWN    RTS_IEC_INT_C(0x5)	
/* Typed enum definition */
#define RTSCERTTRUSTLEVEL    RTS_IEC_INT

/**
 * <description>Enum: RtsX509AltNameType</description>
 */
#define RTSX509ALTNAMETYPE_OTHERNAME    RTS_IEC_INT_C(0x0)	/* Not supported */
#define RTSX509ALTNAMETYPE_EMAIL    RTS_IEC_INT_C(0x1)	/* Supported */
#define RTSX509ALTNAMETYPE_DNSNAME    RTS_IEC_INT_C(0x2)	/* Supported */
#define RTSX509ALTNAMETYPE_X400ADDRESS    RTS_IEC_INT_C(0x3)	/* Not supported */
#define RTSX509ALTNAMETYPE_DIRECTORYNAME    RTS_IEC_INT_C(0x4)	/* Not supported */
#define RTSX509ALTNAMETYPE_EDIPARTYNAME    RTS_IEC_INT_C(0x5)	/* Not supported */
#define RTSX509ALTNAMETYPE_URI    RTS_IEC_INT_C(0x6)	/* Supported */
#define RTSX509ALTNAMETYPE_IPADDRESS    RTS_IEC_INT_C(0x7)	/* Supported */
#define RTSX509ALTNAMETYPE_REGISTERDID    RTS_IEC_INT_C(0x8)	/* Supported */
/* Typed enum definition */
#define RTSX509ALTNAMETYPE    RTS_IEC_INT

/**
 * <description>Enum: RtsX509CertFilterType</description>
 */
#define RTSX509CERTFILTERTYPE_TRUST_LEVEL    RTS_IEC_INT_C(0x0)	
#define RTSX509CERTFILTERTYPE_SUBJECT    RTS_IEC_INT_C(0x1)	
#define RTSX509CERTFILTERTYPE_SUBJECT_MATCHALL    RTS_IEC_INT_C(0x2)	
#define RTSX509CERTFILTERTYPE_CERT_DATEVALID    RTS_IEC_INT_C(0x3)	
#define RTSX509CERTFILTERTYPE_CERT_KEYUSAGE    RTS_IEC_INT_C(0x4)	
#define RTSX509CERTFILTERTYPE_CERT_EXKEYUSAGE    RTS_IEC_INT_C(0x5)	
#define RTSX509CERTFILTERTYPE_CERT_THUMBPRINT    RTS_IEC_INT_C(0x6)	
/* Typed enum definition */
#define RTSX509CERTFILTERTYPE    RTS_IEC_INT

/**
 * <description>RtsOIDStore</description>
 */
typedef union
{
	RTS_IEC_BYTE aOID[16];		
	RTS_IEC_BYTE *pOID;		
} RtsOIDStore;

/**
 * <description>RtsOID</description>
 */
typedef struct tagRtsOID
{
	RTS_IEC_UDINT length;		/* Lenght of the OID in memory */
	RtsOIDStore data;		/* Storage of the OID */
	RTS_IEC_UDINT flags;		/* Internal */
} RtsOID;

/**
 * <description>RtsX509AltNameStore</description>
 */
typedef union
{
	RTS_IEC_STRING *pEmail;		
	RTS_IEC_STRING *pDnsName;		
	RTS_IEC_STRING *pUri;		
	INADDR ipAddress;		
	RtsOID registerdID;		
} RtsX509AltNameStore;

/**
 * Represents an alternative name of a certificate. The alternative 
 * name can be selected out of different meanings. E.g. E-Mail 
 * address, IP-Address, URI or a DNS name. Use the corresponding
 * fiels of the union to geht the values. The meaning is declared
 * in the valueType field.
 */
typedef struct tagRtsX509AltName
{
	RTS_IEC_INT valueType;		/* Type of the alternative name */
	RtsX509AltNameStore value;		
} RtsX509AltName;

/**
 * Represents an entry of the X509 Names used in the
 * subject or issuer fields in the certificate.
 * This sturucter contains the OID to identify the field
 * and the corresponding string as value. Use the 
 * RtsOIDGetName function to get the string
 * representations of the field.
 */
typedef struct tagRtsX509NameEntry
{
	RtsOID id;		/* ID of the entry */
	RTS_IEC_STRING *value;		/* String value of the entry */
} RtsX509NameEntry;

/**
 * <description>RtsX509CertName</description>
 */
typedef struct tagRtsX509CertName
{
	RTS_IEC_UDINT numOfEntries;		/* Number of entries in the X509 Name */
	RtsX509NameEntry *entries;		/* Pointer to a list of name entries. */
} RtsX509CertName;

/**
 * <description>RtsX509ExKeyUsage</description>
 */
typedef struct tagRtsX509ExKeyUsage
{
	RTS_IEC_UDINT numOfExKeyUsages;		/* Number of extended key usages */
	RtsOID *pExKeyUsages;		/* Pointer to a list of extended key usages. */
} RtsX509ExKeyUsage;

/**
 * <description>RtsX509CertFilterContent</description>
 */
typedef union
{
	RTS_IEC_INT trustLevel;		
	RtsX509CertName *subject;		
	RTS_IEC_UDINT keyUsage;		
	RtsX509ExKeyUsage *exKeyUsage;		
	RtsByteString *thumpbrint;		
} RtsX509CertFilterContent;

/**
 * <description>RtsX509CertFilter</description>
 */
typedef struct tagRtsX509CertFilter
{
	RTS_IEC_INT filterType;		
	RtsX509CertFilterContent filterContent;		
} RtsX509CertFilter;

/**
 * This structuer contains common fiels of an certificate. Most values are stored in
 * textual form if available. The alternative key usages and the signature algorithm
 * are stored as RtsOID. Use the RtsOIDGetName function to get human readable names
 * of this fields. The notBefor and notAfter fiels are in UTC format and high resolution
 * timestam
 */
typedef struct tagRtsX509CertInfo
{
	RTS_IEC_UDINT ui32StructSize;		/* Structure size. Used if the structuer is extended in the futuer. */
	RtsX509CertName issuer;		/* Common fields of the issuer */
	RtsX509CertName subject;		/* Common fields of the subject */
	RTS_IEC_UDINT numOfAltNames;		/* Number of stored alternative names */
	RtsX509AltName *pAltNames;		/* Pointer to a list of alternative names. */
	RTS_IEC_ULINT notBefore;		/* High resolution UTC timestamp */
	RTS_IEC_ULINT notAfter;		/* High resolution UTC timestamp */
	RTS_IEC_UDINT keyUsage;		/* Key usage field. Use the constans of X509CertKeyUsage to determin the key usages. Every value is represented by a specific bit of the value. */
	RTS_IEC_UDINT numOfExKeyUsages;		/* Number of extended key usages */
	RtsOID *pExKeyUsages;		/* Pointer to a list of extended key usages. */
	RtsOID signatureAlgorithm;		/* OID of the signature algorithm. Use the RtsOIDGetName to get a human readable string. */
} RtsX509CertInfo;

/**
 * Clear an OID
 * :return: Result of the operation
 */
typedef struct tagrtsoidclear_struct
{
	RtsOID *oid;						/* VAR_INPUT */	
	RTS_IEC_RESULT RtsOIDClear;			/* VAR_OUTPUT */	
} rtsoidclear_struct;

DEF_API(`void',`CDECL',`rtsoidclear',`(rtsoidclear_struct *p)',1,0xB53A1CAF,0x03050B00)

/**
 * Create an RtsOID based on a given ID.
 * :return: Result of the operation.
 */
typedef struct tagrtsoidcreate_struct
{
	RTS_IEC_STRING *id;					/* VAR_INPUT */	/* OID as string in dottet format. E.g. (1.2.3.4.5.6.7.8.9.0) */
	RtsOID *oid;						/* VAR_INPUT */	/* Pointer to an OID to fill up. */
	RTS_IEC_RESULT RtsOIDCreate;		/* VAR_OUTPUT */	
} rtsoidcreate_struct;

DEF_API(`void',`CDECL',`rtsoidcreate',`(rtsoidcreate_struct *p)',1,0xE11A70BD,0x03050B00)

/**
 * Get the ID of an OID in dottet notation.
 * :return: Result of the operation
 */
typedef struct tagrtsoidgetid_struct
{
	RtsOID *oid;						/* VAR_INPUT */	/* OID to print. */
	RtsByteString *pBuffer;				/* VAR_INPUT */	/* Buffer where to store the ID. */
	RTS_IEC_RESULT RtsOIDGetID;			/* VAR_OUTPUT */	
} rtsoidgetid_struct;

DEF_API(`void',`CDECL',`rtsoidgetid',`(rtsoidgetid_struct *p)',1,0xB69D55FF,0x03050B00)

/**
 * Get the given name of an OID. If the OID is unknown 
 * to the system the dottet notation will be returned.
 * :return: Result of the operation.
 */
typedef struct tagrtsoidgetname_struct
{
	RtsOID *oid;						/* VAR_INPUT */	
	RtsByteString *pBuffer;				/* VAR_INPUT */	
	RTS_IEC_RESULT RtsOIDGetName;		/* VAR_OUTPUT */	
} rtsoidgetname_struct;

DEF_API(`void',`CDECL',`rtsoidgetname',`(rtsoidgetname_struct *p)',1,0xBEA6E204,0x03050B00)

/**
 * Close the certificate.
 * :return: Result of the operation.
 */
typedef struct tagx509certclose_struct
{
	RTS_IEC_HANDLE hCert;				/* VAR_INPUT */	/* Handle of to certificate. */
	RTS_IEC_RESULT X509CertClose;		/* VAR_OUTPUT */	
} x509certclose_struct;

DEF_API(`void',`CDECL',`x509certclose',`(x509certclose_struct *p)',1,0x150A5E6B,0x03050B00)

/**
 * <description>x509certcmsdecrypt</description>
 */
typedef struct tagx509certcmsdecrypt_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hRecipientCert;		/* VAR_INPUT */	
	RtsByteString *pCms;				/* VAR_INPUT */	
	RTS_IEC_INT encoding;				/* VAR_INPUT, Enum: RTSCERTENCODING */
	RtsByteString *pOutData;			/* VAR_INPUT */	
	RTS_IEC_RESULT X509CertCmsDecrypt;	/* VAR_OUTPUT */	
} x509certcmsdecrypt_struct;

DEF_API(`void',`CDECL',`x509certcmsdecrypt',`(x509certcmsdecrypt_struct *p)',1,0xCCAD85D1,0x03050B00)

/**
 * <description>x509certcmsverify</description>
 */
typedef struct tagx509certcmsverify_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RtsByteString *pCms;				/* VAR_INPUT */	
	RTS_IEC_INT encoding;				/* VAR_INPUT, Enum: RTSCERTENCODING */
	RtsByteString *pInData;				/* VAR_INPUT */	
	RtsByteString *pOutData;			/* VAR_INPUT */	
	RTS_IEC_RESULT X509CertCmsVerify;	/* VAR_OUTPUT */	
} x509certcmsverify_struct;

DEF_API(`void',`CDECL',`x509certcmsverify',`(x509certcmsverify_struct *p)',1,0x73653424,0x03050B00)

/**
 * <description>x509certcreatecsr</description>
 */
typedef struct tagx509certcreatecsr_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hBackend;			/* VAR_INPUT */	
	RtsX509CertInfo *pCertInfo;			/* VAR_INPUT */	
	RTS_IEC_UDINT ui32KeySize;			/* VAR_INPUT */	
	RTS_IEC_INT encoding;				/* VAR_INPUT, Enum: RTSCERTENCODING */
	RtsByteString *pCSR;				/* VAR_INPUT */	
	RTS_IEC_RESULT X509CertCreateCSR;	/* VAR_OUTPUT */	
} x509certcreatecsr_struct;

DEF_API(`void',`CDECL',`x509certcreatecsr',`(x509certcreatecsr_struct *p)',1,0xF64C1D04,0x03050B00)

/**
 * <description>x509certcreateselfsigned</description>
 */
typedef struct tagx509certcreateselfsigned_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hBackend;			/* VAR_INPUT */	
	RtsX509CertInfo *pCertInfo;			/* VAR_INPUT */	
	RTS_IEC_UDINT ui32KeySize;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE X509CertCreateSelfSigned;	/* VAR_OUTPUT */	
} x509certcreateselfsigned_struct;

DEF_API(`void',`CDECL',`x509certcreateselfsigned',`(x509certcreateselfsigned_struct *p)',1,0x6765E8BD,0x03050B00)

/**
 * Get the certificate in a binary encoded format. Use the encoding parameter
 * to set the needed format.
 * :return: Result of the operation.
 */
typedef struct tagx509certgetbinary_struct
{
	RTS_IEC_HANDLE hCert;				/* VAR_INPUT */	/* Handle of the certificate of intrest. */
	RTS_IEC_INT encoding;				/* VAR_INPUT, Enum: RTSCERTENCODING */
	RtsByteString *pCert;				/* VAR_INPUT */	/* Buffer where to store the certificate. If the bytestring contains a NULL memory pointer the function will write the needed bufferlength to the pCert->ui32Length member. */
	RTS_IEC_RESULT X509CertGetBinary;	/* VAR_OUTPUT */	
} x509certgetbinary_struct;

DEF_API(`void',`CDECL',`x509certgetbinary',`(x509certgetbinary_struct *p)',1,0x6F7D6C42,0x03050B00)

/**
 * Get some common content from the certificate.
 * :return: Result of the operation.
 */
typedef struct tagx509certgetcontent_struct
{
	RTS_IEC_HANDLE hCert;				/* VAR_INPUT */	/* Handle of the certificate of intrest. */
	RtsX509CertInfo *pCertContent;		/* VAR_INPUT */	/* Pointer where to store the information. */
	RTS_IEC_RESULT X509CertGetContent;	/* VAR_OUTPUT */	
} x509certgetcontent_struct;

DEF_API(`void',`CDECL',`x509certgetcontent',`(x509certgetcontent_struct *p)',1,0xDA69570E,0x03050B00)

/**
 * <description>x509certgetprivatekey</description>
 */
typedef struct tagx509certgetprivatekey_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hCert;				/* VAR_INPUT */	
	RtsCryptoKey *pPrivateKey;			/* VAR_INPUT */	
	RTS_IEC_RESULT X509CertGetPrivateKey;	/* VAR_OUTPUT */	
} x509certgetprivatekey_struct;

DEF_API(`void',`CDECL',`x509certgetprivatekey',`(x509certgetprivatekey_struct *p)',1,0x279C9A63,0x03050B00)

/**
 * Get the PUBLIC key FROM the certificate.
 *
 * The format of this key is an implementation detail and has to match
 * the expected format of the asymmetric functions of the CmpCrpyotItf.
 * The key data is opaque for the user of the keys. If the keys are needed in a
 * defined exchange format use the CryptoKeyExport function of the CmpCryptoItf.
 * :return: Result of the operation. 
 */
typedef struct tagx509certgetpublickey_struct
{
	RTS_IEC_HANDLE hCert;				/* VAR_INPUT */	/* Handle of the certificate of intrest. */
	RtsCryptoKey *pPublicKey;			/* VAR_INPUT */	/* Pointer to the crypto key storing the public key. */
	RTS_IEC_RESULT X509CertGetPublicKey;	/* VAR_OUTPUT */	
} x509certgetpublickey_struct;

DEF_API(`void',`CDECL',`x509certgetpublickey',`(x509certgetpublickey_struct *p)',1,0x35142E48,0x03050B00)

/**
 * Generate the certificate thumbprint. The thumbprint will be just the plain bytes of the hash. 
 * The thumprint can be used to identify certificates of the local store. The thumprint may not be globally unique.
 * :return: Result of the operation.
 */
typedef struct tagx509certgetthumbprint_struct
{
	RTS_IEC_HANDLE hCert;				/* VAR_INPUT */	/* Handle of the certificate of intrest. */
	RTS_IEC_UDINT *hashAlgorithm;		/* VAR_INPUT */	/* The hashing algorithmen used to generate the thumbprint. */
	RtsByteString *pThumprint;			/* VAR_INPUT */	/* Buffer to store the thumbprint. If bytestring is NULL memory ia allocated. */
	RTS_IEC_RESULT X509CertGetThumbprint;	/* VAR_OUTPUT */	
} x509certgetthumbprint_struct;

DEF_API(`void',`CDECL',`x509certgetthumbprint',`(x509certgetthumbprint_struct *p)',1,0x5B1EA1C5,0x03050B00)

/**
 * Cleanup an RtsX509CertInfo structure. All allocated memory used by this strucutre will be release.
 * :return: Result of the operation
 */
typedef struct tagx509certinfoexit_struct
{
	RtsX509CertInfo *pCertInfo;			/* VAR_INPUT */	/* Pointer to the object to clean up. */
	RTS_IEC_RESULT X509CertInfoExit;	/* VAR_OUTPUT */	
} x509certinfoexit_struct;

DEF_API(`void',`CDECL',`x509certinfoexit',`(x509certinfoexit_struct *p)',1,0x4F4B0310,0x03050B00)

/**
 * Initialize the RtsX509CertInfo structure.
 * :return: Result of the operation
 */
typedef struct tagx509certinfoinit_struct
{
	RtsX509CertInfo *pCertInfo;			/* VAR_INPUT */	/* Pointer to the structure. */
	RTS_IEC_UDINT structSize;			/* VAR_INPUT */	/* Size of the structure. */
	RTS_IEC_RESULT X509CertInfoInit;	/* VAR_OUTPUT */	
} x509certinfoinit_struct;

DEF_API(`void',`CDECL',`x509certinfoinit',`(x509certinfoinit_struct *p)',1,0xD52F28DD,0x03050B00)

/**
 * Release a PRIVATE OR PUBLIC key with THIS FUNCTION. THIS FUNCTION
 * indicates that this key is not needed anymore and allows to clean up ressources
 * used by this key
 * :return: Result of the operation
 */
typedef struct tagx509certkeyclose_struct
{
	RtsCryptoKey *pKey;					/* VAR_INPUT */	/* Pointer to the key */
	RTS_IEC_RESULT X509CertKeyClose;	/* VAR_OUTPUT */	
} x509certkeyclose_struct;

DEF_API(`void',`CDECL',`x509certkeyclose',`(x509certkeyclose_struct *p)',1,0x6A598D05,0x03050B00)

/**
 * <description>x509certstoreaddcert</description>
 */
typedef struct tagx509certstoreaddcert_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hBackend;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hCert;				/* VAR_INPUT */	
	RTS_IEC_INT trustLevel;				/* VAR_INPUT, Enum: RTSCERTTRUSTLEVEL */
	RTS_IEC_RESULT X509CertStoreAddCert;	/* VAR_OUTPUT */	
} x509certstoreaddcert_struct;

DEF_API(`void',`CDECL',`x509certstoreaddcert',`(x509certstoreaddcert_struct *p)',1,0x690E5D79,0x03050B00)

/**
 * <description>x509certstoreclose</description>
 */
typedef struct tagx509certstoreclose_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_RESULT X509CertStoreClose;	/* VAR_OUTPUT */	
} x509certstoreclose_struct;

DEF_API(`void',`CDECL',`x509certstoreclose',`(x509certstoreclose_struct *p)',1,0x048C3968,0x03050B00)

/**
 * <description>x509certstoregetfirstcert</description>
 */
typedef struct tagx509certstoregetfirstcert_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hBackend;			/* VAR_INPUT */	
	RTS_IEC_INT trustLevel;				/* VAR_INPUT, Enum: RTSCERTTRUSTLEVEL */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE X509CertStoreGetFirstCert;	/* VAR_OUTPUT */	
} x509certstoregetfirstcert_struct;

DEF_API(`void',`CDECL',`x509certstoregetfirstcert',`(x509certstoregetfirstcert_struct *p)',1,0x9165907D,0x03050B00)

/**
 * <description>x509certstoregetnextcert</description>
 */
typedef struct tagx509certstoregetnextcert_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hBackend;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hCert;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE X509CertStoreGetNextCert;	/* VAR_OUTPUT */	
} x509certstoregetnextcert_struct;

DEF_API(`void',`CDECL',`x509certstoregetnextcert',`(x509certstoregetnextcert_struct *p)',1,0x894377FA,0x03050B00)

/**
 * <description>x509certstoregetregisteredcert</description>
 */
typedef struct tagx509certstoregetregisteredcert_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hUseCase;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE X509CertStoreGetRegisteredCert;	/* VAR_OUTPUT */	
} x509certstoregetregisteredcert_struct;

DEF_API(`void',`CDECL',`x509certstoregetregisteredcert',`(x509certstoregetregisteredcert_struct *p)',1,0x8C0F7D34,0x03050B00)

/**
 * <description>x509certstoreopen</description>
 */
typedef struct tagx509certstoreopen_struct
{
	RTS_IEC_UDINT componentID;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE X509CertStoreOpen;	/* VAR_OUTPUT */	
} x509certstoreopen_struct;

DEF_API(`void',`CDECL',`x509certstoreopen',`(x509certstoreopen_struct *p)',1,0xFE7CCE6C,0x03050B00)

/**
 * <description>x509certstoreregister</description>
 */
typedef struct tagx509certstoreregister_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_UDINT cmpID;				/* VAR_INPUT */	
	RtsX509CertInfo *pCertInfo;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE X509CertStoreRegister;	/* VAR_OUTPUT */	
} x509certstoreregister_struct;

DEF_API(`void',`CDECL',`x509certstoreregister',`(x509certstoreregister_struct *p)',1,0x35F7F607,0x03050B00)

/**
 * <description>x509certstoreremovecert</description>
 */
typedef struct tagx509certstoreremovecert_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hBackend;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hCert;				/* VAR_INPUT */	
	RTS_IEC_BOOL xRemovePrivateKey;		/* VAR_INPUT */	
	RTS_IEC_RESULT X509CertStoreRemoveCert;	/* VAR_OUTPUT */	
} x509certstoreremovecert_struct;

DEF_API(`void',`CDECL',`x509certstoreremovecert',`(x509certstoreremovecert_struct *p)',1,0x0E795BC4,0x03050B00)

/**
 * <description>x509certstoresearchgetfirst</description>
 */
typedef struct tagx509certstoresearchgetfirst_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RtsX509CertFilter *pFilters;		/* VAR_INPUT */	
	RTS_IEC_UDINT ui32NumOfFilters;		/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE X509CertStoreSearchGetFirst;	/* VAR_OUTPUT */	
} x509certstoresearchgetfirst_struct;

DEF_API(`void',`CDECL',`x509certstoresearchgetfirst',`(x509certstoresearchgetfirst_struct *p)',1,0,0x03050B00)

/**
 * <description>x509certstoresearchgetnext</description>
 */
typedef struct tagx509certstoresearchgetnext_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hCert;				/* VAR_INPUT */	
	RtsX509CertFilter *pFilters;		/* VAR_INPUT */	
	RTS_IEC_UDINT ui32NumOfFilters;		/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE X509CertStoreSearchGetNext;	/* VAR_OUTPUT */	
} x509certstoresearchgetnext_struct;

DEF_API(`void',`CDECL',`x509certstoresearchgetnext',`(x509certstoresearchgetnext_struct *p)',1,0,0x03050B00)

/**
 * <description>x509certstoreunregister</description>
 */
typedef struct tagx509certstoreunregister_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hRegisteredComponent;	/* VAR_INPUT */	
	RTS_IEC_RESULT X509CertStoreUnregister;	/* VAR_OUTPUT */	
} x509certstoreunregister_struct;

DEF_API(`void',`CDECL',`x509certstoreunregister',`(x509certstoreunregister_struct *p)',1,0xE41C13F3,0x03050B00)

/**
 * <description>x509certverify</description>
 */
typedef struct tagx509certverify_struct
{
	RTS_IEC_HANDLE hCertStore;			/* VAR_INPUT */	
	RTS_IEC_HANDLE hCert;				/* VAR_INPUT */	
	RTS_IEC_RESULT X509CertVerify;		/* VAR_OUTPUT */	
} x509certverify_struct;

DEF_API(`void',`CDECL',`x509certverify',`(x509certverify_struct *p)',1,0x9822EB29,0x03050B00)

/**
 * Parse a certificate which is located in the memory (e.g received FROM a
 * communication partner). Once parsed the certificate is stored
 * in a temporary store. Use the function X509CertClose to close the certificate.
 * :return: Handle to the parsed certificate.
 */
typedef struct tagx509parsecertificate_struct
{
	RtsByteString *pCert;				/* VAR_INPUT */	/* Binary encoded certificate. */
	RTS_IEC_INT encoding;				/* VAR_INPUT, Enum: RTSCERTENCODING */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Result of the operation */
	RTS_IEC_HANDLE X509ParseCertificate;	/* VAR_OUTPUT */	
} x509parsecertificate_struct;

DEF_API(`void',`CDECL',`x509parsecertificate',`(x509parsecertificate_struct *p)',1,0x01B27207,0x03050B00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

/**
 * <element name="Result" type="OUT">Result returned by X509CertCreateSelfSigned</element>
 * <element name="hCert" type="OUT">Handle of the geneatred certificate.</element>
 */
typedef struct
{
	RTS_RESULT Result;
	RTS_HANDLE hCert;
} X509CertCreateSelfSignedAsyncResult;

/**
 * <element name="Result" type="OUT">Result returned by X509CertCreateCSR</element>
 * <element name="hCert" type="OUT">Pointer to the RtsByteString given as parameter in X509CertCreateCSR containing the CSR.</element>
 */
typedef struct
{
	RTS_RESULT Result;
	RtsByteString* pCSR;
} X509CertCreateCSRAsyncResult;


typedef union
{
	X509CertCreateSelfSignedAsyncResult selfSigned;
	X509CertCreateCSRAsyncResult csr;
} X509AsyncOperationResult;

/**
 * <element name="ui32Operation" type="OUT">Identifier which operation was executed.</element>
 * <element name="Result" type="OUT">Result of the operation. Use the field according the ui32Operation.</element>
 * <element name="pCallbackParam" type="OUT">Pointer to callback parameter given in the X509CertCreate...Async function.</element>
 */
typedef struct
{
	RTS_UI32 ui32Operation;
	X509AsyncOperationResult Result;
	void* pCallbackParam;
} X509AsyncResult;

#define CMPX509CERT_ASYNC_FUNCTION_CREATESELFSIGNED		1
#define CMPX509CERT_ASYNC_FUNCTION_CREATECSR			2


typedef void HUGEPTR(CDECL *PFX509ASYNCCALLBACK)(X509AsyncResult *pAsyncStruct);



/* --------------------------------------------------------------------------- */
/*                             Static defines                                  */
/* --------------------------------------------------------------------------- */
/**
 * <category>Key Usage</category>
 * <description>These defines are the bits representing the key usages in the 
 * keyUsage field of the RtsX509CertInfo structure</description>
 */
#define RTS_KEY_USAGE_DIGITAL_SIGNATURE 0x1
#define RTS_KEY_USAGE_DIGITAL_SIGNATURE_STR "Digital Signature"
#define RTS_KEY_USAGE_NON_REPUDIATION 0x2
#define RTS_KEY_USAGE_NON_REPUDIATION_STR "Non Repudiation"
#define RTS_KEY_USAGE_ENCIPHERMENT 0x4
#define RTS_KEY_USAGE_ENCIPHERMENT_STR "Key Encipherment"
#define RTS_KEY_USAGE_DATA_ENCIPHERMENT 0x8
#define RTS_KEY_USAGE_DATA_ENCIPHERMENT_STR "Data Encipherment"
#define RTS_KEY_USAGE_KEY_AGREEMENT 0x10
#define RTS_KEY_USAGE_KEY_AGREEMENT_STR "Key Agreement"
#define RTS_KEY_USAGE_CERTIFICATE_SIGN 0x20
#define RTS_KEY_USAGE_CERTIFICATE_SIGN_STR "Certificate Sign"
#define RTS_KEY_USAGE_CRL_SIGN 0x40
#define RTS_KEY_USAGE_CRL_SIGN_STR "CRL Sign"
#define RTS_KEY_USAGE_ENCIPHER_ONLY 0x80
#define RTS_KEY_USAGE_ENCIPHER_ONLY_STR "Encipher Only"
#define RTS_KEY_USAGE_DECIPHER_ONLY 0x100
#define RTS_KEY_USAGE_DECIPHER_ONLY_STR "Decipher Only"

/**
 * <category>Object Identifiers</category>
 * <description>A list of well known OIDs in their string representations. Use this defines
 * with the function RtsOidCreate to generate a new OID object.</description>
 */
#define RTS_OID_COUNTRY_NAME                "2.5.4.6"
#define RTS_OID_ORGANIZATION_NAME           "2.5.4.10"
#define RTS_OID_ORGANIZATIONAL_UNIT_NAME	"2.5.4.11"
#define RTS_OID_COMMON_NAME				    "2.5.4.3"
#define RTS_OID_LOCALITY_NAME				"2.5.4.7"
#define RTS_OID_STATE_OR_PROVINCE_NAME		"2.5.4.8"
#define RTS_OID_TITLE						"2.5.4.12"
#define RTS_OID_GIVEN_NAME					"2.5.4.42"
#define RTS_OID_INITIALS					"2.5.4.43"
#define RTS_OID_SUR_NAME					"2.5.4.4"
#define RTS_OID_DOMAIN_COMPONENT			"0.9.2342.19200300.100.1.25"
#define RTS_OID_RSA_EMAILADDR				"1.2.840.113549.1.9.1"
#define RTS_OID_STREET_ADDRESS				"2.5.4.9"
#define RTS_OID_RSA_UNSTRUCTNAME			"1.2.840.113549.1.9.2"
#define RTS_OID_RSA_UNSTRUCTADDR			"1.2.840.113549.1.9.8"
#define RTS_OID_DEVICE_SERIAL_NUMBER		"2.5.4.5"
#define RTS_OID_TLS_WEBSERVER_AUTHENTICATION "1.3.6.1.5.5.7.3.1"
#define RTS_OID_TLS_WEBCLIENT_AUTHENTICATION "1.3.6.1.5.5.7.3.2"

/* --------------------------------------------------------------------------- */
/*                                  Types                                      */
/* --------------------------------------------------------------------------- */

typedef struct RtsCertBackendInfo_
{
	int dummy;
} RtsCertBackendInfo;


/* --------------------------------------------------------------------------- */
/*                                  Events                                     */
/* --------------------------------------------------------------------------- */

/**
 * <category>Events</category>
 * <description>Event which is called by the Certificate store to gather
 * the need for certificates from the differenct components. Register
 * your component to this event if you need a certificate plus a private key.
 * Use the Interfacefunction X509CertStoreRegister to register your certificate
 * informations. Doing so enables the user to view the configured certificates
 * and view missing certificates. Don't create certificates by your own. The
 * needed certificates will be generated by the Certificate store. Event is sent
 * if the user vies the certificate status out of the IDE. You can also register
 * your certificate at application startup. This event is the last chance to register
 * your certificate.
 *
 * This event is only needed if the component implements the management of the
 * certificate store.
 * </description>
 */
#define EVT_GetCertificatInfo		MAKE_EVENTID(EVTCLASS_INFO, 1)


#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------------------------------- */
/*                   Basic Certificate store functions                         */
/* --------------------------------------------------------------------------- */

/**
 * <description>Open the certificate store.</description>
 * <param name="componentID" type="IN">ID of the component opening the certificate store.</param>
 * <param name="pResult" type="OUT">Result of the operation.</param>
 * <result>Handle to the certificate store</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`X509CertStoreOpen',`(CMPID componentID, RTS_RESULT* pResult)')

/**
 * <description>Close the certificate store.</description>
 * <param name="hCertStore" type="IN">Handle of to certificate store.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertStoreClose',`(RTS_HANDLE hCertStore)')

/**
 * <description>Verify the given certificate. This verify checks only if the certificate
 * itself is trusted using the certificates in the store. The verify checks
 * if the certificate was added to the untrusted certs list. No subjects, key usages
 * or other fields are verified. This has to be done by the application using this function.
 * If the verify should use CRL to verify the certificates set the setting VerifyUseCRL to 1.
 * This is disabled by default.</description>
 * <param name="hCertStore" type="IN">Handle of to certificate store.</param>
 * <param name="hCert" type="IN">Certificate to verify.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertVerify',`(RTS_HANDLE hCertStore, RTS_HANDLE hCert)')

/**
 * <description>Search for the given certificate in the cert store.</description>
 * <param name="hCertStore" type="IN">Handle of to certificate store.</param>
 * <param name="pFilters" type="IN">Pointer to array of filters to be applied.</param>
 * <param name="ui32NumOfFilters" type="IN">Number of applied filters.</param>
 * <result>Handle to the first certificate matching the filter criteria.</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`X509CertStoreSearchGetFirst',`(RTS_HANDLE hCertStore, RtsX509CertFilter *pFilters, RTS_UI32 ui32NumOfFilters, RTS_RESULT *pResult)')

/**
 * <description>Search for the given certificate in the cert store.</description>
 * <param name="hCertStore" type="IN">Handle of to certificate store.</param>
 * <param name="hCert" type="IN">Handle of the last found certificate.</param>
 * <param name="pFilters" type="IN">Pointer to array of filters to be applied.</param>
 * <param name="ui32NumOfFilters" type="IN">Number of applied filters.</param>
 * <result>Handle to the first certificate matching the filter criteria.</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`X509CertStoreSearchGetNext',`(RTS_HANDLE hCertStore, RTS_HANDLE hCert, RtsX509CertFilter *pFilters, RTS_UI32 ui32NumOfFilters, RTS_RESULT *pResult)')


/* --------------------------------------------------------------------------- */
/*                      Handling single certificates                           */
/* --------------------------------------------------------------------------- */

/**
 * <description>Parse a certificate which is located in the memory (e.g received from a
 * communication partner). Once parsed the certificate is stored
 * in a temporary store. Use the function X509CertClose to close the certificate.
 * </description>
 * <param name="pCert" type="IN">Binary encoded certificate.</param>
 * <param name="encoding" type="IN">Encoding of the certificate.</param>
 * <param name="pResult" type="OUT">Result of the operation</param>
 * <result>Handle to the parsed certificate.</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`X509ParseCertificate',`(RtsByteString* pCert, RTSCERTENCODING encoding, RTS_RESULT* pResult)')

/**
 * <description>Get some common content from the certificate.</description>
 * <param name="hCert" type="IN">Handle of the certificate of intrest.</param>
 * <param name="pCertContent" type="OUT">Pointer where to store the information.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertGetContent',`(RTS_HANDLE hCert, RtsX509CertInfo* pCertContent)')

/**
 * <description>Get the certificate in a binary encoded format. Use the encoding parameter
 * to set the needed format.
 * </description>
 * <param name="hCert" type="IN">Handle of the certificate of intrest.</param>
 * <param name="encoding" type="IN">How to encode the certificate.</param>
 * <param name="pCert" type="OUT">Buffer where to store the certificate. If the bytestring contains a NULL memory pointer the function will write the needed bufferlength to the pCert->ui32Length member.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertGetBinary',`(RTS_HANDLE hCert, RTSCERTENCODING encoding, RtsByteString* pCert)')

/**
 * <description>Get the public key from the certificate.
 *
 * The format of this key is an implementation detail and has to match
 * the expected format of the asymmetric functions of the CmpCrpyotItf.
 * The key data is opaque for the user of the keys. If the keys are needed in a
 * defined exchange format use the CryptoKeyExport function of the CmpCryptoItf.
 * </description>
 * <param name="hCert" type="IN">Handle of the certificate of intrest.</param>
 * <param name="pPublicKey" type="OUT">Pointer to the crypto key storing the public key.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertGetPublicKey',`(RTS_HANDLE hCert, RtsCryptoKey* pPublicKey)')

/**
 * <description>Get the private key of the certificate. This is only
 * possible if the private key stored in the certificate store. 
 *
 * The format of this key is an implementation detail and has to match
 * the expected format of the asymmetric functions of the CmpCrpyotItf.
 * The key data is opaque for the user of the keys.
 * </description>
 * <param name="hCert" type="IN">Handle of the certificate of intrest.</param>
 * <param name="pPublicKey" type="OUT">Pointer to the crypto key storing the priave key.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertGetPrivateKey',`(RTS_HANDLE hCertStore, RTS_HANDLE hCert, RtsCryptoKey* pPrivateKey)')

/**
 * <description>Generate the certificate thumbprint. The thumbprint will be just the plain bytes of the hash.
 * Set the hash algorithm to your needs.</description>
 * <param name="hCert" type="IN">Handle of the certificate of intrest.</param>
 * <param name="hashAlgorithm" type="IN">The hashing algorithmen used to generate the thumbprint.</param>
 * <param name="pThumbprint" type="OUT">Buffer to store the thumbprint. If bytestring is NULL memory ia allocated.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertGetThumbprint',`(RTS_HANDLE hCert,  RTSCRYPTOID* hashAlgorithm, RtsByteString* pThumbprint)')

/**
 * <description>Check if a certificate has a valid date (notbefore and notafter is in the current time period)</description>
 * <param name="hCert" type="IN">Handle of the certificate</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">hCert is valid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">hCert is invalid</errorcode>
 * <result>Result of the operation</result>
 * <errorcode name="RTS_BOOL" type="TRUE">Date of certificate is valid</errorcode>
 * <errorcode name="RTS_BOOL" type="FALSE">Date of certificate is out of current period</errorcode>
 */
DEF_ITF_API(`RTS_BOOL',`CDECL',`X509CertIsDateValid',`(RTS_HANDLE hCert, RTS_RESULT *pResult)')

/**
 * <description>Check if a certificate is selfsigned of is signed by a CA authority</description>
 * <param name="hCert" type="IN">Handle of the certificate</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">hCert is valid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">hCert is invalid</errorcode>
 * <result>Result of the operation</result>
 * <errorcode name="RTS_BOOL" type="TRUE">Certificate is selfsigned</errorcode>
 * <errorcode name="RTS_BOOL" type="FALSE">Certificate is signed ba a CA authority</errorcode>
 */
DEF_ITF_API(`RTS_BOOL',`CDECL',`X509CertIsSelfSigned',`(RTS_HANDLE hCert, RTS_RESULT *pResult)')

/**
 * <description>Check if the extended keyusages of the specified certificate has the specified extended keyusages</description>
 * <param name="hCert" type="IN">Handle of the certificate</param>
 * <param name="numOfExKeyUsages" type="IN">Number of extended keyusages</param>
 * <param name="pExKeyUsages" type="IN">Pointer to list of extended keyusages</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">hCert is valid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">hCert is invalid</errorcode>
 * <result>Result of the operation</result>
 * <errorcode name="RTS_BOOL" type="TRUE">Extended keyusages identical</errorcode>
 * <errorcode name="RTS_BOOL" type="FALSE">Extended keyusages not identical identical</errorcode>
 */
DEF_ITF_API(`RTS_BOOL',`CDECL',`X509CertHasExtendedKeyUsage',`(RTS_HANDLE hCert, RTS_UI32 numOfExKeyUsages, RtsOID *pExKeyUsages, RTS_RESULT *pResult)')

/**
 * <description>Compare two certificates if they are identical.</description>
 * <param name="hCert1" type="IN">Handle to first certificate</param>
 * <param name="hCert1" type="IN">Handle to second certificate</param>
 * <result>TRUE if they are identical, FALSE if not.</result>
 */
DEF_ITF_API(`RTS_BOOL',`CDECL',`X509CertCompare',`(RTS_HANDLE hCert1, RTS_HANDLE hCert2)')

/**
 * <description>Release a private or public key with this function. This function
 * indicates that this key is not needed anymore and allows to clean up ressources
 * used by this key</description>
 * <para name="pKey" type="IN">Pointer to the key</param>
 * <result>Result of the operation</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertKeyClose',`(RtsCryptoKey* pKey)')

/**
 * <description>Close the certificate.</description>
 * <param name="hCert" type="IN">Handle of to certificate.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertClose',`(RTS_HANDLE hCert)')

/* --------------------------------------------------------------------------- */
/*                       Handling CMS containers                               */
/* --------------------------------------------------------------------------- */

/**
 * <description>Verifys a CMS signature. This function can handle both (detached and attached) signatures.
 * The signers certificate has to be located in the CMS container. Otherwhise the verify will fail.
 * The signers certificate is always verified against the trusted certificate store on the PLC.</description>
 * <param name="hCertStore" type="IN">Handle to the certificate store.</param>
 * <param name="pCms" type="IN">Pointer to a bytestring storing the CMS container.</param>
 * <param name="encoding" type="IN">Encoding of the CMS container.</param>
 * <param name="pInData" type="IN">Used only if the signature is detached. In this case this bytestring has to store the data to be verified</param>
 * <param name="pOutData" type="IN">Pointer to a bytestring where to store the extraced data.</param>
 * <result>ERR_OK if the signature is valid and the signer was trustworthy.
 * ERR_SIGNATURE_MISMATCH if the signature is invalid and / or the signer was not trustworthy.
 * ERR_PARAMETER if the given parameters are not consistent.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertCmsVerify',`(RTS_HANDLE hCertStore, RtsByteString* pCms, RTSCERTENCODING encoding, RtsByteString* pInData, RtsByteString* pOutData)')

/**
 * <description>The description of X509CertCmsVerify applies here too. Additional this interface returns a handle to the signers certificate.</description>
 * <param name="hCertStore" type="IN">Handle to the certificate store.</param>
 * <param name="pCms" type="IN">Pointer to a bytestring storing the CMS container.</param>
 * <param name="encoding" type="IN">Encoding of the CMS container.</param>
 * <param name="pInData" type="IN">Used only if the signature is detached. In this case this bytestring has to store the data to be verified</param>
 * <param name="pOutData" type="IN">Pointer to a bytestring where to store the extraced data.</param>
 * <param name="phSignerCert" type="IN">Pointer to a handle where to store the signers certificate. 
 *  This handle is only returned if the verification was successful. If the container was signed multiple times this handle contains the first valid certificate. 
 *  Can be NULL.
 * </param>
 * <result>ERR_OK if the signature is valid and the signer was trustworthy.
 * ERR_SIGNATURE_MISMATCH if the signature is invalid and / or the signer was not trustworthy.
 * ERR_PARAMETER if the given parameters are not consistent.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertCmsVerify2',`(RTS_HANDLE hCertStore, RtsByteString* pCms, RTSCERTENCODING encoding, RtsByteString* pInData, RtsByteString* pOutData, RTS_HANDLE* phSignerCert)')

/**
 * <description>Decrypt a CMS container.</description>
 * <param name="hCertStore" type="IN">Handle to the certificate store.</param>
 * <param name="hRecipientCert" type="IN">Handle to the recipients certificat. A private key of the certificate has to be available. Though the certificate has to be located in the "own" store.</param>
 * <param name="pCms" type="IN">Pointer to a bytestring storing the CMS container.</param>
 * <param name="encoding" type="IN">Encoding of the CMS container.</param>
 * <param name="pOutData" type="IN">Pointer to a bytestring where to store the extraced data.</param>
 * <result>ERR_OK if the container was successfully decrypted.
 * ERR_PARAMETER if the given parameters are not consistent.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertCmsDecrypt',`(RTS_HANDLE hCertStore, RTS_HANDLE hRecipientCert, RtsByteString* pCms, RTSCERTENCODING encoding, RtsByteString* pOutData)')

/* --------------------------------------------------------------------------- */
/*                             Utility functions                               */
/* --------------------------------------------------------------------------- */

/**
 * <description>Create an RtsOID based on a given ID.</description>
 * <param name="id" type="IN">OID as string in dottet format. E.g. (1.2.3.4.5.6.7.8.9.0)</param>
 * <param name="oid" type="OUT">Pointer to an OID to fill up.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RtsOIDCreate',`(char* id, RtsOID* oid)')

/**
 * <description>Get the ID of an OID in dottet notation.</description>
 * <param name="oid" type="IN">OID to print.</param>
 * <param name="pBuffer" type="OUT">Buffer where to store the name.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RtsOIDGetID',`(RtsOID* oid, RtsByteString* pBuffer)')

/**
 * <description>Get the given name of an OID. If the OID is unknown to the system the number.number.number... notation will be returned.</description>
 * <param name="oid" type="IN">OID to print.</param>
 * <param name="pBuffer" type="OUT">Buffer where to store the name.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RtsOIDGetName',`(RtsOID* oid, RtsByteString* pBuffer)')

/**
 * <description>Clear an OID</description>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RtsOIDClear',`(RtsOID* oid)')

/**
 * <description>Initialize the RtsX509CertInfo structure.</description>
 * <param name="pCertInfo" type="IN">Pointer to the structure.</param>
 * <param name="structSize" type="IN">Size of the structure.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertInfoInit',`(RtsX509CertInfo* pCertInfo, RTS_UI32 structSize)')

/**
 * <description>Cleanup an RtsX509CertInfo structure. All allocated memory used by this strucutre will be release.</description>
 * <param name="hCert" type="IN">Pointer to the object to clean up.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertInfoExit',`(RtsX509CertInfo* pCertInfo)')


/* --------------------------------------------------------------------------- */
/*                   Organizing the certificate store                          */
/*                                                                             */
/* The following functions are needed to manage the certificate store. If this */
/* management is not implemented by the component the functions should return  */
/* invalid handles and ERR_NOTIMPLEMENTED                                      */
/* --------------------------------------------------------------------------- */


/**
 * <description>Get the first registerd backend of the certificate store.</description> 
 * <param name="hCertStore" type="IN">Handle to the certificate store</param>
 * <param name="pInfo" type="OUT">Pointer to backend info. Filled up by the function.</param>
 * <param name="pResult" type="OUT">Result of the operation.</param>
 * <result>Handle of the first backend.</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`X509CertStoreGetFirstBackend',`(RTS_HANDLE hCertStore, RtsCertBackendInfo* pInfo, RTS_RESULT* pResult)')

/**
 * <description>Get the next registerd backend of the certificate store.</description>
 * <param name="hCertStore" type="IN">Handle to the certificate store</param>
 * <param name="hBackend" type="IN">Handle to the preverios backend.</param>
 * <param name="pInfo" type="OUT">Pointer to backend info. Filled up by the function.</param>
 * <param name="pResult" type="OUT">Result of the operation.</param>
 * <result>Handle of the next Backend. RTS_INVALID_HANDLE if no more backend is available.</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`X509CertStoreGetNextBackend',`(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsCertBackendInfo* pInfo, RTS_RESULT* pResult)')


/**
 * <description>The the information of a specific certificate backend.</description>
 * <param name="hCertStore" type="IN">Handle to the certificate store</param>
 * <param name="hBackend" type="IN">Handle to the preverios backend.</param>
 * <param name="pInfo" type="OUT">Pointer to backend info. Filled up by the function.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertStorGetBackendInfo',`(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsCertBackendInfo* pInfo)')

/**
 * <description>Create a new self signed certificate. A private key is generated and automatically stored.</description>
 * <param name="hCertStore" type="IN">Handle to the certificate store</param>
 * <param name="hBackend" type="IN">Handle to the backend where to store the generated certificate. RTS_INVALID_HANDLE should be used if no backend is specified.</param>
 * <param name="pCertInfo" type="IN">Information of the certificate to be generated.</param>
 * <param name="ui32KeySize" type="IN">Size in bits of the private key.</param>
 * <param name="pResult" type="OUT">Result of the operation.
 *      - ERR_OK: Everything went fine.
 *      - ERR_INVALID_HANDLE: Some input handle is invalid.
 *      - ERR_PARAMETER: Some input parameter is invalid.
 *      - ERR_OVERFLOW: The timestamps of the certificate would overflow.
 *      - ERR_NOMEMORY: Not enough memory to perform this operation.
 *      - ERR_FAILED: Creation of self signed certificate failed. failed</param>
 * <result>Handle to the created selfsigned certificate</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`X509CertCreateSelfSigned',`(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, RTS_UI32 ui32KeySize, RTS_RESULT *pResult)')

/**
 * <description>Create a new self signed certificate, asynchronously. A private key is generated and automatically stored.</description>
 * <param name="hCertStore" type="IN">Handle to the certificate store</param>
 * <param name="hBackend" type="IN">Handle to the backend where to store the generated certificate. RTS_INVALID_HANDLE should be used if no backend is specified.</param>
 * <param name="pCertInfo" type="IN">Information of the certificate to be generated.</param>
 * <param name="ui32KeySize" type="IN">Size in bits of the private key.</param>
 * <param name="ui32KeySize" type="IN">Size in bits of the private key.</param>
 * <param name="pCallbackParam" type="IN">Parameter used when the callback is called when the operation has finished.</param>
 * <param name="pfCallback" type="IN">Callback function that is called at the end of the operation</param>
 * <result>Result of the operation</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertCreateSelfSignedAsync',`(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, RTS_UI32 ui32KeySize, void* pCallbackParam, PFX509ASYNCCALLBACK pfCallback)')

/**
 * <description>Create a new certificate request. A new private key will be 
 * generated and automatically stored in the key store. The certificate request 
 * can be sent to an offical CA to get a signed certificate.</description>
 * <param name="hCertStore" type="IN">Handle to the certificate store</param>
 * <param name="hBackend" type="IN">Handle to the backend where to store the generated certificate. RTS_INVALID_HANDLE should be used if no backend is specified.</param>
 * <param name="pCertInfo" type="IN">Information of the certificate to be generated.</param>
 * <param name="ui32KeySize" type="IN">Size in bits of the private key.</param>
 * <param name="encoding" type="IN">Encoding of the generated CSR.</param>
 * <param name="pCSR" type="OUT">The signing request in binary form.</param>
 * <result>Result of the operation</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertCreateCSR',`(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, RTS_UI32 ui32KeySize, RTSCERTENCODING encoding, RtsByteString* pCSR)')

/**
 * <description>Create a new certificate request. A new private key will be 
 * generated and automatically stored in the key store. The certificate request 
 * can be sent to an offical CA to get a signed certificate.</description>
 * <param name="hCertStore" type="IN">Handle to the certificate store</param>
 * <param name="hBackend" type="IN">Handle to the backend where to store the generated certificate. RTS_INVALID_HANDLE should be used if no backend is specified.</param>
 * <param name="pCertInfo" type="IN">Information of the certificate to be generated.</param>
 * <param name="cmpID" type="IN">Component ID of the component for which the CSR is created.</param>
 * <param name="ui32KeySize" type="IN">Size in bits of the private key.</param>
 * <param name="encoding" type="IN">Encoding of the generated CSR.</param>
 * <param name="pCSR" type="OUT">The signing request in binary form.</param>
 * <param name="pCallbackParam" type="IN">Parameter used when the callback is called when the operation has finished.</param>
 * <param name="pfCallback" type="IN">Callback function that is called at the end of the operation</param>
 * <result>Result of the operation</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertCreateCSRAsync',`(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, CMPID cmpID, RTS_UI32 ui32KeySize, RTSCERTENCODING encoding, RtsByteString* pCSR, void* pCallbackParam, PFX509ASYNCCALLBACK pfCallback)')

/**
 * <description>Add the given certificate to the Certificate store</description>
 * <param name="hCertStore" type="IN">Handle of to certificate store.</param>
 * <param name="hBackend" type="IN">Handle to the backend where to store the generated certificate. RTS_INVALID_HANDLE should be used if no backend is specified.</param>
 * <param name="hCert" type="IN">Handle of the certificate to be imported.</param>
 * <param name="trustLevel" type="IN">The category where to store the certificate. Note: RtsTrustLevel_Own ist not selectable.</param>
 * <param name="pResult">Result of the operation.</param>
 * <result>Handle to the imported certificate.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertStoreAddCert',`(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTS_HANDLE hCert, RTSCERTTRUSTLEVEL trustLevel)')

/**
 * <description>Remove the certificate from the store.</description>
 * <param name="hCertStore" type="IN">Handle of to certificate store.</param>
 * <param name="hBackend" type="IN">Handle to the backend where to store the generated certificate. RTS_INVALID_HANDLE should be used if no backend is specified.</param>
 * <param name="hCert" type="IN">Handle of the certificate to remove.</param>
 * <param name="bRemovePrivateKey" type="IN">Select if the private key of the certificate should be deleted too. If the certificate is renewed the same private key the key shouldn't be deleted.</param>
 * <result>Result of the operation.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertStoreRemoveCert',`(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTS_HANDLE hCert, RTS_BOOL bRemovePrivateKey)')

/**
 * <description>Get the first certificate of the certificate store.</description>
 * <param name="hCertStore" type="IN">Handle of to certificate store.</param>
 * <param name="hBackend" type="IN">Pointer to a handle of the backend where to iterate. RTS_INVALID_HANDLE 
 * if all backends should be iterated. A valid handle if only a specific backend should be iterated.</param>
 * <param name="trustLevel" type="IN">Category of certificates to iterate.</param>
 * <param name="pResult" type="OUT">Result of the operation.</param>
 * <result>Handle to the first certificate of the given category.</param>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`X509CertStoreGetFirstCert',`(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTSCERTTRUSTLEVEL trustLevel, RTS_RESULT* pResult)')

/**
 * <description>Get the next certificate of the certificate store. If all certificates
 * are read the function will retrun RTS_INVALID_HANDLE.</description>
 * <param name="hCertStore" type="IN">Handle of to certificate store.</param>
 * <param name="hBackend" type="IN">Pointer to a handle of the backend where to iterate. RTS_INVALID_HANDLE 
 * if all backends should be iterated. A valid handle if only a specific backend should be iterated.</param>
 * <param name="hCert" type="IN">Handle to the last certificate got by X509CertStoreGetFirst or X509CertStoreGetNext</param>
 * <param name="pResult" type="OUT">Result of the operation.</param>
 * <result>Handle to the next certificate of the given category.</param>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`X509CertStoreGetNextCert',`(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTS_HANDLE hCert, RTS_RESULT* pResult)')

/**
 * <description>
 * Register your certificate at the certificate store. This has to be
 * done in order to allow the user the view the different configured certificates
 * and to generate missing certificates or to renew outdated certificates. Register the same
 * information you are using in the X509CertStoreSearch function.
 * </description>
 * <param name="hCertStore" type="IN">Handle of to certificate store.</param>
 * <param name="CmpID" type="IN">Component ID which registerd the certificate</param>
 * <param name="pCertInfo" type="IN">Certificate information to be registerd. Should match the information needed to use the Search function.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the entry</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`X509CertStoreRegister',`(RTS_HANDLE hCertStore, CMPID cmpID, RtsX509CertInfo* pCertInfo, RTS_RESULT* pResult)')

/**
 * <description>
 * </description>
 * <param name="hCertStore" type="IN">Handle of to certificate store</param>
 * <param name="hRegisteredComponent" type="IN">Handle to the entry retrieved by X509CertStoreRegister</param>
 * <result>Result of the operation</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`X509CertStoreUnregister',`(RTS_HANDLE hCertStore, RTS_HANDLE hRegisteredComponent)')

/**
 * <description>
 * Get the certificate available for a registered use case. If not certificate is available RTS_INVALID_HANDLE will be returned.
 * The following rules apply for selecting the certificate:
 * - Check if a certificate is configured by the user. (The thumbprint is pinned for component and index). Use this one if available, return error if not available.
 * - If no certificate is configured filter the available certificates by subject, key usage, extended key usage and a valid timestamp. Return error if list is empty.
 * - Split the available certificates by signed and self signed certificates. Prefer the signed certificates over the self signed certificates:
 * - Select the certificate with the longest period of validity.
 * - If some certificates have the same period of validity select the one with the strongest key.
 * </description>
 * <param name="hCertStore" type="IN">Handle of to certificate store.</param>
 * <param name="hUseCase" type="IN">Handle to the registered use case. Retrieved using X509CertStoreRegister.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the certificate. Use X509CertClose to close the certificat.</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`X509CertStoreGetRegisteredCert',`(RTS_HANDLE hCertStore, RTS_HANDLE hUseCase, RTS_RESULT* pResult)')

#ifdef __cplusplus
}
#endif



