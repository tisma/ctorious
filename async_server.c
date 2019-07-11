#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define N_BACKLOG 64

void perror_die(char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void report_peer_connected(const struct sockaddr_in* sa, socklen_t salen) {
	char hostbuf[NI_MAXHOST];
	char portbuf[NI_MAXSERV];
	if (getnameinfo((struct sockaddr*)sa, salen, hostbuf, NI_MAXHOST, portbuf, NI_MAXSERV, 0) == 0) {
		printf("peer (%s, %s) connected\n", hostbuf, portbuf);
	} else {
		printf("peer (unknown) connected\n");
	}
}

int listen_inet_socket(int portnum) {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror_die("ERROR opening socket");
	}

	int opt = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		perror_die("setsockopt");
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portnum);

	if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		perror_die("ERROR on binding");
	}

	if (listen(sockfd, N_BACKLOG) < 0) {
		perror_die("ERROR on listen");
	}

	return sockfd;
}

void make_socket_non_blocking(int sockfd) {
	int flags = fcntl(sockfd, F_GETFL, 0);
	if (flags == -1) {
		perror_die("fcntl F_GETFL");
	}

	if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
		perror_die("fcntl F_SETFL O_NONBLOCK");
	}
}


int main(int argc, const char** argv) {
	setvbuf(stdout, NULL, _IONBF, 0);

	int portnum = 9988;
	if (argc >= 2) {
		portnum = atoi(argv[1]);
	}
	printf("Listening on port %d\n", portnum);

	int sockfd = listen_inet_socket(portnum);
	struct sockaddr_in peer_addr;
	socklen_t peer_addr_len = sizeof(peer_addr);

	int newsockfd = accept(sockfd, (struct sockaddr*)&peer_addr, &peer_addr_len);
	if (newsockfd < 0) {
		perror_die("ERROR on accept");
	}
	report_peer_connected(&peer_addr, peer_addr_len);

	int flags = fcntl(newsockfd, F_GETFL, 0);
	if (flags == -1) {
		perror_die("fcntl F_GETFL");
	}

	if (fcntl(newsockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
		perror_die("fcntl F_SETFL O_NONBLOCK");
	}

	while (1) {
		uint8_t buf[1024];
		printf("Calling recv...\n");
		int len = recv(newsockfd, buf, sizeof(buf), 0);
		if (len < 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				usleep(200 * 1000);
				continue;
			}
			perror_die("recv");
		} else if (len == 0) {
			printf("Peer disconnected; I'm done.\n");
			break;
		}
		printf("recv returned %d bytes\n", len);
	}

	close(newsockfd);
	close(sockfd);

	return 0;
}

