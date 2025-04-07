# 使用 Node.js 18 Alpine 作為前端基礎環境
FROM node:18-alpine

WORKDIR /app

# 複製前端 package.json 並安裝 Node.js 依賴
COPY Frontend/package.json /app/
RUN npm install

# 複製完整前端代碼
COPY Frontend/ /app/

# 開放端口
EXPOSE 3000

# 啟動 React 應用
CMD ["npm", "start"]
