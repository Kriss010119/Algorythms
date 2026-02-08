import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

unq = 50000
arr = {
    'b': [4, 6, 8, 10, 12, 14],
    'actual_error': [26.7409, 9.13309, 2.44886, 3.08742, 0.27069, 0.753047],
    'theoretical_error': [26.0, 13.0, 6.5, 3.25, 1.625, 0.8125],
    'M': [16, 64, 256, 1024, 4096, 16384],
    'estimate': [36629.6, 45433.5, 48775.6, 51543.7, 50135.3, 50376.5]
}

def gr1():
    df = pd.read_csv('res1.csv')
    plt.figure(figsize=(10,6))
    plt.plot(df['pct'], df['exact'], 'b-', linewidth=2, label='True (F0_t)')
    plt.plot(df['pct'], df['est'], 'r--', linewidth=2, label='HLL (N_t)')
    plt.fill_between(df['pct'], df['est']-df['err'], df['est']+df['err'], 
                     alpha=0.2, color='r', label='± Error')
    plt.xlabel('Stream %', fontsize=12)
    plt.ylabel('Unique count', fontsize=12)
    plt.title('HLL vs True (50000 unique elements)', fontsize=14)
    plt.legend(loc='best')
    plt.grid(True, alpha=0.3)
    plt.savefig('plot1_hll_vs_true.png', dpi=300, bbox_inches='tight')
    plt.show()

def gr2():
    plt.figure(figsize=(10,6))
    plt.plot(arr['b'], arr['actual_error'], 'bo-', linewidth=2, markersize=8, label='Actual error')
    plt.plot(arr['b'], arr['theoretical_error'], 'r--', linewidth=2, label='Theoretical error (1.04/√M)')
    for i, (b, act, theo) in enumerate(zip(arr['b'], arr['actual_error'], arr['theoretical_error'])):
        plt.annotate(f'{act:.1f}%', xy=(b, act), xytext=(0, 10), textcoords='offset points', ha='center')
        plt.annotate(f'{theo:.1f}%', xy=(b, theo), xytext=(0, -15), textcoords='offset points', ha='center', color='red')
    plt.xlabel('B (bits)', fontsize=12)
    plt.ylabel('Error (%)', fontsize=12)
    plt.title('HLL Error vs Number of Bits (B)', fontsize=14)
    plt.legend(loc='best')
    plt.grid(True, alpha=0.3)
    plt.xticks(arr['b'])
    plt.savefig('plot2_error_by_b.png', dpi=300, bbox_inches='tight')
    plt.show()

def gr3():
    plt.figure(figsize=(10,6))
    x = np.arange(len(arr['b']))
    width = 0.35
    plt.bar(x - width/2, arr['estimate'], width, label='HLL Estimate', color='lightblue', edgecolor='black')
    plt.bar(x + width/2, [unq]*len(arr['b']), width, label='True Value (50000)', color='lightgreen', edgecolor='black', alpha=0.7)
    for i, (est, err) in enumerate(zip(arr['estimate'], arr['actual_error'])):
        plt.text(i - width/2, est + 1000, f'{est:.0f}\n({err:.1f}%)', ha='center', va='bottom', fontsize=9)
    plt.axhline(y=unq, color='red', linestyle='--', alpha=0.5)
    plt.xlabel('B (bits) / M (registers)', fontsize=12)
    plt.ylabel('Unique count', fontsize=12)
    plt.title('HLL Estimates for Different B Values', fontsize=14)
    plt.xticks(x, [f'B={b}\nM={m}' for b, m in zip(arr['b'], arr['M'])])
    plt.legend(loc='best')
    plt.grid(True, alpha=0.3, axis='y')
    plt.savefig('plot3_estimates_by_b.png', dpi=300, bbox_inches='tight')
    plt.show()


if __name__ == "__main__":    
    gr1()
    gr3()
    gr3()