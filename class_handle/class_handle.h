class class_hdl_base
{
public:
virtual class_hdl_base* clone() const =0;
};
template<class T>
class class_hdl
{
T *p;
int *use;
void decr_use(){if(--*use==0){if(p) delete p;delete use;}}
public:
class_hdl():p(0),use(new int(1)){}
class_hdl(const T &rhl):p(rhl.clone()),use(new int(1)){}
class_hdl(const class_hdl &rhl):p(rhl.p),use(rhl.use){++*use;}
class_hdl &operator=(const class_hdl &rhl){++*rhl.use;decr_use();p=rhl.p;use=rhl.use;return *this;}
~class_hdl(){decr_use();}

const T *operator->()const 
{if(p) return p;/*else throw std::logic_error("unbound");*/}
const T &operator*()const 
{if(p) return *p;/*else throw std::logic_error("unbound");*/}
};