#ifndef DOMINIOS_HPP
#define DOMINIOS_HPP
#include <string>
#include <stdexcept>

///
/// Padr&atilde;o para representa&ccedil;&atilde;o de codigo.
///
/// Regras de formato:
///
/// - C&oacute;digo &eacute; v&aacute;lido caso:
///   - Tamanho igual a 5;
///   - Os dois primeiros caracteres s&atilde;o letras maiusculas;
///   - Os 3 ultimos caracteres s&atilde;o digitos num&eacute;ricos.
///

//Domínio-Codigo:
class Codigo{
private:
    static const int LIMITE = 5;
    void validar(std::string);
    std::string Code;
public:

///
/// Retorna c&oacute;digo.
///
/// @return C&oacute;digo.
///

    std::string getCode()const;

///
/// Armazena o c&oacute;digo informado caso o mesmo seja v&aacute;lido.
///
/// Caso o c&oacute;digo informado seja inv&aacute;lido, lan&ccedil;a exce&ccedil;&atilde;o.
///
/// @param valor C&oacute;digo.
///
/// @throw invalid_argument
///

    void setCode(std::string);
};
//Metodos-Codigo:
inline std::string Codigo::getCode()const{
    return Code;
}


///
/// Padr&atilde;o para representa&ccedil;&atilde;o de senha.
///
/// Regras de formato:
///
/// - Senha &eacute; v&aacute;lida caso:
///   - Tamanho igual a 6;
///   - Contenha apenas letras (A-Z ou a-z) ou d&iacute;gitos (0-9);
///   - Letra n&atilde;o seja seguida por letra;
///   - D&iacute;gito n&atilde;o seja seguido por d&iacute;gito;
///   - Existe pelo menos uma letra min&uacute;scula (a-z);
///   - Existe pelo menos uma letra mai&uacute;scula (A-Z);
///   - Existe pelo menos um d&iacute;gito (0-9).
///

//Domínio-Senha:
class Senha{
private:
    static const int LIMITE = 6;
    std::string senha;
    void validar(std::string);
public:

///
/// Retorna Senha.
///
/// @return Senha.
///

    std::string getSenha()const;

///
/// Armazena a senha informada caso a mesma seja v&aacute;lida.
///
/// Caso a senha informada seja inv&aacute;lida, lan&ccedil;a exce&ccedil;&atilde;o.
///
/// @param valor Senha.
///
/// @throw invalid_argument
///

    void setSenha(std::string);
};
//Metodos-Senha:
inline std::string Senha::getSenha()const{
    return senha;
}


///
/// Padr&atilde;o para representa&ccedil;&atilde;o de tempo.
///
/// Regras de formato:
///
/// - Tempo &eacute; v&aacute;lido caso:
///   - Valor <u>menor</u> ou igual a 365;
///   - Valor <u>maior</u> que 0.
///

//Domínio-Tempo:
class Tempo{
private:
    static const int max_t = 365, min_t = 0;
    int duracao;
    void validar(int);
public:

///
/// Armazena o tempo informado caso o mesmo seja v&aacute;lido.
///
/// Caso o tempo informado seja inv&aacute;lido, lan&ccedil;a exce&ccedil;&atilde;o.
///
/// @param valor Tempo.
///
/// @throw invalid_argument
///

    void setDuracao(int);

///
/// Retorna Tempo.
///
/// @return Tempo.
///

    int getDuracao()const;
};
//Metodos-Tempo:
inline int Tempo::getDuracao()const{
    return duracao;
}


///
/// Padr&atilde;o para representa&ccedil;&atilde;o de texto.
///
/// Regras de formato:
///
/// - Texto &eacute; v&aacute;lido caso:
///   - Tamanho seja <u>menor</u> ou igual a 40;
///   - Contenha apenas letras (a-z ou A-Z), d&iacute;gitos (0-9), v&iacute;rgulas, pontos ou espa&ccedil;os em branco;
///   - V&iacute;rgula n&atilde;o seja seguida por v&iacute;rgula ou ponto;
///   - Ponto n&atilde;o seja seguido por v&iacute;rgula ou ponto;
///   - Espa&ccedil;o em branco seja seguido por letra ou d&iacute;gito;
///   - Primeiro e ultimo caracter n&atilde;o seja v&iacute;rgula, ponto ou espa&ccedil;o em branco.
///

//Domínio-Texto:
class Texto{
private:
    static const int LIMITE = 40;
    std::string texto;
    void validar(std::string);
public:

///
/// Armazena o texto informado caso o mesmo seja v&aacute;lido.
///
/// Caso o texto informado seja inv&aacute;lido, lan&ccedil;a exce&ccedil;&atilde;o.
///
/// @param valor Texto.
///
/// @throw invalid_argument
///

    void setTexto(std::string);

///
/// Retorna Texto.
///
/// @return Texto.
///

    std::string getTexto()const;
};
//Metodos-Texto:
inline std::string Texto::getTexto()const{
    return texto;
}


///
/// Padr&atilde;o para representa&ccedil;&atilde;o de data.
///
/// Regras de formato:
///
/// - Data &eacute; v&aacute;lida caso:
///   - Formato seja "DIA/MÊS/ANO";
///   - Dia seja n&uacute;mero de 1 a 31;
///   - Mês seja n&uacute;mero 01, 02, 03, 04, 05, 06, 07, 08, 09 , 10, 11 ou 12;
///   - Ano seja n&uacute;mero de 2000 a 2999;
///   - Data seja v&aacute;lida considerando anos bissextos.
///

//Dominio-Data:
class Data{
private:
    int dia, mes, ano;
    std::string data;
    bool bissexto;
public:
    bool operator<(const Data& outro) const{
        if(ano != outro.ano) return ano < outro.ano;
        if(mes != outro.mes) return mes < outro.mes;
        return dia < outro.dia;
    }

///
/// Armazena o dia informado caso o mesmo seja v&aacute;lido.
///
/// Caso o dia informado seja inv&aacute;lido, lan&ccedil;a exce&ccedil;&atilde;o.
///
/// @param valor Dia.
///
/// @throw invalid_argument
///

    void setDia(int);

///
/// Armazena o mês informado caso o mesmo seja v&aacute;lido.
///
/// Caso o mês informado seja inv&aacute;lido, lan&ccedil;a exce&ccedil;&atilde;o.
///
/// @param valor Mês.
///
/// @throw invalid_argument
///

    void setMes(int);

///
/// Armazena o ano informado caso o mesmo seja v&aacute;lido.
///
/// Caso o ano informado seja inv&aacute;lido, lan&ccedil;a exce&ccedil;&atilde;o.
///
/// @param valor Ano.
///
/// @throw invalid_argument
///

    void setAno(int);

///
/// Armazena a data informada caso a mesma seja v&aacute;lida.
///
/// Caso a data informada seja inv&aacute;lida, lan&ccedil;a exce&ccedil;&atilde;o.
///
/// @param valor Data.
///
/// @throw invalid_argument
///

    void setData(std::string);

///
/// Retorna Data.
///
/// @return Data.
///

    std::string getData()const;
};
//Metodos-Data:
inline std::string Data::getData()const{
    return data;
}


///
/// Padr&atilde;o para representa&ccedil;&atilde;o de estado.
///
/// Regras de formato:
///
/// - Estado &eacute; v&aacute;lido caso:
///   - Escolha esteja entre o n&uacute;mero 1 - (A FAZER), 2 - (FAZENDO) ou 3 - (FEITO).
///

//Dominio-Estado:
class Estado{
private:
    int escolha;
    std::string estado;
    void validar(int);
    static const int LIMITE = 3;
public:

///
/// Armazena o estado baseado na escolha caso a mesma seja v&aacute;lida.
///
/// Caso a escolha seja inv&aacute;lida, lan&ccedil;a exce&ccedil;&atilde;o.
///
/// @param valor Escolha.
///
/// @throw invalid_argument
///

    void setEstado(int);

///
/// Retorna Estado.
///
/// @return Estado.
///

    std::string getEstado()const;
};
//Metodos-Estado:
inline std::string Estado::getEstado()const{
    return estado;
}


///
/// Padr&atilde;o para representa&ccedil;&atilde;o de prioridade.
///
/// Regras de formato:
///
/// - Prioridade &eacute; v&aacute;lida caso:
///   - Escolha esteja entre o n&uacute;mero 1 - (ALTA), 2 - (MEDIA) ou 3 - (BAIXA).
///

//Dominio-Prioridade:
class Prioridade{
private:
    std::string prio;
    static const int LIMITE = 3;
    int valor;
    void validar(int);
public:

///
/// Armazena a prioridade baseado na escolha caso a mesma seja v&aacute;lida.
///
/// Caso a escolha seja inv&aacute;lida, lan&ccedil;a exce&ccedil;&atilde;o.
///
/// @param valor Escolha.
///
/// @throw invalid_argument
///

    void setPrio(int);

///
/// Retorna Prioridade.
///
/// @return Prioridade.
///

    std::string getPrio()const;

};
//Metodos-Prioridade:
inline std::string Prioridade::getPrio()const{
    return prio;
}


///
/// Padr&atilde;o para representa&ccedil;&atilde;o de papel.
///
/// Regras de formato:
///
/// - Papel &eacute; v&aacute;lido caso:
///   - Escolha esteja entre o n&uacute;mero 1 - (DESENVOLVEDOR), 2 - (MESTRE SCRUM) ou 3 - (PROPIETARIO DE PRODUTO).
///

//Dominio-Papel:
class Papel{
private:
    std::string escolha_papel;
    static const int LIMITE = 3;
    int valor;
    void validar(int);
public:

///
/// Armazena o papel baseado na escolha caso a mesma seja v&aacute;lida.
///
/// Caso a escolha seja inv&aacute;lida, lan&ccedil;a exce&ccedil;&atilde;o.
///
/// @param valor Escolha.
///
/// @throw invalid_argument
///

    void setEscolha_papel(int);

///
/// Retorna Papel.
///
/// @return Papel.
///

    std::string getEscolha_papel()const;

};
//Metodos-Papel:
inline std::string Papel::getEscolha_papel()const{
    return escolha_papel;
}


///
/// Padr&atilde;o para representa&ccedil;&atilde;o de nome.
///
/// Regras de formato:
///
/// - Nome &eacute; v&aacute;lido caso:
///   - Tamanho seja <u>menor</u> ou igual a 10;
///   - Contenha apenas letras (a-z ou A-Z) ou espa&ccedil;os em branco;
///   - Espa&ccedil;o em branco seja seguido por letra;
///   - Primeiro e ultimo caracter n&atilde;o seja espa&ccedil;o em branco.
///

//Dominio-Nome:
class Nome{
private:
    static const int LIMITE = 10;
    std::string nome;
    void validar(std::string);
public:

///
/// Armazena o nome caso o mesmo seja v&aacute;lido.
///
/// Caso o nome seja inv&aacute;lido, lan&ccedil;a exce&ccedil;&atilde;o.
///
/// @param valor Nome.
///
/// @throw invalid_argument
///

    void setNome(std::string);

///
/// Retorna Nome.
///
/// @return Nome.
///

    std::string getNome()const;
};
//Metodos-Nome:
inline std::string Nome::getNome()const{
    return nome;
}


///
/// Padr&atilde;o para representa&ccedil;&atilde;o de email.
///
/// Regras de formato:
///
/// - Email &eacute; v&aacute;lido caso:
///   - Formato da parte local seja "parte-local@dom&iacute;nio";
///   - Tamanho da parte local seja <u>menor</u> ou igual a 64;
///   - Parte local contenha apenas letras (a-z), d&iacute;gitos (0-9), pontos(.) ou h&iacute;fen(-);
///   - Parte local n&atilde;o iniciar ou terminar com ponto ou h&iacute;fen;
///   - Ponto ou h&iacute;fen sejam seguidos por letra(s) ou d&iacute;gito(s);
///   - Dom&iacute;nio seja composto por uma ou mais partes separadas por ponto(.);
///   - Tamanho do dom&iacute;nio seja <u>menor</u> ou igual a 255;
///   - Cada parte do dom&iacute;nio contenha apenas letras(a-z), d&iacute;gitos (0-9) ou h&iacute;fen(-);
///   - Parte do dom&iacute;nio n&atilde;o iniciar ou terminar com h&iacute;fen.
///

//Dominio-Email:
class Email{

private:
    static const int LIMITE_LOCAL = 64;
    static const int LIMITE_DOMINIO = 255;
    std::string email;
    void validar(std::string);

public:

///
/// Retorna Email.
///
/// @return Email.
///

    std::string getEmail() const;

///
/// Armazena o email caso o mesmo seja v&aacute;lido.
///
/// Caso o email seja inv&aacute;lido, lan&ccedil;a exce&ccedil;&atilde;o.
///
/// @param valor Email.
///
/// @throw invalid_argument
///

    void setEmail(std::string);
};
//Metodos-Email:
inline std::string Email::getEmail() const {
    return email;
}
#endif
