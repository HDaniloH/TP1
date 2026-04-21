#include <iostream>
#include "dominios.hpp"

using namespace std;

//Entidade_Plano_de_Sprint:
class Plano_de_Sprint{
private:
    Codigo codigo;
    Texto objetivo;
    Tempo capacidade;
public:
    Codigo getCod()const;
    Texto getObj()const;
    Tempo getCap()const;
    void setCod(Codigo);
    void setObj(Texto);
    void setCap(Tempo);
};
//Metodos_Plano_de_Sprint:
inline Codigo Plano_de_Sprint::getCod()const{
    return codigo;
}
inline Texto Plano_de_Sprint::getObj()const{
    return objetivo;
}
inline Tempo Plano_de_Sprint::getCap()const{
    return capacidade;
}
inline void Plano_de_Sprint::setCod(Codigo code){
    this->codigo = code;
}
inline void Plano_de_Sprint::setObj(Texto texto){
    this->objetivo = texto;
}
inline void Plano_de_Sprint::setCap(Tempo tempo){
    this->capacidade = tempo;
}

//Entidade Historia_de_usuario:
class Historia_de_usuario{
private:
    Codigo codigo;
    Texto titulo;
    Texto papel;
    Texto acao;
    Texto valor;
    Tempo estimativa;
    Prioridade prioridade;
    Estado estado;
public:
    Codigo getCod()const;
    Texto getTit()const;
    Texto getPap()const;
    Texto getAca()const;
    Texto getVal()const;
    Tempo getEst()const;
    Prioridade getPri()const;
    Estado getEto()const;
    void setCod(Codigo);
    void setTit(Texto);
    void setPap(Texto);
    void setAca(Texto);
    void setVal(Texto);
    void setEst(Tempo);
    void setPri(Prioridade);
    void setEto(Estado);
};
//Metodos Historia_de_usuario:
inline Codigo Historia_de_usuario::getCod()const{
    return codigo;
}
inline Texto Historia_de_usuario::getTit()const{
    return titulo;
}
inline Texto Historia_de_usuario::getPap()const{
    return papel;
}
inline Texto Historia_de_usuario::getAca()const{
    return acao;
}
inline Texto Historia_de_usuario::getVal()const{
    return valor;
}
inline Tempo Historia_de_usuario::getEst()const{
    return estimativa;
}
inline Prioridade Historia_de_usuario::getPri()const{
    return prioridade;
}
inline Estado Historia_de_usuario::getEto()const{
    return estado;
}
inline void Historia_de_usuario::setCod(Codigo code){
    this->codigo = code;
}
inline void Historia_de_usuario::setTit(Texto titu){
    this->titulo = titu;
}
inline void Historia_de_usuario::setPap(Texto pape){
    this->papel = pape;
}
inline void Historia_de_usuario::setAca(Texto acao){
    this->acao = acao;
}
inline void Historia_de_usuario::setVal(Texto valo){
    this->valor = valo;
}
inline void Historia_de_usuario::setEst(Tempo esti){
    this->estimativa = esti;
}
inline void Historia_de_usuario::setPri(Prioridade prio){
    this->prioridade = prio;
}
inline void Historia_de_usuario::setEto(Estado esta){
    this->estado = esta;
}

