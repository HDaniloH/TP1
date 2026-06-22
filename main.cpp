#include "controladorasApresentacao.hpp"
#include "controladorasServico.hpp"
#include "controladorasPersistencia.hpp"
#include <iostream>
using namespace std;

int main(){
    // camada de persistencia (banco unico)
    CntrBancoDados bancoDados;

    // camada de servico
    CntrServicoAutenticacao servicoAutenticacao;
    CntrServicoPessoa       servicoPessoa;
    CntrServicoProjeto      servicoProjeto;

    // camada de apresentacao
    CntrApresentacaoAutenticacao apresentacaoAutenticacao;
    CntrApresentacaoPessoa       apresentacaoPessoa;
    CntrApresentacaoProjeto      apresentacaoProjeto;

    // ligacoes servico -> banco
    servicoAutenticacao.setCntrBancoDados(&bancoDados);
    servicoPessoa.setCntrBancoDados(&bancoDados);
    servicoProjeto.setCntrBancoDados(&bancoDados);

    // ligacoes apresentacao -> servico
    apresentacaoAutenticacao.setCntrServicoAutenticacao(&servicoAutenticacao);
    apresentacaoPessoa.setCntrServicoPessoa(&servicoPessoa);
    apresentacaoProjeto.setCntrServicoProjeto(&servicoProjeto);

    // semente: cria um usuario inicial pra poder logar (so insere se ainda nao existir)
    {
        Pessoa admin;
        Nome n; Email em; Senha s; Papel pa;
        n.setNome("Amanda");
        em.setEmail("amanda@teste.com");
        s.setSenha("a1B2c3");
        pa.setEscolha_papel(2);
        admin.setNome(n); admin.setEmail(em); admin.setSenha(s); admin.setPapel(pa);
        bancoDados.criar(admin);
    }

    // fluxo
    Email email;
    if(apresentacaoAutenticacao.autenticar(&email)){
        cout << "\nAutenticado com sucesso!\n";
        int op;
        do {
            cout << "\n========= MENU PRINCIPAL =========\n";
            cout << "1 - Gerir Pessoas\n";
            cout << "2 - Gerir Projetos\n";
            cout << "0 - Sair\n";
            cout << "Escolha: ";
            cin >> op;
            if(op == 1)      apresentacaoPessoa.executar(email);
            else if(op == 2) apresentacaoProjeto.executar(email);
            else if(op != 0) cout << "Opcao invalida.\n";
        } while(op != 0);
    } else {
        cout << "\nFalha na autenticacao.\n";
    }
    return 0;
}
