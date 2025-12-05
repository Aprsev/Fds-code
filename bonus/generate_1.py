import random
import pyperclip

def generate_lruk_input():
    K = random.randint(1, 5)  # K 的范围是 1 到 5
    N = random.randint(500, 503)  # N 取较大值，最大为 10000
    M = random.randint(5000, 5003)  # M 取较大值，最大为 100000
    
    pages = [random.randint(1, 20000) for _ in range(M)]  # M 个随机的页面 ID
    
    result = f"{K} {N} {M}\n" + " ".join(map(str, pages))
    pyperclip.copy(result)  # 复制到剪贴板

# 生成一组测试数据并复制到剪切板
generate_lruk_input()
print("数据已复制到剪切板！")
