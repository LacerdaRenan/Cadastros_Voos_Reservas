#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define TAMANHO_DATA 11
#define NMR_VOO 9
#define NMR_RESERVA 10
#define BASE 10
#define CPF 15

//LIMPA TELA
void clear(){
	system("clear||cls");
}

//PAUSA...
void pause(){
	printf("\nPressione ENTER para continuar\n");
	setbuf(stdin,NULL);
	getchar();
	
}

//CONVERTE UMA STRING PARA UM INTEIRO	
int string_para_inteiro(char aux[]){
	return strtol(aux,NULL,BASE);
}

//_____________________________________________________________________
//Dados referentes à dia, mes e ano.
struct DATA{
	int dia;
	int mes;
	int ano;
};
typedef struct DATA DATA;

//_____________________________________________________________________
//Dados referentes a horas e minutos.
struct HORAS{
	int hora;
	int minutos;
};
typedef struct HORAS HORAS;

//_____________________________________________________________________
//Dados para cadastro de voo.
struct DADOS_VOO{
	char numero_voo[NMR_VOO];
	int nmr_passageiros;
	HORAS hora_voo;
	DATA data_voo;
	int status_voo; //1 para Ativo, 0 para Cancelado.
};
typedef struct DADOS_VOO DADOS_VOO;

//_____________________________________________________________________
//Dados para cadastro de reserva.
struct DADOS_RESERVA{
	char numero_reserva[NMR_RESERVA];
	char numero_voo[NMR_VOO];
	char cpf[CPF];
	char nome[100];
	char sexo;
	DATA data_nascimento;
	int status_reserva;//1 para Ativo, 0 para Cancelado.
};
typedef struct DADOS_RESERVA DADOS_RESERVA;

//_____________________________________________________________________
//VERIFICAR SE UM NUMERO DE CADASTRO FOI ESCRITO CORRETAMENTE
int verifica_cadastro(char nmr_cadastro[], int escolha){
	
	if(escolha==1){
		if(strlen(nmr_cadastro)!=NMR_VOO-1){
			clear();
			printf("\nDADOS INVALIDOS\n");
			pause();
			return 0;
		}else if((nmr_cadastro[0] != 'J')||(nmr_cadastro[1]!='E')||(nmr_cadastro[2] != 'B')||(nmr_cadastro[3] != '-')||(!isdigit(nmr_cadastro[4]))||(!isdigit(nmr_cadastro[5]))||(!isdigit(nmr_cadastro[6]))||(!isdigit(nmr_cadastro[7]))){
			clear();
			printf("\nDADOS INVALIDOS\n");
			pause();
			return 0;
		}else{
			return 1;
		}
	}else{
		if(strlen(nmr_cadastro)!=NMR_RESERVA-1){
			clear();
			printf("\nDADOS INVALIDOS\n");
			pause();
			return 0;
		}else if((nmr_cadastro[0] != 'G')||(nmr_cadastro[1]!='B')||(nmr_cadastro[2] != '-')||(!isdigit(nmr_cadastro[3]))||(!isdigit(nmr_cadastro[4]))||(!isdigit(nmr_cadastro[5]))||(!isdigit(nmr_cadastro[6]))||(!isdigit(nmr_cadastro[7]))||(!isdigit(nmr_cadastro[8]))){
			clear();
			printf("\nDADOS INVALIDOS\n");
			pause();
			return 0;
		}else{
			return 1;
		}
	}
	
}

//VERIFICAR SE O NUMERO DE VOO JÁ ESTÁ CADASTRADO NO ARQUIVO
int verifica_arquivo_voo(char nmr_voo[]){
	
	//Encerra a função caso o tamanho da string seja invalido
	if (strlen(nmr_voo)!=NMR_VOO-1){
		return 0;
	} 
	
	DADOS_VOO pesquisa_voo;
	FILE *file = fopen("dados_voo.bin", "rb");
	
	if(file == NULL){
		printf("\nVOO AINDA NAO CADASTRADO, PASSIVEL DE CADASTRO\n");
		pause();
		return 1;
	}else{
		while (fread(&pesquisa_voo,sizeof(DADOS_VOO),1,file)==1){
			if(strcmp(pesquisa_voo.numero_voo,nmr_voo)==0){
				clear();
				printf("\nVOO JA CADASTRADO!\n");
				pause();
				fclose(file);
				return 0;
			}
		}
		printf("\nVOO AINDA NAO CADASTRADO, PASSIVEL DE CADASTRO\n");
		pause();
		fclose(file);
		return 1;
	}
}

//VERIFICA SE OS DADOS INFORMADOS PELO USUÁRIO SÃO NUMEROS
int verifica_numero(char numero[]){
	int i;
	
	for(i=0;i<strlen(numero);i++){
		if(!isdigit(numero[i])){
			clear();
			printf("\nDADOS INVALIDOS\n");
			pause();
			return 0;
		}
	}
	return 1;
}

//VERIFCA SE A DATA É VÁLIDA
int verificador_data(int dia, int mes, int ano){
	
	  
	if (mes >= 1 && mes <= 12){
        if ((dia >= 1 && dia <= 31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12))
            return 1;
        else if ((dia >= 1 && dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11))
            return 1;
        else if ((dia >= 1 && dia <= 28) && (mes == 2))
            return 1;
        else if (dia == 29 && mes == 2 && (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)))
            return 1;
        else
            clear();
			printf("\nDATA INVALIDA\n");
			pause();
			return 0;
    }else{
        clear();
		printf("\nDATA INVALIDA\n");
		pause();
		return 0;
    }
	
}

//VERIFICA SE A HORA INFORMADA É CORRETA
int verifica_horas(char horas[],char H){
	if(H =='H'){
		if(string_para_inteiro(horas)<24){
			return 1;
		}else{
			clear();
			printf("\nDADOS INVALIDOS\n");
			pause();
			return 0;
		}
	}else{
		if(string_para_inteiro(horas)<60){
			return 1;
		}else{
			clear();
			printf("\nDADOS INVALIDOS\n");
			pause();
			return 0;
		}
	}
}

//VERIFICA SE O NUMERO DE RESERVA JÁ ESTÁ CADASTRADO
int verifica_reserva(char reserva[]){
	
	//Encerra a função caso o tamanho do numero da reserva seja inválido
	if(strlen(reserva)!= NMR_RESERVA-1){
		return 0;
	}
	
	DADOS_RESERVA verifica;
	int i;
	int j=0;
	FILE *file = fopen("dados_reserva.bin", "rb");
	
	if(file == NULL){
		return 1; //Se não for encontrado nenhum arquivo, significa que posso cadastrar qualquer numero de reseva
	}else{
		while (fread(&verifica,sizeof(DADOS_RESERVA),1,file)==1){

			if(strcmp(verifica.numero_reserva,reserva)==0){
				clear();
				printf("\nRESERVA JA FOI CADASTRADA, TENTE NOVAMENTE\n");
				pause();
				fclose(file);
				return 0;
			}
		}
		fclose(file);
		return 1;
	}
}

//VERIFICA SE HÁ VAGAS PARA NOVOS PASSAGEIROS EM UM VOO
int verifica_vagas_ocupadas(char voo[]){
	
	DADOS_RESERVA consultar_reserva;
	DADOS_VOO consultar_voo;
	int k=0;
	
	FILE *file_voo = fopen("dados_voo.bin","rb");
	if(file_voo==NULL){
		return 0;//Encerrar a pesquisa caso não haja nenhum voo cadastrado.
	}
	
	FILE *file_reserva = fopen("dados_reserva.bin", "rb");
	if(file_reserva==NULL){
		fclose(file_voo);
		return 1;//Caso não haja nenhum arquivo de reserva, então o voo ainda possui todas suas vagas livres.
	}else{ // Caso haja reservas, vamos verificar se o numero de reservas já feitas é igual ao numero max de passageiros no voo.
		while(fread(&consultar_reserva,sizeof(DADOS_RESERVA),1,file_reserva)==1){
			if(strcmp(consultar_reserva.numero_voo, voo)==0){
				k++;
			}
		}
		if(k==0){
			fclose(file_reserva);
			fclose(file_voo);
			return 1; //Todas as vagas do voo estão livres.
		}else{
			while(fread(&consultar_voo,sizeof(DADOS_VOO),1,file_voo)==1){
				if(strcmp(consultar_voo.numero_voo,voo)==0){
					if(consultar_voo.nmr_passageiros==k){
						clear();
						printf("\nESTE VOO ESTA LOTADO\n");
						pause();
						fclose(file_reserva);
						fclose(file_voo);
						return 0; //Voo lotado.
					}else{
						fclose(file_reserva);
						fclose(file_voo);
						return 1; //Voo com vagas.
					}
				}
			}
		}
	}
}

//VERIFICA SE O CPF FOI ESCRITO DE FORMA CORRETA, TAMBEM VERIFICA SE O CPF JA ESTÁ CADASTRADO EM ALGUM VOO
int verifica_cpf(char aux[], char voo[], int opc){
	
	int i;
	int j=0;
	DADOS_RESERVA consulta_cpf;
	
	if(strlen(aux)!=CPF-1){
		clear();
		printf("\nDADOS INVALIDOS\n");
		pause();
		return 0;
	}else if((isdigit(aux[0])&&isdigit(aux[1])&&isdigit(aux[2])&&isdigit(aux[4])&&isdigit(aux[5])&&isdigit(aux[6])&&isdigit(aux[8])&&isdigit(aux[9])&&isdigit(aux[10])&&isdigit(aux[12])&&isdigit(aux[13]))==0){
		clear();
		printf("\nDADOS INVALIDOS\n");
		pause();
		return 0;
	}else if((aux[3]!='.')||(aux[7]!='.')){
		clear();
		printf("\nDADOS INVALIDOS\n");
		pause();
		return 0;
	}else if(aux[11]!='-'){
		clear();
		printf("\nDADOS INVALIDOS\n");
		pause();
		return 0;
	}else if(opc == 1){
		FILE *file = fopen("dados_reserva.bin","rb");
	
		if(file == NULL){
			return 1;
		}else{
			while(fread(&consulta_cpf,sizeof(DADOS_RESERVA),1,file)==1){
				if(strcmp(consulta_cpf.numero_voo,voo)==0){
					if(strcmp(consulta_cpf.cpf, aux)==0){
						clear();
						printf("\nPASSAGEIRO JA ESTA CADASTRADO NESTE VOO, TENTE NOVAMENTE\n");
						pause();
						fclose(file);
						return 0;
					}
				}
			}
			fclose(file);
			return 1;
		}
	}else{
		return 1;
	}
}

//VERIFICA SE O NOME DO PASSAGEIRO É UM NOME VÁLIDO
int verifica_nome(char nome[]){
	int i;
	
	if(isspace(nome[0])){
		clear();
		printf("\nDADOS INVALIDOS\n");
		pause();
		return 0;
	}else if(nome[0]=='\0'){
		clear();
		printf("\nDADOS INVALIDOS\n");
		pause();
		return 0;
	}else{
		for(i=0;i<strlen(nome);i++){
			if(((isalpha(nome[i]))||(isspace(nome[i])))==0){
				clear();
				printf("\nDADOS INVALIDOS\n");
				pause();
				return 0;
			}
		}
	}
	return 1;
}

//VERIFICA SE O SEXO EH UM CARACTER VALIDO
int verifica_sexo(char aux[]){
	if(strlen(aux) != 1){
		clear();
		printf("\nDADOS INVALIDOS\n");
		pause();
		return 0;
	}else if((aux[0] == 'M')||(aux[0] == 'm')){
		return 1;
	}else if((aux[0] == 'F') || (aux[0] =='f')){
		return 1;
	}else{
		clear();
		printf("\nDADOS INVALIDOS\n");
		pause();
		return 0;
	}
}

//FUNÇÃO PARA CADASTRO DE UM NOVO VOO (Completo, testado)
void cadastrar_voo(){
	
	//Caso não haja arquivo para cadastro, o mesmo será criado!
	DADOS_VOO novo_voo;
	
	
	char aux[50];
	int i;
	int aux_dia;
	int aux_mes;
	int aux_ano;
	
	
	//Cadastro de numero de voo (completo, testado)
	do{
		clear();
		printf("\n___________________________________");
		printf("\nCADASTRO DE VOO\n\n");
		printf("INFORME O CODIGO DO NOVO VOO:\n");
		setbuf(stdin,NULL);
		scanf("%s",aux);
	}while((verifica_cadastro(aux, 1)&&verifica_arquivo_voo(aux))==0);
	strcpy(novo_voo.numero_voo,aux);


	//Cadastro do numero de passageiros(completo, testado)
	do{
		clear();
		printf("\n___________________________________");
		printf("\nCADASTRO DE VOO\n\n");
		printf("INFORME O NUMERO DE PASSAGEIROS\n");
		setbuf(stdin,NULL);
		scanf("%s", aux);
		if(aux[0]=='0'){
			clear();
			printf("\nDADOS INVALIDOS\n");
			pause();
		}
	}while((verifica_numero(aux)&&(aux[0]!='0'))==0);
	novo_voo.nmr_passageiros=string_para_inteiro(aux);
	
	
	//Cadastro da data do voo(completo, testado)
	do{
		do{
			clear();
			printf("\n___________________________________");
			printf("\nCADASTRO DE VOO\n\n");
			printf("INFORME O DIA DO VOO\n");
			setbuf(stdin,NULL);
			scanf("%s", aux);
		}while(!verifica_numero(aux));
		aux_dia=string_para_inteiro(aux);
		
		do{
			clear();
			printf("\n___________________________________");
			printf("\nCADASTRO DE VOO\n\n");
			printf("INFORME O MES DO VOO\n");
			setbuf(stdin,NULL);
			scanf("%s", aux);
		}while(!verifica_numero(aux));
		aux_mes=string_para_inteiro(aux);
		
		do{
			clear();
			printf("\n___________________________________");
			printf("\nCADASTRO DE VOO\n\n");
			printf("INFORME O ANO DO VOO\n");
			setbuf(stdin,NULL);
			scanf("%s", aux);
		}while(!verifica_numero(aux));
		aux_ano=string_para_inteiro(aux);
		
	}while(!verificador_data(aux_dia, aux_mes, aux_ano));
	novo_voo.data_voo.dia=aux_dia;
	novo_voo.data_voo.mes=aux_mes;
	novo_voo.data_voo.ano=aux_ano;
	
	//Cadastro da hora de voo(completo, testado)
	do{
		clear();
		printf("\n___________________________________");
		printf("\nCADASTRO DE VOO\n\n");
		printf("INFORME A HORA DO VOO. EX(22)\n");
		setbuf(stdin,NULL);
		scanf("%s", aux);
	}while((verifica_horas(aux,'H')&&(verifica_numero(aux)))==0);
	novo_voo.hora_voo.hora = string_para_inteiro(aux);
	
	do{
		clear();
		printf("\n___________________________________");
		printf("\nCADASTRO DE VOO\n\n");
		printf("INFORME O MINUTO DO VOO. EX(55)\n");
		setbuf(stdin,NULL);
		scanf("%s", aux);
	}while((verifica_horas(aux,'M')&&(verifica_numero(aux)))==0);
	novo_voo.hora_voo.minutos = string_para_inteiro(aux);
	
	novo_voo.status_voo=1; // voo ativo
	
	FILE *cadastro = fopen("dados_voo.bin", "ab");
	fwrite(&novo_voo,sizeof(DADOS_VOO),1,cadastro);
	
	fclose(cadastro);
	
}

//CADASTRA UMA NOVA RESERVA
void cadastrar_reserva(){
	
	DADOS_RESERVA nova_reserva;
	char aux[100];
	int i;
	int aux_dia;
	int aux_mes;
	int aux_ano;
	
	
	//Cadastro do numero de reserva(testado, completo)
	do{
		clear();
		printf("\n___________________________________");
		printf("\nCADASTRO DE RESERVA\n\n");
		printf("INFORME O CODIGO DA NOVA RESERVA:\n");
		setbuf(stdin,NULL);
		scanf("%s",aux);
	}while((verifica_cadastro(aux,2)&&verifica_reserva(aux))==0);
    strcpy(nova_reserva.numero_reserva,aux);
    
	//cadastro do voo da reserva, possibilidade de criar novo voo(testado, completo)
	int k=0;
	do{
		if(k!=0){
			clear();
			printf("\nVOCE DESEJA CADASTRAR UM NOVO VOO? SIM(S)  NAO(N)\n");
			setbuf(stdin,NULL);
			aux[0]=getchar();
			if((aux[0]=='s')||(aux[0]=='S')){
				cadastrar_voo();
				printf("\nAGORA PRESSIONE ENTER E EM SEGUIDA INFORME O NUMERO DO VOO QUE VOCE CADASTROU\n");
				pause();
			}
		}
		clear();
		printf("\n___________________________________");
		printf("\nCADASTRO DE RESERVA\n\n");
		printf("INFORME O CODIGO DO VOO PARA A RESERVA:\n");
		setbuf(stdin,NULL);
		scanf("%s",aux);
		k++;
	}while((verifica_cadastro(aux,1)&&!verifica_arquivo_voo(aux)&&verifica_vagas_ocupadas(aux))==0);
    strcpy(nova_reserva.numero_voo,aux);

	//Cadastro de cpf(testado,completo)
	do{
		clear();
		printf("\n___________________________________");
		printf("\nCADASTRO DE RESERVA\n\n");
		printf("INFORME O CPF: XXX.XXX.XXX-XX\n");
		setbuf(stdin,NULL);
		scanf("%s",aux);
	}while(!verifica_cpf(aux, nova_reserva.numero_voo,1));
    strcpy(nova_reserva.cpf,aux);

	//Cadastro de nome(testado, completo)
	char c;
	do{
		clear();
		printf("\n___________________________________");
		printf("\nCADASTRO DE RESERVA\n\n");
		printf("INFORME O NOME DO PASSAGEIRO\n");
		setbuf(stdin,NULL);
		fgets(aux, 100,stdin);
		aux[strlen(aux)-1]='\0';
	}while(((verifica_nome(aux)))==0);
	strcpy(nova_reserva.nome,aux);
	
	//Leitura do sexo(completo, testado)
	do{
		clear();
		printf("\n___________________________________");
		printf("\nCADASTRO DE RESERVA\n\n");
		printf("INFORME O SEXO M/F\n");
		setbuf(stdin,NULL);
		scanf("%s",aux);
	}while(verifica_sexo(aux)==0);
	nova_reserva.sexo=aux[0];
	
	//leitura data de nascimento(completo, testado)
	do{
		do{
			clear();
			printf("\n___________________________________");
			printf("\nCADASTRO DE RESERVA\n\n");
			printf("INFORME SEU DIA DE NASCIMENTO, EX(10)\n");
			setbuf(stdin,NULL);
			scanf("%s", aux);
		}while(verifica_numero(aux)==0);
		aux_dia=string_para_inteiro(aux);
		
		do{
			clear();
			printf("\n___________________________________");
			printf("\nCADASTRO DE RESERVA\n\n");
			printf("INFORME O MES DO SEU NASCIMENTO, EX(5)\n");
			setbuf(stdin,NULL);
			scanf("%s", aux);
		}while(verifica_numero(aux)==0);
		aux_mes=string_para_inteiro(aux);
		
		do{
			clear();
			printf("\n___________________________________");
			printf("\nCADASTRO DE RESERVA\n\n");
			printf("INFORME O ANO DO SEU NASCIMENTO, EX(2005)\n");
			setbuf(stdin,NULL);
			scanf("%s", aux);
		}while(verifica_numero(aux)==0);
		aux_ano=string_para_inteiro(aux);
		
	}while(!verificador_data(aux_dia, aux_mes, aux_ano));
	nova_reserva.data_nascimento.dia = aux_dia;
	nova_reserva.data_nascimento.mes = aux_mes;
	nova_reserva.data_nascimento.ano = aux_ano;
	
	
	FILE *reserva = fopen("dados_reserva.bin", "ab");
	FILE *voo = fopen("dados_voo.bin", "rb");
	DADOS_VOO dado;
	if(voo == NULL){
		printf("ERROR");
		return;
	}else{
		while(fread(&dado, sizeof(DADOS_VOO),1,voo )==1){
			if(strcmp(dado.numero_voo, nova_reserva.numero_voo)==0){
				nova_reserva.status_reserva=dado.status_voo;
				break;
			}
		}
	}
	
	fwrite(&nova_reserva,sizeof(DADOS_RESERVA),1,reserva);
	
	fclose(reserva);
}

//CONSULTA TODAS AS RESERVAS EM UM VOO
void consultar_voo(){

	DADOS_RESERVA ler_reserva;
	int k=0;

	char aux[100];
	do{
		clear();
		printf("\n___________________________________");
		printf("\nCONSULTA DE VOO\n\n");
		printf("INFORME O CODIGO DO VOO:\n");
		setbuf(stdin,NULL);
		scanf("%s",aux);
	}while((verifica_cadastro(aux, 1))==0);

	FILE *abrir_reserva = fopen("dados_reserva.bin", "rb");
	if(abrir_reserva == NULL){
		clear();
		printf("\nNENHUMA RESERVA ENCONTRADA OU VOO AINDA NAO CADASTRADO\n");
		return;
	}

	clear();
	while(fread(&ler_reserva, sizeof(DADOS_RESERVA), 1, abrir_reserva)==1){
		if(strcmp(ler_reserva.numero_voo, aux)==0){
			printf("\n____________________________________________");
			ler_reserva.status_reserva == 1 ? printf("\nRESERVA ATIVA"):printf("\nRESERVA CANCELADA");
			printf("\n\nNUMERO RESERVA: %s",ler_reserva.numero_reserva);
			printf("\nNUMERO VOO: %s", ler_reserva.numero_voo);
			printf("\nCPF: %s", ler_reserva.cpf);
			printf("\nNOME PASSAGEIRO: %s", ler_reserva.nome);
			printf("\nSEXO: %c", ler_reserva.sexo);
			printf("\nDATA DE NASCIMENTO: %d/%d/%d", ler_reserva.data_nascimento.dia,ler_reserva.data_nascimento.mes,ler_reserva.data_nascimento.ano);
			k++;
		}
	}

	if(k==0){
		clear();
		printf("\nNENHUMA RESERVA ENCONTRADA OU VOO AINDA NAO CADASTRADO\n");
	}else{
		DADOS_VOO pesquisa;
		FILE *voo = fopen("dados_voo.bin", "rb");
		if(voo==NULL){
			fclose(abrir_reserva);
			return;
		}else{
			while(fread(&pesquisa,sizeof(DADOS_VOO),1,voo)){
				if(strcmp(pesquisa.numero_voo,aux)==0){
					printf("\nTAXA DE OCUPACAO %.3f%%", (float)100*k/pesquisa.nmr_passageiros);
					fclose(abrir_reserva);
					fclose(voo);
					return;
				}
			}
		}

		
	}
	fclose(abrir_reserva);
	return;
}

//CONSULTA UMA RESERVA
void consultar_reserva(){

	char aux[100];
	do{
		clear();
		printf("\n___________________________________");
		printf("\nCONSULTA DE RESERVA\n\n");
		printf("INFORME O CODIGO DA RESERVA:\n");
		setbuf(stdin,NULL);
		scanf("%s",aux);
	}while((verifica_cadastro(aux, 2)==0));

    clear();
    DADOS_RESERVA consulta;
    FILE *file = fopen("dados_reserva.bin", "rb");
    if(file==NULL){
		printf("\nNENHUMA RESERVA ENCONTRADA\n");
		return;
    }else{
        while (fread(&consulta,sizeof(DADOS_RESERVA),1,file)==1){
            if(strcmp(consulta.numero_reserva,aux)==0){
				
                printf("\n____________________________________________");
				printf("\n\nNUMERO RESERVA: %s",consulta.numero_reserva);
				printf("\nNUMERO VOO: %s", consulta.numero_voo);
				printf("\nCPF: %s", consulta.cpf);
				printf("\nNOME PASSAGEIRO: %s", consulta.nome);
				printf("\nSEXO: %c", consulta.sexo);
				printf("\nDATA DE NASCIMENTO: %d/%d/%d\n", consulta.data_nascimento.dia,consulta.data_nascimento.mes,consulta.data_nascimento.ano);
				consulta.status_reserva == 1 ? printf("\nRESERVA ATIVA\n"):printf("\nRESERVA CANCELADA\n");
				fclose(file);
				return;
            }
        }
		printf("\nNENHUMA RESERVA ENCONTRADA\n");
		fclose(file);
		return;
    }
}

//CONSULTAR TODAS AS RESERVAS FEITAS POR UM PASSAGEIRO
void consultar_passageiro(){

	int k=0;
	char aux[100];
	do{
		clear();
		printf("\n___________________________________");
		printf("\nCONSULTA DE PASSAGEIRO\n\n");
		printf("INFORME O CPF DO PASSAGEIRO: XXX.XXX.XXX-XX\n");
		setbuf(stdin,NULL);
		scanf("%s",aux);
	}while(!verifica_cpf(aux, NULL,2));

	DADOS_RESERVA consulta;
	FILE *file = fopen("dados_reserva.bin", "rb");
	if(file == NULL){
		clear();
		printf("\nNENHUMA RESERVA ENCONTRADA\n");
		return;
	}else{
		clear();
		while (fread(&consulta,sizeof(DADOS_RESERVA),1,file)==1){
			if(strcmp(consulta.cpf,aux)==0){

				printf("\n____________________________________________");
				printf("\n\nNUMERO RESERVA: %s",consulta.numero_reserva);
				printf("\nNUMERO VOO: %s", consulta.numero_voo);
				printf("\nCPF: %s", consulta.cpf);
				printf("\nNOME PASSAGEIRO: %s", consulta.nome);
				printf("\nSEXO: %c", consulta.sexo);
				printf("\nDATA DE NASCIMENTO: %d/%d/%d\n", consulta.data_nascimento.dia,consulta.data_nascimento.mes,consulta.data_nascimento.ano);
				consulta.status_reserva == 1 ? printf("\nRESERVA ATIVA\n"):printf("\nRESERVA CANCELADA\n");
				k=1;
			}
		}
		if(k==0){
			printf("\nNENHUMA RESERVA ENCONTRADA\n");
		}
		fclose(file);
		return;
	}
}

//VERIFICAR SE A DATA É ANTERIOR A DATA DE HOJE
int verifica_data_anterior(char aux[]){

	struct tm *data_hora_atual;
	time_t segundos;
	time(&segundos);
	data_hora_atual = localtime(&segundos);	

	DADOS_VOO pesquisa;
	FILE *file = fopen("dados_voo.bin", "rb");
	if(file == NULL){
		clear();
		printf("\nNENHUM VOO CADASTRADO\n");
		return;
	}else{
		while (fread(&pesquisa,sizeof(DADOS_VOO),1,file)==1){
			if(strcmp(pesquisa.numero_voo, aux)==0){
				if(pesquisa.data_voo.ano<data_hora_atual->tm_year+1900){
					clear();
					printf("\nCANCELAMENTO NAO PERMITIDO, ANO PASSADO\n");
					fclose(file);
					return 0;
				}else if(pesquisa.data_voo.ano == data_hora_atual->tm_year+1900){
					if(pesquisa.data_voo.mes<data_hora_atual->tm_mon+1){
						clear();
						printf("\nCANCELAMENTO NAO PERMITIDO, MES PASSADO\n");
						fclose(file);
						return 0;
					}else if(pesquisa.data_voo.mes == data_hora_atual->tm_mon+1){
						if(pesquisa.data_voo.dia<data_hora_atual->tm_mday){
							clear();
							printf("\nCANCELAMENTO NAO PERMITIDO, DIA PASSADO\n");
							fclose(file);
							return 0;
						}else if(pesquisa.data_voo.dia==data_hora_atual->tm_mday){
							if(pesquisa.hora_voo.hora<data_hora_atual->tm_hour){
								clear();
								printf("\nCANCELAMENTO NAO PERMITIDO, HORA PASSADA\n");
								fclose(file);
								return 0;
							}else if(pesquisa.hora_voo.hora==data_hora_atual->tm_hour){
								if(pesquisa.hora_voo.minutos<data_hora_atual->tm_min){
									clear();
									printf("\nCANCELAMENTO NAO PERMITIDO, MINUTOS PASSADOS\n");
									fclose(file);
									return 0;
								}
							}
						}
					}
				}
			}
		}
		fclose(file);
		return 1;	
	}
}

//MUDA O STATUS DE VOO E TODAS SUAS RESERVA PARA CANCELADO
void cancelar_voo(){

	//PARTE 1: PRIMEIRO ALTERAR STATUS DO VOO PARA CANCELADO
	char aux[100];
	do{
		clear();
		printf("\n___________________________________");
		printf("\nCANCELAMENTO DE VOO\n\n");
		printf("INFORME O CODIGO DO VOO:\n");
		setbuf(stdin,NULL);
		scanf("%s",aux);
	}while((verifica_cadastro(aux, 1)==0));

	if(verifica_data_anterior(aux)==0){	
		return;
	}
	
	//Copiando todos os dados do arquivo de voo para um buffer
	DADOS_VOO ler;
	FILE *leitura = fopen("dados_voo.bin", "rb");

	if(leitura == NULL){
		clear();
		printf("\nNENHUM VOO CADASTRADO\n");
		return;
	}
	FILE *escrita = fopen("buffer_voo.bin", "wb");

	while(fread(&ler, sizeof(DADOS_VOO),1,leitura)==1){
		fwrite(&ler,sizeof(DADOS_VOO),1,escrita);
	}
	
	fclose(leitura);
	fclose(escrita);

	//Copiar dados do buffer para o arquivo principal
	FILE *escrita_voo = fopen("dados_voo.bin", "wb");
	FILE *leitura_buffer = fopen("buffer_voo.bin", "rb");

	if(leitura_buffer == NULL){
		printf("\nNAO FOI POSSIVEL ABRIR O BUFFER\n");
		fclose(escrita_voo);
		return;
	}

	int k=0;
	while(fread(&ler, sizeof(DADOS_VOO),1,leitura_buffer)==1){
		if(strcmp(ler.numero_voo,aux)==0){
			ler.status_voo=0;//Alterando o status do voo para cancelado
			k=1;
		}
		fwrite(&ler,sizeof(DADOS_VOO),1,escrita_voo);
	}

	if(k==0){
		clear();
		printf("\nNENHUM VOO ENCONTRADO\n");
		fclose(escrita_voo);
		fclose(leitura_buffer);
		return;
	}else{
		clear();
		printf("\nVOO CANCELADO COM SUCESSO\n");
	}

	fclose(escrita_voo);
	fclose(leitura_buffer);


	//PARTE 2: ALTERAR O STATUS DAS RESERVAS PARA CANCELADAS
	DADOS_RESERVA ler_reserva;
	FILE *leitura_reserva = fopen("dados_reserva.bin", "rb");

	if(leitura_reserva == NULL){
		//Nenuma reserva para cancelar
		return;
	}
	FILE *escrita_buffer = fopen("buffer_reserva.bin", "wb");

	//Copiando todos os dados de reserva para um arquivo buffer
	while(fread(&ler_reserva, sizeof(DADOS_RESERVA),1,leitura_reserva)==1){
		fwrite(&ler_reserva,sizeof(DADOS_RESERVA),1,escrita_buffer);
	}
	fclose(leitura_reserva);
	fclose(escrita_buffer);

	
	//Copiando do arquivo buffer para novo arquivo principal de reserva
	FILE *leitura_buffer_reserva = fopen("buffer_reserva.bin","rb");
	FILE *escrita_reserva = fopen("dados_reserva.bin", "wb");

	if(leitura_buffer_reserva == NULL){
		printf("FALHA AO ABRIR BUFFER");
		fclose(escrita_reserva);
		return;
	}

	while(fread(&ler_reserva, sizeof(DADOS_RESERVA),1,leitura_buffer_reserva)==1){
		if(strcmp(ler_reserva.numero_voo, aux)==0){
			ler_reserva.status_reserva = 0;//Alterando status reserva para cancelado
		}
		fwrite(&ler_reserva,sizeof(DADOS_RESERVA),1,escrita_reserva);
	}
	
	fclose(leitura_buffer_reserva);
	fclose(escrita_reserva);

	return;

}

//CANCELA SOMENTE UMA RESERVA
void cancelar_reserva(){

	//PARTE 2: ALTERAR O STATUS DAS RESERVAS PARA CANCELADAS

	char aux[100];
	do{
		clear();
		printf("\n___________________________________");
		printf("\nCANCELAMENTO DE RESERVA\n\n");
		printf("INFORME O CODIGO DA RESERVA:\n");
		setbuf(stdin,NULL);
		scanf("%s",aux);
	}while((verifica_cadastro(aux, 2)==0));


	
	DADOS_RESERVA ler_reserva;
	FILE *leitura_reserva = fopen("dados_reserva.bin", "rb");

	if(leitura_reserva == NULL){
		//Nenuma reserva para cancelar
		clear();
		printf("\nNENHUMA RESERVA ENCONTRADA\n");
		return;
	}
	FILE *escrita_buffer = fopen("buffer_reserva.bin", "wb");

	//Antes de cancelar a reserva, devo consultar a data do voo
	//Copiando todos os dados de reserva para um arquivo buffer
	while(fread(&ler_reserva, sizeof(DADOS_RESERVA),1,leitura_reserva)==1){

		fwrite(&ler_reserva,sizeof(DADOS_RESERVA),1,escrita_buffer);
		if(strcmp(ler_reserva.numero_reserva,aux)==0){
				if(verifica_data_anterior(ler_reserva.numero_voo)==0){	
					return;
				}
		}
	}
	fclose(leitura_reserva);
	fclose(escrita_buffer);

	//Copiando do arquivo buffer para novo arquivo principal de reserva
	FILE *leitura_buffer_reserva = fopen("buffer_reserva.bin","rb");
	FILE *escrita_reserva = fopen("dados_reserva.bin", "wb");

	if(leitura_buffer_reserva == NULL){
		printf("FALHA AO ABRIR BUFFER");
		fclose(escrita_reserva);
		return;
	}

	int k =0;
	while(fread(&ler_reserva, sizeof(DADOS_RESERVA),1,leitura_buffer_reserva)==1){
		if(strcmp(ler_reserva.numero_reserva, aux)==0){
			ler_reserva.status_reserva = 0;//Alterando status reserva para cancelado
			k=1;
		}
		fwrite(&ler_reserva,sizeof(DADOS_RESERVA),1,escrita_reserva);
	}

	if(k==0){
		clear();
		printf("\nNENHUMA RESERVA ENCONTRADA\n");
	}else{
		clear();
		printf("\nRESERVA CANCELADA COM SUCESSO\n");
	}
	
	fclose(leitura_buffer_reserva);
	fclose(escrita_reserva);
	return;

}

//EXCLUI UM VOO E TODAS SUAS RESERVAS
void excluir_voo(){

	//PARTE 1: PRIMEIRO ALTERAR STATUS DO VOO PARA CANCELADO
	char aux[100];
	do{
		clear();
		printf("\n___________________________________");
		printf("\nEXCLUSAO DE VOO\n\n");
		printf("INFORME O CODIGO DO VOO:\n");
		setbuf(stdin,NULL);
		scanf("%s",aux);
	}while((verifica_cadastro(aux, 1)==0));
	
	//Copiando todos os dados do arquivo de voo para um buffer
	DADOS_VOO ler;
	FILE *leitura = fopen("dados_voo.bin", "rb");

	if(leitura == NULL){
		clear();
		printf("\nNENHUM VOO CADASTRADO\n");
		return;
	}
	FILE *escrita = fopen("buffer_voo.bin", "wb");

	while(fread(&ler, sizeof(DADOS_VOO),1,leitura)==1){
		fwrite(&ler,sizeof(DADOS_VOO),1,escrita);
	}
	
	fclose(leitura);
	fclose(escrita);

	//Copiar dados do buffer para o arquivo principal
	FILE *escrita_voo = fopen("dados_voo.bin", "wb");
	FILE *leitura_buffer = fopen("buffer_voo.bin", "rb");

	if(leitura_buffer == NULL){
		printf("\nNAO FOI POSSIVEL ABRIR O BUFFER\n");
		fclose(escrita_voo);
		return;
	}

	int k=0;
	while(fread(&ler, sizeof(DADOS_VOO),1,leitura_buffer)==1){
		if(strcmp(ler.numero_voo,aux)){
			k++;
			fwrite(&ler,sizeof(DADOS_VOO),1,escrita_voo);
		}else{
			if(strcmp(ler.numero_voo,aux)==0){
				k++;
			}
		}
	}
	if(k==0){
		clear();
		printf("\nNENHUM VOO ENCONTRADO\n");
		fclose(escrita_voo);
		fclose(leitura_buffer);
		return;
	}else{
		clear();
		printf("\nVOO EXCLUIDO COM SUCESSO\n");
	}

	fclose(escrita_voo);
	fclose(leitura_buffer);


	//PARTE 2: EXCLUIR RESERVAS, CASO EXISTAM 
	DADOS_RESERVA ler_reserva;
	FILE *leitura_reserva = fopen("dados_reserva.bin", "rb");

	if(leitura_reserva == NULL){
		//Nenuma reserva para excluir
		return;
	}
	FILE *escrita_buffer = fopen("buffer_reserva.bin", "wb");

	//Copiando todos os dados de reserva para um arquivo buffer
	while(fread(&ler_reserva, sizeof(DADOS_RESERVA),1,leitura_reserva)==1){
		fwrite(&ler_reserva,sizeof(DADOS_RESERVA),1,escrita_buffer);
	}
	fclose(leitura_reserva);
	fclose(escrita_buffer);

	
	//Copiando do arquivo buffer para novo arquivo principal de reserva
	FILE *leitura_buffer_reserva = fopen("buffer_reserva.bin","rb");
	FILE *escrita_reserva = fopen("dados_reserva.bin", "wb");

	if(leitura_buffer_reserva == NULL){
		printf("FALHA AO ABRIR BUFFER");
		fclose(escrita_reserva);
		return;
	}

	while(fread(&ler_reserva, sizeof(DADOS_RESERVA),1,leitura_buffer_reserva)==1){
		if(strcmp(ler_reserva.numero_voo, aux)!=0){
			fwrite(&ler_reserva,sizeof(DADOS_RESERVA),1,escrita_reserva);
		}
	}
	
	fclose(leitura_buffer_reserva);
	fclose(escrita_reserva);
	return;

}

int main(){
	
	char escolha;
	do{
		clear();
		printf("MENU DE OPCOES:\n\n");
		printf("1) Cadastrar voo\n");
		printf("2) Cadastrar reserva\n");
		printf("3) Consultar voo\n");
		printf("4) Consultar reserva\n");
		printf("5) Consultar passageiro\n");
		printf("6) Cancelar voo\n");
		printf("7) Cancelar reserva\n");
		printf("8) Excluir voo\n");
		printf("9) Sair do programa\n");
	
		setbuf(stdin,NULL);
		scanf(" %c",&escolha);
		switch (escolha){
			case '1':

				cadastrar_voo();
				clear();
				printf("\nDADOS CADASTRADOS COM SUCESSO!\n");
				pause();
				break;
		
			case '2':
            
				cadastrar_reserva();
				clear();			
				printf("\nDADOS CADASTRADOS COM SUCESSO!\n");
				pause();
				break;
			
			case '3':
				clear();
				consultar_voo();
				pause();
				break;
			
			case '4':
				clear();
				consultar_reserva();
				pause();
				break;

			case '5':
				clear();
				consultar_passageiro();
				pause();
				break;

			case '6':
				clear();
				cancelar_voo();
				pause();
				break;

			case '7':
				clear();
				cancelar_reserva();
				pause();
				break;

			case '8':

				clear();
				excluir_voo();
				pause();
				break;
				
			default:
				pause();
				break;
		}
	
	}while(escolha != '9');
	return 0;
}

