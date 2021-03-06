# Linux_Network_Programming

### Index
- [소켓프로그래밍](https://github.com/KimUJin3359/Linux_Network_Programming/blob/master/README.md#%EC%86%8C%EC%BC%93%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D)
- [Network 기본](https://github.com/KimUJin3359/Linux_Network_Programming/blob/master/README.md#network-%EA%B8%B0%EB%B3%B8)
- [프로토콜의 이해](https://github.com/KimUJin3359/Linux_Network_Programming/blob/master/README.md#%ED%94%84%EB%A1%9C%ED%86%A0%EC%BD%9C%EC%9D%98-%EC%9D%B4%ED%95%B4)
- [서버의 이해](https://github.com/KimUJin3359/Linux_Network_Programming/blob/master/README.md#%EC%84%9C%EB%B2%84%EC%9D%98-%EC%9D%B4%ED%95%B4)
- [Socket 통신 개요](https://github.com/KimUJin3359/Linux_Network_Programming/blob/master/README.md#socket-%ED%86%B5%EC%8B%A0-%EA%B0%9C%EC%9A%94)
- [Router](https://github.com/KimUJin3359/Linux_Network_Programming/blob/master/README.md#router)
- [OSI 7 Layer](https://github.com/KimUJin3359/Linux_Network_Programming/blob/master/README.md#osi-7-layer)
- [IP Subnetting](https://github.com/KimUJin3359/Linux_Network_Programming/blob/master/README.md#ipsubnetting)
- [TCP/IP](https://github.com/KimUJin3359/Linux_Network_Programming/blob/master/README.md#tcp--ip)

---

#### [소켓프로그래밍](https://github.com/KimUJin3359/Linux_Network_Programming/tree/master/socket)
- 서버와 클라이언트가 서로 Read, Wirte
- 클라이언트가 종료되도 서버는 꺼지지 않음
- 클라이언트가 다시 접속하면 채팅이 이뤄짐
- 서버를 끄면 클라이언트도 종료

---
### Network 기본
#### 인터넷 원리
- Network
  - Net : 그물
  - 노드와 링크로 구성된 데이터 교환망
    - 노드 : 컴퓨팅 장치들
    - 링크 : 연결
- IP 주소
  - 노드들의 고유 ID
  - IPv4, IPv6
- 공유기(라우터)의 사용
  - PC끼리 연결하지 않고, 공유기를 거쳐 연결
  - 연결 PC가 늘어나도, 사용하는 랜카드는 PC당 1개
- 케이블
  - STP Cable
    - UTP : Unshieleded Twisted-Pair
    - STP : Shielded Twisted-Pair
    - EMI 방지를 위한 호일을 한번 더 감은 고급 케이블
  - UTP Cable
    - 다이렉트 케이블
    - 크로스 케이블
    - 잘못 사용하면 통신이 안됨
    - Auto MDI : 아무 케이블만 꽂아도, 잘 동작하는 기술(임베디드 보드들은 미지원)
    - PC, PC 등 동일 기종 간에는 크로스 케이블
    - PC와 Router 등 이기종 간에는 다이렉트 케이블
  - 동축케이블
  - 광(섬유)케이블
    - 빛 굴절을 이용하요, 선이 꺾이더라도 직진성으로 전달
  - 전송 스펙
    - CAT5e : 1Gbps, 100MHz 대역폭
    - CAT6 : 1Gbps, 250MHz 대역폭
    - CAT7 : 10Gbps, 600MHz 대역폭

#### 서버와 DNS

![그림](https://user-images.githubusercontent.com/50474972/114398417-bcf0b700-9bda-11eb-8692-59c68114fe30.JPG)

- 인터넷의 발전
  - 어떠한 한 공유폴더를 공유하여 사용했음
    - 해당 공유폴더를 가지고 있는 컴퓨터가 종료하면, 다른 작업을 하지 못함
    - 공용 컴퓨터(서버, 24시간 계속 켜두는 컴퓨터)를 둬서 위의 문제를 해결
- 인터넷의 창시자
  - 팀 버너스리
  - www(world wide web) : 가장 거대한 네트워크
  - w3c : www의 협회장
  - HTML 문서의 규격을 만듬
  - HTML 문서를 읽어내는 것 : 웹 브라우저
  - 해당 서버에 접속하려면 서버의 IP주소를 입력
- 렌더링
  - 소스코드(java script)를 가져와 빌드하여 보여주는 것
  - 브라우저를 렌더링 머신이라고도 함
- DNS(Domain Name System)
  - 사람이 이해하기 쉬운 도메인 주소를 IP로 변환
  - 인터넷상의 전화번호부  

#### 네트워크 분류
- 규모에 따른 분류
  - LAN(Local Area Network)
    - 랜카드 : 근거리 통신망을 위한 네트워크 카드
    - 랜케이블 : 근거리 통신망 용 케이블
    - 집안 / 사무실 / 소규모 공장 수준
    - Ethernet 방식으로 사용하는 소규모 네트워크
  - WAN(Wild Area Network)
    - LAN보다 넓은 네트워크를 의미
  - 인터넷
    - 가장 거대한 네트워크
    - ISP(Internet Service Provider) 업체 신청하여, 전용선 + IP를 사용
- Cell : 무선 이동통신을 위해 하나의 기지국이 포괄하는 범위
- Cellular
  - 한 지역을 여러개의 셀로 분할하여 운용하는 통신 방식
  - 주파수를 알뜰하게 쓰기 위함
  - 주파수 대역 : 사람의 수에 따라 대역폭이 많이 필요함
- IoT
  - 무선 네트워크가 Default 통신 방식
  - 네트워크 규모, 특징에 따라 필요한 속도, 가격 존재
    - 무선 LAN : Wifi/BLE
    - 실외 : Cellular - LTE/5G
    - 무선 WAN(LowerPowerWAN) : 낮은 전력으로 넓은 범위에서 쓸 수 있는 방법

---

### 프로토콜의 이해
- 프로토콜 : 통신의 약속
  - 통신의 두 주체가 같은 프로토콜을 쓴다면, 약속된 규칙으로 통신이 가능
  - HW : 장비 규칙, 신호 전달 속도
  - Format : 신호의 형태
  - Sequence : Handshake 방식, 신호 전달 순서
  - SW 동작 : 오류 검출을 위한 행동
- 프로토콜을 이해해야 하는 이유
  - 완벽한 통신 Application 제작 가능
  - 통신 App을 위한 Library 제작 가능
  - 프로토콜 내용대로 수행하는 Server 구축 가능

#### TCP/IP
- IP(Internet Protocol)
  - 송신 호스트와 수신 호스트가 정보를 주고받는데 사용하는 규약
  - 패킷 혹은 데이터그램이라고 하는 덩어리로 나뉘어 전송
  - 비 연결성
    - 패킷을 받을 대상이 없거나 해당 도착지의 주소가 불능 상태여도 패킷을 전송
  - 비 신뢰성
    - 통신 도중 패킷이 사라질 수 있음
    - 패킷이 순서대로 도착하지 않을 수 있음
  - IP Address : 인터넷 상에 있는 컴퓨터의 고유한 주소

```
이더넷(LAN) : CSMA/CD 사용, MAC주소를 통한 정보 공유
인터넷 : TCP/IP 사용, IP Address를 통한 정보 공유
TCP/IP 사용 시 라우터가 길을 미리 세팅(라우팅 : MST)
```

- TCP(Transmission Control Protocol)
  - 전송 제어 프로토콜
  - IP의 핵심 프로토콜 중 하나
  - 연결 지향(3way handshake)
  - 데이터 전달 보증
  - 순서 보증
  - 신뢰할 수 있는 프로토콜
- UDP(User Datagram Protocol)
  - 데이터 전달, 순서 보장 X
  - 속도가 빠름

#### Ethernet Cable
- 전송속도(bit rate)
  - bit per second(bps)
  - 초당 몇 bit를 전송하는지

  | UART 통신 | USB 통신 |
  | --- | --- |
  | 0.01MBps | 400MBps |
  | 느리다 | 빠름 |

- USB 통신을 쓰지 않는 이유
  - 엔지니어에게 USB는 어려움(개발시간, spec up)
  - 전력
- 대역폭
  - 주파수
    - 최대와 최소 주파수의 폭
    - 폭이 넓을수록 정보를 한꺼번에 실을 수 있는 양이 커짐
  - 통신
    - 한번에 데이터를 전송할 수 있는 양

---

### 서버의 이해
#### 서버의 구성
- Client들이 접속하여 쓸 수 있는 시스템
- 특징
  - 대부분 무중단 운영
  - 대용량 트래픽 처리
- 역할
  - 웹 서버 : Client들에게 HTTP 문서를 전달하는 서버
  - DB 서버 : Client들의 DB를 관리하는 서버
  - 게임 서버 : Client들의 게임 데이터를 관리, 처리해주는 서버
- 하나의 PC를 여러 역할의 서버(DB 서버, 파일 서버, 게임 서버)로 사용
  - 단점
    - 개인용 PC를 계속 켜두어야 함
    - 개인용 자료가 유출 될 수 있음
    - 개인 PC에서 게임을 돌리면, 모든 서버들 속도가 낮아짐
- 여러 역할을 하는 서버를 사용
  - 장점
    - 개인용 PC는 자유롭게 사용
  - 단점
    - 서버용 컴퓨터는 항상 켜둠
    - 누군가 파일 서버에서 다운로드를 받고 있으면, 웹이 먹통
- 모든 서버를 따로 시스템을 둠
  - 장점
    - 보안에 안전
    - 간섭으로 인한 속도 저하가 없음
  - 단점
    - 관리가 힘듦
- 핸드폰을 서버로 사용
 
#### 로드밸런싱
- 웹 서버 한대가 처리할 수 있는 트래픽
- 접속자가 많아지면 다음 문젤 성능 이슈 발생
  - 네트워크 회선 문제
  - SSD Read 성능 문제
- 웹 서버를 여러대 두고 분할로 접속하도록 구성하면 속도가 빨라짐
- 하나의 웹 서버가 죽었을 때, 무중단 운영이 가능

#### 클라우드
- 인터넷을 이용하여, 가상화된 시스템 리소스를 사용할 수 있는 것
  - 자신의 컴퓨터가 아닌, 서버 컴퓨터 자원을 사용하는 기술
  - 전산 운영 비용을 줄일 수 있음
    - 월 정기 : 서버 관리자 급여 / 전기비 / 사무실 임대료 / 회선 비용
    - 일시적 : L4 스위치 / 방화벽 / 랙 / 항온항습 장치 / UPS 등
- Auto Scailing
  - 장비 없이 장비 세팅이 편함 : 로드 밸런싱이 몇 번의 클릭으로 이루어짐
  - 서버의 개수가 자동으로 조절 설정 가능
    - 트래픽이 많아지면, 서버의 수가 늘어남
- 전산실 운영
  - 적정 온도, 습도 유지
    - 항온 항습 시스템
    - 공기 여과기 등
  - UPS 설치
    - 비상 전력 시스템
  - 물리적 보안
  - 서버 관리자
  - 서버 랙
    - 안정적인 전원 공급
    - 먼지 관리
- 코로케이션(IDC 입주 서비스)
  - 전산실 필수 도구 구비완비 : 전기비, 빠른 전용선, 안정적 전력
  - 추가서비스 : 방화벽, 위탁운영, 백업 서비스
- 서버실 운영 문제점
  - 특정 일에만 트래픽이 몰리는 경우
- 가상화 기술
  - 한 대의 고성능 컴퓨터에서 시뮬레이션 SW 컴퓨터를 생성
  - 시뮬레이션 환경이지만, 실제 컴퓨터와 똑같이 동작
  - 사용자는 시뮬레이션인지 실제 컴퓨터인지 구분이 어려움

#### IaaS
- Infrastructure as a Service
- 컴퓨팅 시스템을 가상화 환경으로 만들어, 서비스를 제공

#### PaaS
- Platform as a Service
- 바꿀 없는 기본 시스템이 구축되어 있는 상태에서 App 개발/ 배포/ DB 관리 등 가능한 상태의 시스템

#### SaaS
- Software as a Service
- 서버에서 호스팅 방식으로 서비스 제공

#### 인증 팩터
- 인증할 수 있는 요소
  - 지식 기반 Factor : Password
  - 소유 기반 Factor : OTP, 키파일, 공인인증서
- 인증 개수
  - SFA(싱글 팩터 인증)
  - 2FA(투 팩터 인증)
  - MFA(멀티 팩터 인증)
- Hash(Cryptographic Hash Function)
  - 입력시 예측할 수 없는 암호화된 데이터가 나옴
  - Encoding은 가능하지만, Decoding은 불가
  - 원본 값 한 글자만 바뀌어도, 예측 불가한 숫자가 나옴
  - 같은 코드값이 나올 확률이 매우 희박
  - 사용
    - 파일 무결성 검사
    - 스니핑(도청) 방지
- 암호화 방식
  - SHA-2
    - Hash를 사용한 암호화
    - 디코딩을 할 수 없음
  - RSA
    - 공개키, 개인키로 암호화 하는 방식
    - 개인키가 있으면 디코딩을 할 수 있음

---

### Socket 통신 개요
- Socket : TCP/IP 통신을 하기위한 SW 객체
- Socket의 Interface만 맞추면 통신 가능
  - TCP/UDP
  - IP/OORT
- Linux Kernel은 Socket을 파일로 관리

#### 통신 조건
- Server와 Client 모두 Socket 객체를 생성해서 서로 연결 필요
- 상대방의 IP주소와 Port 번호를 알고 있어야 함
  - 한 Port 당 하나의 소켓 통신이 가능
  - 하나의 Host에서 동시에 여러 소켓 통신을 할 수 있도록 여러 Port를 지원
    - 개인적으로 사용하는 Port는 기본적으로 막혀있음
    - Port 방화벽을 열어야 함

#### 방화벽 허용
- iptables -I INPUT '숫자' -p tcp --dport '포트번호' -j ACCEPT
  - -I 옵션 : 인바운드 설정, 규칙 #'숫자'번
  - -p 옵션 : tcp, ip 설정
  - --dport 옵션 : 몇 번 포트를 설정할지 결정
  - -j 옵션 : 처리를 ACCEPT할지 DENY할지 결정
- 확인 방법
  - ping
  - nc
    - nc -l '포트번호' : 메세지 서버를 엶
    - nc 'IP주소' '포트번호' : 메세지 서버에 접속 

---

### Router
#### 메시지 전달 방법
- Unicast : 한 노드에게로 전달
- Broadcast : 모든 노드에게로 전달
- Multicast : 그룹핑 후, 해당 그룹에게만 전달

#### Unicast
- 1대 1로 데이터를 전송
- 허브
  - 데이터, 출발지, 도착지를 적어둠
    - 시작주소 : 자신의 MAC
    - 도착주소 : 도착지의 MAC
  - LAN은 모든 네트워크에 신호를 뿌림
    - 각 노드는 자신의 메세지가 아니라면 무시하고 버림
    - NIC에서 처리하기에, CPU까지 도달되지 않음
- 스위치
  - 스위치의 MAC Address Table
  - 메세지를 보낸 노드의 MAC 주소가 어느 포트에 있는지 저장해둠
  - 도착지 MAC 주소 확인 후, MAC Table을 확인하여 어느 포트에 있는지 바로 알아낼 수 있음
  - 만약, MAC Table에 없다면 브로드캐스팅으로 전체에 신호를 뿌림

#### ARP
- Address Resolution Protool
- IP만으로 MAC 주소를 찾을 떄 사용하는 프로토콜
  - 일반적으로 LAN환경에서는 MAC 주소를 기반으로 통신
- 동작 방식
  - 전체 브로드캐스팅
  - 만약 Target이 나를 찾는 다는 것을 알게되면 Target Node는 MAC 주소를 담아 응답
  - 브로드캐스트는 라우터가 차단
    - 다른 네트워크로 넘어가지 않음
- 단점
  - ARP를 받으면 NIC가 아닌 CPU가 처리
  - ARP Request 발생 시
    - 각 NIC들이 해당 MAC 주소를 받음
    - Interrupt 발생
    - 자신의 IP 주소와 일치하는지 확인
    - 자신의 IP 주소와 일치하면 Response
  - 스위치를 써서 막을 수 있는 것
    - collision 차단
  - 스위치를 써도 못막는 것
    - ARP로 인한 PC들 성능 저하

#### Router
- 한 네트워크에 PC가 많을수록 브로드캐스팅이 자주 발생
  - 브로드캐스팅 신호끼리 collison 발생 가능성이 높아짐
  - collision이 많이 발생할 수록 통신 지연 발생
  - ARP Request가 많아짐
    - 잦은 Interrupt로 PC도 느려짐
- 네트워크 분할 필요
  - 브로드캐스트 영역을 라우터를 이용하여 분할
- 라우터의 역할
  - 스위치와 달리 라우터는 복잡한 Firmware(OS Level)로 동작
  - Gateway : 서로 다른 네트워크 통신 목적
  - 브로드캐스트 영역을 나누기 위함
  - 라우터끼리 연결되어있을 떄, 지능적으로 배정 가능

---

### OSI 7 Layer
- ISO에서 정한 통신의 추상화 단계
  - OSI : Open Systems Interconnection
  - 통신은 Hardware, Software 모두가 필요
  - 통신에 필요한 동작을 7단계로 나눔
- 계층화를 통한 장점
  - 커뮤니케이션 용도
    - HW 장비 지칭 : 통신에서 어떤 역할을 하는 장비인지 Layer 번호로 표현
    - SW 소스 코드 : 통신에서 어떤 역할을 하는 소스코드인지 Layer 번호로 표현
    - Data : 어떤 단계에서 만들어진 Data인지 Layer 번호로 표현 가능
- 처리 과정
  - 신호 전달 과정
    - App에서 시작하여 App에 도달하기까지 과정을 계층별로 생각할 수 있음
  - 통신 과정을 세부적으로 나눔
    - 모든 단계를 거치는 것이 필수가 아님
    - 통신에 따라 일부 과정은 생략

#### Data관점에서 OSI 7 Layer
- App Layer에서 메세지로 부터 시작
  - App에서 전달하고 싶은 메세지가 존재
  - 각 단계별로 '헤더' 정보를 하나씩 추가
  - 최종적으로 만들어진 데이터를 프레임이라고 함
- 데이터 링크 계층
  - 만들어진 데이터(PDU)를 프레임이라고 함
  - Frame Header에는 MAC 주소가 적힘
- 네트워크 계층
  - 만들어지는 데이터를 Packet이라고 함
  - Packet Header에는 IP 주소가 적힘
  - 라우터는 프레임을 열고, 헤더를 확인하여 경로를 읽어냄
    - L2 Header: MAC / L3 Header : IP주소
    - Header에 적힌 목적지를 확인하여 전달
- 전송 계층
  - 오류 관련, 속도, 포트번호를 적어줌
- 그 외 상위 계층
  - 필요한 경우에 사용되며, L6, L7은 사용되지 않는 경우도 존재
  - L5(Session Layer) : 통신의 동기화 정보
  - L6(Presentation Layer) : 데이터 압축, 암호화 정보
  - L7(Application Layer) : 사용자 데이터

#### SW관점에서 OSI 7 Layer
- L7(Application) : Application
- L6(Presentation) : 압축/암호화 소스코드
- L5(Session)
- L4(Transport) : Port Header 추가
- L3(Network) : IP Header 추가
- L2(Datalink) : 네트워크 드라이버(장치제어)
- L1(Physical) : SW없음(허브, 랜선, 랜카드)

#### HW관점에서 OSI 7 Layer
- HW 관점에서 커뮤니케이션
  - 장비관리 수월
  - L1 ~ L7 장비
  - 추상화로 Interface만 맞추어주면 다른 장비들 개발 가능
- L1장비 : 전기적 신호를 처리하는 곳
  - 허브, NIC, UTP 케이블
- L2장비 : LAN 영역의 Data 정보전달(ethernet, MAC 연관)
  - L2 스위치
- L3장비 : 네트워크 데이터 전달(IP 확인)
  - 라우터, L3 스위치
- L4장비 : IP 뿐만 아니라 TCP의 포트까지 확인하여, IP 수정하여 경로를 변경
  - L4 스위치, 로드밸런싱
- L7장비 : 컨텐츠 내용을 확인 후 스위칭 가능
  - URL, 쿠키 등을 확인하여 로드밸런싱 가능
  - L7 스위치

---

### IP/Subnetting
#### IP주소
- 공인 IP
  - ICANN 조직 아래 5개의 RIR로 나누어 관리
  - RIR에는 각 나라별 NIR로 나누어 관리
  - 한국은 KRNIC라고 함
  - KRNIC에서 KT/SK Broadband/U+ 같은 LIR이 존재
- 구조
  - Network Part + Host Prt
  - 브로드캐스팅 영역에 있는 노드들은 Network Part 값이 모두 같은 값을 가져야 함
  - Host Part는 모두 다른 값을 가져야 함
- 공인 IP Class
  - 네트워크 크기에 따라 Class를 나눔
    - 유니캐스트로 사용할 수 있는 Class는 A, B, C만 가능
  - C class
    - 192.0.0.0 ~ 233.255.255.0까지 사용
    - 앞 24bit는 네트워크 주소, 1Byte를 host 주소로 사용
  - B class
    - 128.0.0.0 ~ 191.255.0.0까지 사용
    - 앞 16bit는 네트워크 주소, 2Bytes를 host 주소로 사용
  - A class
    - 127.0.0.0 이전 IP 주소들
    - 앞 8 bit 네트워크 주소, 3Bytes를 host 주소로 사용
- 사설 IP
  - NIC에서 하지 않고, 네트워크 고나리자가 직접 할당
  - IETF 표준

  | 사설 IP 주소 대역 | 주소 갯수 |
  | --- | --- |
  | `10.0.0.0` | `16,777,216` |
  | `172.[16:31].0.0` | `1,048,576` |
  | `192.168.0.0` | `65,536` |
  
- 특수한 IP 주소
  - 사용하지 않는 IP주소
    - 네트워크 주소를 표기 : HOST ID의 모든 bit가 0인 주소
    - Broadcast 주소 : Host ID의 모든 bit가 1인 주소

#### 서브넷 마스크
- 역할
  - 서브넷 마스크를 씌워 네트워크 영역을 더 잘게 나눔
    - B 클래스를 NIC에서 할당 받으면 Host는 65534개 받을 수 있음
  - 서브넷 마스크를 쓰지 않으면, 한 네트워크에 너무 많은 PC가 붙어있어 브로드캐스트가 너무 많아짐
    - 통신이 불가
- 사용 이유
  - class를 쓰지않고, NAT + Cassless Address를 사용하기 때문
- 프리픽스 표기법
  - 서브넷 마스크를 1과 0으로 표기하지 않고 한번에 표기
  ```
  /24
  - MSB부터 24비트를 네트워크 주소로 
  ```

#### NAT와 DHCP
- IP주소 : NIC(Network Information Center)에서 관리
  - 공인 IP 라고 함
  - IPv4 : 0.0.0.0 ~ 255.255.255.255
  - IoT 시대에서 부족한 양
- NAT(Network Address Translation)
  - 게이트웨이 밖으로 나갈 때는 공인 IP 주소 사용
  - 내부 네트워크에서는 사설 IP를 사용하는 방식
  - 라우터는 보내는 패킷을 라우팅 가능, 받는 패킷을 라우팅 할 수 없음
    - 받는 패킷의 목적지의 IP주소가 사설IP이기 때문
  - 역할
    - 사설 IP <--> 공인 IP 변환 기술
    - NAT Table에 사설 IP + 공인 IP 조합을 저장
- DHCP
  - 한 네트워크에 같은 IP주소가 없도록 자동 할당 기능
    - 공유기가 DHCP 접속을 가지고 있어, Wifi 접속시 별 다른 설정 없이 자동할당
    - 특정 MAC을 가진 Device는 특정 IP를 할당하게 끔 가능
  - 임베디드에서 인터넷 연결 시
    - DHCP 서버 세팅을 해야 IP 할당 가능
    - IP를 수동으로 할당하는 것이 더 편리할 때가 많음

#### Subnetting
- 여러 개의 네트워크로 만들어씀
- 특징
  - 라우팅이 있어야 서브넷팅이 의미가 있음
  - 서브넷 마스크에서 2진수의 1은 연속적으로 나와야 함
  ```
  21.100.0.0
  공인주소를 네트워크 당 PC 30대, 네트워크로 43개를 만들어 라우터로 통신하려면 서브넷 마스크는 몇번으로 설정해야 되는가?
  21.100.0.0 -> 00010101 01100100 00000000 00000000
  PC 30대 -> 2^5
  뒤에서부터 5비트를 host 주소로 사용
  subnetmask : 27
  ```
  
---  
  
### TCP / IP
- IP 프로토콜
  - Internet Protocol
  - node에서 node로 패킷을 전달하는 내용의 프로토콜
- TCP 프로토콜
  - Transmission Control Protocol
  - 전송 사고 등 처리
  - 패킷이 뒤섞여도, 보낸 순서대로 받게 해주는 프로토콜
  - 에러 검사, 에러 발생 시 재전송
- TCP/IP Protocol Suite
  - 인터넷에서 사용하는 프로토콜 집합
  - ICMP
    - IP 주소로 통신할 떄 통신의 성공, 실패를 나타내는 메세지 프로토콜
   
  | Protocol Suite |
  | --- |
  | `Network Application` |
  | `TCP`  `UDP` |
  | `ARP` `IP` `ICMP` |
  | `NIC` |
  
#### 주요 내용
- Packet
  - 인터넷에서는 패킷이라는 단위로 데이터를 전달
  - Header + Data + Tailer로 구성
- TCP와 UDP의 차이

  | TCP | UDP |
  | --- | --- |
  | 연결지항 | 비연결지향 |
  | 데이터의 선로를 만듬, Session을 생성 | 단순히 패킷을 던지거나 받는 방식 |
  | 오류 발생시 재전송 | 일부 손실이 있더라도 큰 지장이 없는 멀티미디어 정보 전달시 사용 |
  | 패킷 순서 섞여도 보낸 순서에 맞추어 응답 |
  
- Handshake
  - Session에 상호간의 접속이 필요
  - establish : 상호간 접속으로 통신의 성립을 뜻하는 말
  - 3 way handshake
    - establish 할 때 사용
  - 4 way handshake
    - session closed에 사용
- Port
  - 동시 다발적 통신을 위한 가상의 문을 뜻함
  - Port Number
    - Well-know Port Number(0 ~ 1023)
    - Registered Port(1024 ~ 49151) : 여러 Tool이 쓰는 포트(3306:MySQL, 8080:HTTP 대체)
    - Dynamic Port(49152 ~ 65535) : 필요할 때 마다 임의의 번호를 사용

---

### 보안
#### 방화벽
- 개인(Private) 방화벽
  - PC상에서 SW로 동작하는 방화벽
  - 허용된 포트만 접속 가능하도록 설정
  - 특정 조건에만 접속 가능하도록 설정
    - 인/아웃 바운드 설정
    - 특정 IP만 접속 허용하도록 설정
  - 부적절한 Data 사전 차단
- 라우터 방화벽
  - 하나의 방화벽으로는 부족
  - 해커의 침입 가능성을 최소로 줄여야함
- 방화벽 뚫는 방법
  - 데이터 위장술
    - 정상적인 데이터인척 위장하여 방화벽 안으로 침투
    - 이메일 : 정상적인 데이터지만, 사용자가 클릭하게 유도
  - 방화벽은 정상적인 데이터를 거르지 못함
    - 보안 SW를 함께 사용해야함
    - 방화벽 : Invalid 신호 차단
    - 보안 SW : Valid한 신호이지만, 악성 코드 차단

#### Cookie
- Client PC에 저장해두는 파일 내용들
- 경로 : C:\Users\'user name'\AppData\Local\Google\Chrome\User Data\Default
  - 상대방 컴퓨터에서 이 파일만 볼 수 있다면, 방문한 사이트들을 모두 볼 수 있음
- 단점
  - 보안이 취약
  - 공용 PC의 경우 개인정보가 그대로 들어남
  - 광고주가 Targeting 광고로 활발히 사용 중
    - 어느 사이트들에 접속했는지, 해당 사이트들의 쿠키 값들도 수집 가능
  - 해당 수집한 정보를 다른 곳으로 전달 및 판매 가능
- 2022년 크롬 쿠키 중단

#### OWASP
- The Open Web Application Security Project
  - 웹 정보노출, 악성코드, 보안 취약점 등을 연구하는 프로젝트
  - OWASP Top10은 여러 취약점 중 가장 위협이 되는 열 가지를 선정하여 매년 발표
- SQL Injection
  - 가장 널리 사용되면서도, 위험한 공격기법
  - Client가 SQL 명령어를 대신 수행하여 정보들을 추출 가능함
  - DB 삭제 가능, 데이터 납치 가능

---

### 컴퓨터 네트워크 관련 질문
- OSI Layer 7에 대해 설명하세요
  - OSI란 Open System Interconnection의 약자로, 네트워크에서 통신이 일어나는 과정을 7 단계로 나눈 것입니다
  - 이렇게 7계층으로 분리를 해 둔 이유는 통신이 일어나는 과정을 단계별로 파악할 수 있고, 특정 계층에 문제가 생기면 다른 단계의 장비 및 소프트웨어를 건드리지 않고 이상이 생긴 부분에서만 수정하면 되기 때문입니다
- TCP/IP에 대해 설명하세요
  - TCP는 전송 계층의 신뢰성 있고, 연결지향적인 프로토콜이며, IP는 네트워크 계층의 데이터 전송을 위한 프로토콜입니다
  - TCP/IP라고 불리는 이유는 TCP는 데이터의 흐름을 제어할 수 있지만 직접적인 경로 설정 등 전송의 역할은 IP가 함으로 둘은 반드시 함께 사용되기 때문입니다
- TCP/IP 4 계층에 대해 설명하세요
  - TCP/IP 4계층은 OSI를 실제 사용하는 인터넷 표준입니다
  - 네트워크 액세스 계층, 인터넷 계층, 전송 계층, 응용 게층으로 구분됩니다
  - 인터넷 계층에는 ICMP, IP, ARP 등의 프로토콜, 전송 계층에는 TCP, UDP 등의 프로토콜, 응용 계층에는 FTP, Telnet 등의 프로토콜이 존재합니다
- OSI 7 Layer 각 계층별로 설명하세요
  ```
  물리 계층은 물리적인 장비들로 직접적인 전송을 하는 계층이며, 데이터 링크 계층은 물리 계층에서 데이터를 송/수신 할 때 발생하는 오류나 흐름을 관리합니다.
  네트워크 계층은 데이터를 목적지까지 전달하는 역할 즉 라우팅이 주된 역할이며, 전송 계층은 통신을 활성화하기 위한 계층입니다.
  세션 계층은 세션 설정 등 통신하기 위한 논리적인 연결을 담당하며, 표현 계층은 암호화, 압축 등의 역할을 수행합니다. 마지막으로, 응용 계층은 사용자 간의 인터페이스 등을 담당합니다.
  ```
