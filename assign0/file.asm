global main
extern scanf
extern printf
segment .data
	x: dd 0
	s: times 100 db 0
	i: db "Input string : ",0
	j: db "Input number : ",0
	k: db "Entered string is %s",0x0a,0
	l: db "Entered number is %d",0x0a,0
	scans: db "%s",0
	scann: db "%d",0

segment .text
main:
	push rsp
	lea rdi,[i]
	xor eax,eax
	call printf

	lea rdi,[scans]
	lea rsi,[s]
	xor eax,eax
	call scanf

	;lea rdi,[k]
	lea rsi,[s]
	lea rdi,[k]
	xor eax,eax
	call printf
	
	lea rdi,[j]
	xor eax,eax
	call printf
	
	lea rdi,[scann]
	lea rsi,[x]
	xor eax,eax
	call scanf

	lea rdi,[l]
	mov edx,[x]
	xor eax,eax
	call printf
	
	mov rax,0
	pop rsp
	ret
