#ifndef UDP_PUNCH_HPP
#define UDP_PUNCH_HPP
#include <cassert>
#define IS_A(x) ((~x)&0x1)
#define IS_REQ(x) ((~x)&(0x1<<1))

struct TLV;
TLV *TLV_factory(int len);
TLV *TLV_factory(int t,int l,void *v=NULL);
void TLV_destroy(TLV* &tlv);


struct TLV
{
	uint16_t tag;
	uint16_t len;
	char val[0];
	TLV():tag(0),len(0){assert(4==sizeof(TLV));}
	TLV *clone(){return TLV_factory(tag,len,val);}
	private:
		~TLV(){}
};
struct packet
{
	u_short port;
	ACE_UINT32 ip;
	TLV *tlv;
	packet():port(0),ip(0),tlv(NULL){}
	packet(const ACE_INET_Addr& addr,TLV *_tlv=NULL):port(addr.get_port_number()),
		ip(addr.get_ip_address()),tlv(_tlv){}
};
TLV *TLV_factory(int len)
{
	TLV * tlv = (TLV *)malloc(len+sizeof(TLV));
	assert(tlv);
	new (tlv) TLV();
	tlv->tag=0;
	tlv->len=len;
	return tlv;
}
TLV *TLV_factory(int t,int l,void *v=NULL)
{
	TLV *tlv=TLV_factory(l);
	if(tlv)
	{
		tlv->tag=t;
		if(v)
			memcpy(tlv->val,v,l);
	}
	return tlv;
}
void TLV_destroy(TLV* &tlv)
{
	if(tlv)
		free(tlv);
	tlv=NULL;
}

#endif

