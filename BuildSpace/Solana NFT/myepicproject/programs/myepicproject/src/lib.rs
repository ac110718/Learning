use anchor_lang::prelude::*;

declare_id!("HwM4AQWCqLT6ixzpzw2Poz1GivsFjVWs68SPJe6hrf3E");

#[program]
pub mod myepicproject {
    use super::*;

    pub fn start_stuff_off(ctx: Context<StartStuffOff>) -> Result<()> {
        // get reference to account within context
        let base_account = &mut ctx.accounts.base_account;
        base_account.total_gifs = 0;
        Ok(())
    }

    pub fn add_gif(ctx: Context<AddGif>, gif_link: String) -> Result<()> {
        // pass in an account like a file.. base_account is for data storage
        // user is for ownership
        let base_account = &mut ctx.accounts.base_account;
        let user = &mut ctx.accounts.user;

        let item = ItemStruct {
            gif_link: gif_link.to_string(),
            user_address: *user.to_account_info().key,
            likes: 0,
            lamports: 0,
            id: base_account.total_gifs,
        };

        base_account.gif_list.push(item);
        base_account.total_gifs += 1;
        Ok(())
    }

    pub fn add_like(ctx: Context<AddGif>, id: u64) -> Result<()> {
        let base_account = &mut ctx.accounts.base_account;
        base_account.gif_list[id as usize].likes += 1;
        Ok(())
    }

    pub fn add_tip(ctx: Context<AddGif>, id: u64, tip: u64) -> Result<()> {
        let base_account = &mut ctx.accounts.base_account;
        base_account.gif_list[id as usize].lamports += tip;
        Ok(())
    }
}

#[derive(Accounts)]
pub struct StartStuffOff<'info> {
    #[account(init, payer = user, space = 9000)]
    // create new account owned by current program (init), user will pay, 9000 rent
    pub base_account: Account<'info, BaseAccount>,
    // user calling program owns wallet account
    #[account(mut)]
    pub user: Signer<'info>,
    pub system_program: Program <'info, System>,
}

#[derive(Accounts)]
pub struct AddGif<'info> {
    #[account(mut)]
    pub base_account: Account<'info, BaseAccount>,
    #[account(mut)]
    pub user: Signer<'info>,
}

#[derive(Debug, Clone, AnchorSerialize, AnchorDeserialize)]
pub struct ItemStruct {
    pub gif_link: String,
    pub user_address: Pubkey,
    pub likes: u64,
    pub lamports: u64,
    pub id: u64,
}

#[account]
pub struct BaseAccount {
    pub total_gifs: u64,
    pub gif_list: Vec<ItemStruct>
}