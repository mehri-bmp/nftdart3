
library(nftbart, lib.loc="/Users/mehribmp/Library/R/dev/arm64/4.3/library") # mehri-bmp


B=8 ## Setting the number of CPU cores for parallel processing to 8 (B=8).
options(mc.cores=B)


data(lung) ##Loading the "lung" dataset, for survival analysis
N=length(lung$status)

##lung$status: 1=censored, 2=dead
##delta: 0=censored, 1=dead
delta=lung$status-1

## this study reports time in days rather than weeks or months

times=lung$time
times=times/7  ## weeks

## matrix of covariates
x.train=cbind(lung[ , -(1:3)])
## lung$sex:        Male=1 Female=2

# mehri-bmp, adding 50 coloumns of random uniform noise to the input to test dart 
set.seed(99) # Setting seed for reproducibility 
#x.noise <- matrix(runif(N * 100), nrow = N, ncol = 100) # Generate uniform noise matrix 
#x.noise <- matrix(rnorm(N * 100), nrow = N, ncol = 100) # Generate normal noise matrix
#x.noise <- matrix(rbinom(N * 100, 1, 0.5), nrow = N, ncol = 100) # Generate binary noise matrix
#x.train <- cbind(x.train, x.noise) # Add noise to x.train 


#x.cont <- matrix(rnorm(N*50), nrow = N, ncol = 50)
#x.bin <- matrix(rbinom(N*10, 1, 0.5), nrow = N, ncol = 10)
x.bin <- matrix(ifelse(rbinom(N*10, 1, 0.5) == 1, 5, 3), nrow = N, ncol = 10)

#x.train <- cbind(x.train, x.cont, x.bin) 
x.train <- cbind(x.train, x.bin) 

post=nft2(x.train, x.train, times, delta, K=0, sparse=TRUE) ##mehri-bmp: added sparse=TRUE

# pdf('LungUniNoiseSparseTRUETheta1.pdf')
pdf("/Users/mehribmp/Downloads/LungBinomNoiseSparseTRUETheta11053.pdf")

par(mfrow = c(4, 2))
hist(1*(post$f.varcount[ , 'ph.ecog']>0), ylim = c(0, 2000), xlim = 0:1, main = '', xlab = 'ph.ecog')
hist(1*(post$f.varcount[ , 'sex']>0), ylim = c(0, 2000), xlim = 0:1, main = '', xlab = 'sex')
hist(1*(post$f.varcount[ , 10]>0), ylim = c(0, 2000), xlim = 0:1, main = '', xlab = '10')
hist(1*(post$f.varcount[ , 17]>0),  ylim = c(0, 2000), xlim = 0:1, main = '', xlab = '17')
# hist(1*(post$f.varcount[ , 97]>0),  ylim = c(0, 2000), xlim = 0:1, main = '', xlab = '97')
# hist(1*(post$f.varcount[ , 107]>0),  ylim = c(0, 2000), xlim = 0:1, main = '', xlab = '107')
mtext("nftbart, Sparse=TRUE, binom noise, theta=1", side = 3, outer = TRUE, line = -2, cex = 1.5) # Adding a common title, mehri-bmp
par(mfrow = c(1, 1))
dev.off()

x.test = rbind(x.train, x.train)
x.test[ , 2]=rep(1:2, each=N)
K=100
events=c(0, quantile(times[delta==1], (0:(K-1))/(K-1)))
a=proc.time()
pred = predict(post, x.test, x.test, K=K, events=events[-1],
               XPtr=TRUE, FPD=TRUE)
               
print((proc.time()-a)/60)

plot(events, c(1, pred$surv.fpd.mean[1:K]), type='l', col=4,
     ylim=0:1,
     xlab=expression(italic(t)), sub='weeks',
     ylab=expression(italic(S)(italic(t), italic(x))))
lines(events, c(1, pred$surv.fpd.upper[1:K]), lty=2, lwd=2, col=4)
lines(events, c(1, pred$surv.fpd.lower[1:K]), lty=2, lwd=2, col=4)
lines(events, c(1, pred$surv.fpd.mean[K+1:K]), lwd=2, col=2)
lines(events, c(1, pred$surv.fpd.upper[K+1:K]), lty=2, lwd=2, col=2)
lines(events, c(1, pred$surv.fpd.lower[K+1:K]), lty=2, lwd=2, col=2)
legend(90, 0.95, c('NFT DART', 'Mortality',
                     'Males', 'Females'), lwd=2, col=c(0, 0, 4, 2), lty=1)
abline(h=0:1, v=0)
