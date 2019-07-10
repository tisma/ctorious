#include "syscalls.h"

.intel_syntax noprefix

.text

.global _start, syscall1, syscall2, syscall3, syscall4, syscall5

_start:
	xor rbp, rbp
	pop rdi
	mov rsi, rsp
	and rsp, 0xfffffffffffffff0
	call main
	mov rdi, rax
	mov rax, SYS_exit
	syscall
	ret

syscall:
	mov rax, rdi
	syscall
	ret

syscall1:
	mov rax, rdi
	mov rdi, rsi
	syscall
	ret

syscall2:
	mov rax, rdi
	mov rdi, rsi
	mov rsi, rdx
	syscall
	ret

syscall3:
	mov rax, rdi
	mov rdi, rsi
	mov rsi, rdx
	mov rdx, rcx
	syscall
	ret

sycall4:
	mov rax, rdi
	mov rdi, rsi
	mov rsi, rdx
	mov rdx, rcx
	mov r10, r8
	syscall
	ret

syscall5:
	mov rax, rdi
	mov rdi, rsi
	mov rsi, rdx
	mov rdx, rcx
	mov r10, r8
	mov r8, r9
	syscall
	ret

