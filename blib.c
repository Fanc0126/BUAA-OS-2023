#include <blib.h>

size_t strlen(const char *s) {
	size_t length;
	for(length=0;s[length]!='\0';length++);
	return length;
}

char *strcpy(char *dst, const char *src) {
	char *res=dst;
	while(*src){
		*dst++=*src++;
	}
	*dst='\0';
	return res;
}

char *strncpy(char *dst, const char *src, size_t n) {
	char *res = dst;
	while (*src && n--) {
		*dst++ = *src++;
	}
	*dst = '\0';
	return res;
}

char *strcat(char *dst, const char *src) {
	char *res = dst;
	size_t i,j;
	for(i=0;dst[i]!='\0';i++);
	for(j=0;src[j]!='\0';j++,i++)
	{
		dst[i]=src[j];
	}
	dst[i]='\0';
	return res;
}

int strcmp(const char *s1, const char *s2) {
	size_t i;
	int ans;
	for(i=0;s1[i]!='\0'&&s2[i]!='\0'&&s1[i]==s2[i];i++);
	if(s1[i]==s2[i])
		ans=0;
	else if(s1[i]<s2[i])
		ans=-1;
	else
		ans=1;
	return ans;
}

int strncmp(const char *s1, const char *s2, size_t n) {
	while (n--) {
		if (*s1 != *s2) {
			return *s1 - *s2;
		}
		if (*s1 == 0) {
			break;
		}
		s1++;
		s2++;
	}
	return 0;
}

void *memset(void *s, int c, size_t n) {
	const unsigned char uc = c;
	unsigned char *su;
	for(su = s;0 < n;++su,--n)
		*su = uc;
	return s;
}

void *memcpy(void *out, const void *in, size_t n) {
	char *csrc = (char *)in;
	char *cdest = (char *)out;
	for (int i = 0; i < n; i++) {
		cdest[i] = csrc[i];
	}
	return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
	const unsigned char *su1=s1;
	const unsigned char *su2=s2;
	int i;
	for(i=0;i<n;i++){
		if(su1[i]<su2[i])
			return -1;
		else if(su1[i]>su2[i])
			return 1;
	}
	return 0;

}
