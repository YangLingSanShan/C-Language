#define read(a) {char c;while((c=getchar())>47) a=a*10+(c^48);}        //�꺯�����
void isPrime(int n,int is_prime[])//����ɸ����is_prime���±�Ϊ������λ��ӳ��Ϊ1������Ϊ0
{
    for (int i = 2;i < n;i++)
        is_prime[i] = 1;
    for (int i = 2;i * i < n;i++)
    {
        if (is_prime[i] == 1)
            for (int j = i * i;j < n;j += i)
                is_prime[j] = 0;
    }
}
/*�Ż���ŷ��ɸ
int prime[N], cnt, notPrime[N + 1]; // ����ͬ��:ȫ���Ϊ0��������
for (int i = 2; i < N; i++)
{
    if (!notPrime[i]) prime[cnt++] = i; // ��¼����
    for (int j = 0; j < cnt && prime[j] <= n / i; j++) // j ��һ����Ŷ��ѣ�prime[j] ��������˵�� p
    {
        not_prime[i * prime[j]] = 1; // ɸ��
        if (i % prime[j] == 0) break; // ��� prime[j] | i��˵������ i ����С�����ӣ�����������Ͳ���Ҫ��
    }
}
*/
long long Sum_One(long long target)//ͳ�� target��1�ĸ���
{
    long long sum = target;
    sum = (sum & 0x5555555555555555) + ((sum >> 1) & 0x5555555555555555);
    sum = (sum & 0x3333333333333333) + ((sum >> 2) & 0x3333333333333333);
    sum = (sum & 0x0F0F0F0F0F0F0F0F) + ((sum >> 4) & 0x0F0F0F0F0F0F0F0F);
    sum = (sum * (0x0101010101010101) >> 56);
    return sum;
}
/*λ���������
* 1.��a+b��>>1���������޷�������������0����ƽ����
* 2. y=(1<<a)|(1<<b)|(1<<c); //�õ�һ����a,b,cλ����1����
*    x=x|y;//��x��a,b,cλ����Ϊ1
* 3. x=~(1<<d)&x; //��x�ĵ�dλ����Ϊ-0
* 4. n&(n-1)//���ã���n�Ķ����Ʊ�ʾ�е����λΪ1�ĸ�Ϊ0,��һ���ÿ�����չ���ܶ��÷�������������������1�ĸ���������N����������2�ĸ���
* 5. n > 0 && ((n & (n - 1)) == 0 ) //�ж�һ�����Ƿ���2�ķ���
* 6. n&(-n) //��ʾ��һ����ֻ�Ǳ��������������ұߵ�1��λ
*/


/*������
*#include <stdio.h>
long long fastPower(long long base, long long power,long long p) 
{
    long long result = 1;
    while (power > 0) {
        if (power & 1) 
        {
            result = result * base % p;
        }
        power >>= 1;
        base = (base * base) % p;
    }
    return result;
}
int main()
{
    long long a, b, p;
    scanf("%lld%lld%lld", &a, &b, &p);
    printf("%lld", fastPower(a, b, p));
}
*/
/*
 �������ݡ��㲻֪���ж��������룬Ҳû�����Ե���������ı�־������ʱ������ʹ�����´��룺
int n;
while (scanf("%d", &n) != EOF){
    // do something
}
�ô����ʾ����ִͣ�� scanf("%d", &n) ��ֱ�������ļ�ĩβ(EOF, End Of File)����Windows��ִ�д˴��룬�������ʱ�����԰���Ctr + Z������һ���س���Ϊ�����ṩ�������ļ�ĩβ���źţ�ʹ����������whileѭ���Ӷ�����������
*/